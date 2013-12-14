#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "lcd.h"
#include "ad.h"
#include "da.h"
#include "timer.h"

#define BUFSIZE       30 /* �Хåե����礭��(kB) */
#define SAMPLINGTIME 100 /* Ͽ��/�������Υ���ץ�󥰼���(us) */
#define SAMPLE         0 /* ư��������(Ͽ��)   */
#define PLAY           1 /* ư��������(����)   */
#define INVERSE        2 /* �պ����⡼�� */
#define NOSELECT      -1 /* ư��������(̤����) */

#define TIME 120000 

volatile unsigned char databuf[(unsigned long)BUFSIZE * 1024];
//volatile unsigned char databuf[120000];
volatile unsigned long bufptr;
volatile int play_mode;

int            main(void);
unsigned char  menu(void);
void           sample_replay(int mode);
void           int_imia0(void);

int main(void)
{
  /* �������Ͼ����������뤿����ѿ���������� */
  unsigned char key_data;

  ROMEMU();      /* ROM���ߥ�졼������ON */
  lcd_init();    /* LCD �ν����            */
  ad_init();     /* A/D �Ѵ���ν����      */
  da_init();     /* D/A �Ѵ���ν����      */
  timer_init();  /* �����ޤν����          */
  
  /* ������(����ͥ�0)�γ����ߴֳ� */
  timer_set(0,SAMPLINGTIME);

  /* �����˥������ϼ����Τ���Υݡ��Ȥν�����򵭽Ҥ��� */
	P6DDR &= ~0x07;                        /* P60,1,2   ���� */
	PADDR |= 0x0f;                         /* PA0,1,2,3 ���� */

	

  while (1) {
    play_mode = NOSELECT;
    key_data = menu();                    /* ��˥塼������ */
    /* Ͽ�������������줿��SAMPLE�����������������줿��PLAY */
    /* ��play_mode�˳�Ǽ��������򵭽Ҥ���                  */
		if(key_data == '*')
			play_mode = SAMPLE;
		else if(key_data == '5')
			play_mode = INVERSE;

    /* �������Ϥ���Ƥ����Ͽ��/�����δؿ���ƤӽФ������򵭽Ҥ��� */
		if(play_mode != NOSELECT)
			sample_replay(play_mode);	
  }

  return 1;
}

unsigned char  menu(void)
     /* LCD �˥�˥塼��񤤤�ư������򤹤뤿��δؿ� */
     /* ����ͤ����ϥ�������                           */
{
  /* �������ϼ����Τ�����ѿ���������� */
  unsigned char cf, key_data;

  lcd_cursor(0,0);                   /* LCD �˥�å�����ɽ�� */
  lcd_printstr("Rec:[*]  Inv:[5]");
  lcd_cursor(0,1);
  lcd_printstr(" Push * or 5 key");

  /* ��������Ƚ�����ѿ��ν����*/
  cf = 0;
  key_data = 0;

  while (key_data == 0 ){  /* �������Ϥ���ޤǥ롼�פ��� */
    /* �����˥������Ϥν����򵭽Ҥ��� */
		/* �������饭�����Ϥν��� */
		{
			key_data = 0;

			//key 4,5,6
			PADR = 0x0b;
			cf = P6DR;
			cf = ~cf;
			cf &= 0x07;
			switch(cf) {
				case 1 : key_data = '4'; break;
				case 2 : key_data = '5'; break;
				case 4 : key_data = '6'; break;
			}  

			//key 7,8,9
			//PADR = 0x0b; /* This is a mistake code. */
			PADR = 0x0d;
			cf = P6DR;
			cf = ~cf;
			cf &= 0x07;
			switch(cf) {
				case 1 : key_data = '7'; break;
				case 2 : key_data = '8'; break;
				case 4 : key_data = '9'; break;
			}  

			//key *,0,#
			PADR = 0x0e;
			cf = P6DR;
			cf = ~cf;
			cf &= 0x07;
			switch(cf) {
				case 1 : key_data = '*'; break;
				case 2 : key_data = '0'; break;
				case 4 : key_data = '#'; break;
			}  

			//key 1,2,3
			PADR = 0x07; // PA3 = L
			cf = P6DR;   // �ǡ�������
			cf = ~cf;    // cf��ȿž
			cf &= 0x07;  // P60,1,2�Τ߸���
			switch(cf) {
				case 1 : key_data = '1'; break;
				case 2 : key_data = '2'; break;
				case 4 : key_data = '3'; break;
			} 
		}
  }

  /* ���Ϥ��줿�����ξ�����֤� */
  return key_data;
}

void sample_replay(int mode)
     /* Ͽ���ޤ��Ϻ�����Ԥ��ؿ� */
     /*   mode: PLAY, SAMPLE     */
{
  if (mode == INVERSE){                    /* �����⡼�ɤν��� */
    /* �����˥��ԡ����򥹥ԡ����Ȥ��ƻ��Ѥ���̿��򵭽Ҥ��� */
    speaker_switch(SPEAKER);

   lcd_cursor(0,0);
	 lcd_printstr(" Push * or 5 key");
	 lcd_cursor(0,1);
	 lcd_printstr(" Now Inverse... ");
  }
  if (mode == SAMPLE){                  /* Ͽ���⡼�ɤν��� */
    /* �����˥��ԡ�����ޥ����Ȥ��ƻ��Ѥ���̿��򵭽Ҥ���   */
    speaker_switch(MIC);
    
		lcd_cursor(0,0);
		lcd_printstr(" Push * or 5 key");
		lcd_cursor(0,1);
    lcd_printstr(" Now Sampling...");
  }
  bufptr = 0;               /* �Хåե��ݥ��󥿤����� */
  timer_start(0);           /* ����ץ�󥰥�����(����ͥ�0)�Υ������� */
  ENINT();                  /* CPU�����ߵ��� */
  while (bufptr < (TIME));
                            /* �Хåե������դˤʤ�ޤǼ¹� */
  speaker_switch(MIC);      /* ���ԡ��������� */
  timer_stop(0);            /* �����ޤΥ��ȥå� */
}

#pragma interrupt
void int_imia0(void)
     /* Ͽ���������ѤΥ����޳����ߥϥ�ɥ�         */
     /* �ץ쥤�⡼�ɤˤ�äƥǡ����γ�Ǽ�����Ϥ�Ԥ� */
{
  if (play_mode == SAMPLE){      
    /* ������Ͽ���ΤȤ��ν����򵭽Ҥ���(�ʲ��Υ����Ȥ򻲾ȤΤ���) */
		ad_start( 0, 0);              /* A/D�Ѵ���������           */
		while(ADSTATUS() == 0);		    /* A/D�Ѵ���λ�ޤ��Ԥ� ��5us */
		databuf[bufptr] = ADREAD();   /* �Ѵ��ǡ������Ǽ          */
  }
	if (play_mode == INVERSE){
		da_out( 0, databuf[TIME - bufptr]);
	}
  bufptr++;                      /* �Хåե��ݥ��󥿤� +1           */
  timer_intflag_reset(0);        /* ������0�γ����ߥե饰�򥯥ꥢ */
  ENINT();                       /* CPU������ߵ��ľ��֤�         */
}
