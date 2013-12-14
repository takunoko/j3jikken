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
#define NOSELECT      -1 /* ư��������(̤����) */

volatile unsigned char databuf[(unsigned long)BUFSIZE * 1024];
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
                                      /* P60,1,2   ���� */
                                      /* PA0,1,2,3 ���� */

  while (1) {
    play_mode = NOSELECT;
    key_data = menu();                    /* ��˥塼������ */
    /* Ͽ�������������줿��SAMPLE�����������������줿��PLAY */
    /* ��play_mode�˳�Ǽ��������򵭽Ҥ���                  */
   


    /* �������Ϥ���Ƥ����Ͽ��/�����δؿ���ƤӽФ������򵭽Ҥ��� */



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

  /* ��������Ƚ�����ѿ��ν����*/
  cf = 0;
  key_data = 0;

  while (cf == 0 ){  /* �������Ϥ���ޤǥ롼�פ��� */
    /* �����˥������Ϥν����򵭽Ҥ��� */
    

  }

  /* ���Ϥ��줿�����ξ�����֤� */
  return key_data;
}

void sample_replay(int mode)
     /* Ͽ���ޤ��Ϻ�����Ԥ��ؿ� */
     /*   mode: PLAY, SAMPLE     */
{
  if (mode == PLAY){                    /* �����⡼�ɤν��� */
    /* �����˥��ԡ����򥹥ԡ����Ȥ��ƻ��Ѥ���̿��򵭽Ҥ��� */

    lcd_cursor(0,1);
    lcd_printstr(" Now playing... ");
  }
  if (mode == SAMPLE){                  /* Ͽ���⡼�ɤν��� */
    /* �����˥��ԡ�����ޥ����Ȥ��ƻ��Ѥ���̿��򵭽Ҥ���   */
    
    lcd_cursor(0,1);
    lcd_printstr(" Now Sampling...");
  }
  bufptr = 0;               /* �Хåե��ݥ��󥿤����� */
  timer_start(0);           /* ����ץ�󥰥�����(����ͥ�0)�Υ������� */
  ENINT();                  /* CPU�����ߵ��� */
  while (bufptr < ((unsigned long)BUFSIZE * 1024));
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
                                       /* A/D�Ѵ���������           */
                                       /* A/D�Ѵ���λ�ޤ��Ԥ� ��5us */
                                       /* �Ѵ��ǡ������Ǽ          */
  }
  if (play_mode == PLAY){        
    /* �����˺����ΤȤ��ν����򵭽Ҥ���(�ʲ��Υ����Ȥ򻲾ȤΤ���) */
                                       /* D/A�˥ǡ��������         */
  }
  bufptr++;                      /* �Хåե��ݥ��󥿤� +1           */
  timer_intflag_reset(0);        /* ������0�γ����ߥե饰�򥯥ꥢ */
  ENINT();                       /* CPU������ߵ��ľ��֤�         */
}
