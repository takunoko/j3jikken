#include "h8-3052-iodef.h"
/* #include "h8-3052-int.h" */
#include "lcd.h"
#include "ad.h"
#include "da.h"

#define BUFSIZE       30 /* �Хåե����礭��(kB) */
#define SAMPLE         0 /* ư������(Ͽ��)       */
#define PLAY           1 /* ư������(����)       */
#define NOSELECT      -1 /* ư��������(������)   */
#define TIME      120000 /* Ͽ��/��������        */

#define MS_SLEEP 17500	/* sleep�δ�� */

volatile unsigned char databuf[(unsigned long)BUFSIZE * 1024];
volatile unsigned long bufptr;
volatile int play_mode;

int            main(void);
unsigned char  menu(void);
void           sample_replay(int mode);

void sleep_ms(int);
	
int main(void)
{
  /* �������Ͼ����������뤿����ѿ���������� */
  unsigned char key_data;

  lcd_init();    /* LCD �ν����            */
  ad_init();     /* A/D �Ѵ���ν����      */
  da_init();     /* D/A �Ѵ���ν����      */

  /* �������˥������ϼ����Τ���Υݡ��Ȥν�����򵭽Ҥ��� */

	/* �ɵ�	*/
	P6DDR &= ~0x07;  /* P60,1,2   ���� */
	PADDR |= 0x0f;   /* PA0,1,2,3 ���� */
	/* �����ޤ� */

  while (1) {
    play_mode = NOSELECT;
    key_data = menu();                    /* ��˥塼������   */
    /* Ͽ�������������줿��SAMPLE, ���������������줿��PLAY   */
    /* ��play_mode�˳�Ǽ��������򵭽Ҥ���                    */
		
		/*�ɵ�*/
		if(key_data == '*')
			play_mode = SAMPLE;
		if(key_data == '#')
			play_mode = PLAY;
		/*�����ޤ�*/
    
    
    /* ��*�������Ϥ���Ƥ����Ͽ��/�����δؿ���ƤӽФ������򵭽Ҥ���  */
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
  lcd_printstr("Rec:[*] Play:[#]");
  lcd_cursor(0,1);
  lcd_printstr(" Push * or # key");

  /* ��������Ƚ�����ѿ��ν���� */
  cf = 0;
  key_data = 0;


	char old_data=0;

  while (cf == 0 ){  /* �������Ϥ���ޤǥ롼�פ��� */
    /* �����˥������Ϥν����򵭽Ҥ��� */

		/* ���������ɵ� */
		key_data = 0;

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

		//���㥿����ɻ�
		if(key_data != 0 && old_data != key_data){
			sleep_ms(10);
			old_data = key_data;
		}
		if(key_data == 0){
			old_data = 0;
			sleep_ms(10);
		}

		/* �����ޤ��ɵ� */
	  
    /* ��key *,# �Τߤ����Ϥ��б�����������򵭽Ҥ��� */

		/*�ɵ�*/
		if(key_data == '*' || key_data == '#')
			cf = 1;
		/*�����ޤ�*/
  }

  /* ���Ϥ��줿�����ξ�����֤� */
  return key_data;
}

void sample_replay(int mode)
     /* Ͽ���ޤ��Ϻ�����Ԥ��ؿ� */
     /*   mode: PLAY, SAMPLE     */
{
   bufptr = 0;                             /* �Хåե��ݥ��󥿤�����  */
  if (mode == PLAY){                                /* �����⡼�ɤν��� */
    /* �����˥��ԡ����򥹥ԡ����Ȥ��ƻ��Ѥ���̿�� */
    speaker_switch(SPEAKER);
    lcd_cursor(0,1);
    lcd_printstr(" Now playing... ");
    
    /* �������Ͻ������Ƥ򵭽Ҥ��� */
    while(bufptr <= TIME){                 /*   �ǡ������Ϥ򷫤��֤�    */
			da_out( 0, databuf[bufptr]);         /* ���ġ����˥ǡ��������    */
			bufptr++;                            /* ���Хåե��ݥ��󥿤� +1   */
    }   
  }
  if (mode == SAMPLE){                              /* Ͽ���⡼�ɤν��� */
    /* �����˥��ԡ�����ޥ����Ȥ��ƻ��Ѥ���̿�� */
    speaker_switch(MIC);
    lcd_cursor(0,1);
    lcd_printstr(" Now Sampling...");
    
    /* ��������������Ƥ򵭽Ҥ��� */
    while(bufptr <= TIME){              /*   �ǡ����ɹ��򷫤��֤�     */
			ad_start( 0, 0);                  /* ���������Ѵ���������       */
			while(ADSTATUS() == 0);					  /* ���������Ѵ���λ�Ԥ� ��5us */
			databuf[bufptr] = ADREAD();		    /* ���Ѵ��ǡ������Ǽ�� ������*/
			bufptr++;												  /* ���Хåե��ݥ��󥿤� +1    */
    }
  }
  speaker_switch(MIC);      /* ���ԡ���������   */
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}