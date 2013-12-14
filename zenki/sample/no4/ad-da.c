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

volatile unsigned char databuf[(unsigned long)BUFSIZE * 1024];
volatile unsigned long bufptr;
volatile int play_mode;

int            main(void);
unsigned char  menu(void);
void           sample_replay(int mode);

int main(void)
{
  /* �������Ͼ����������뤿����ѿ���������� */
  unsigned char key_data;

  lcd_init();    /* LCD �ν����            */
  ad_init();     /* A/D �Ѵ���ν����      */
  da_init();     /* D/A �Ѵ���ν����      */

  /* �������˥������ϼ����Τ���Υݡ��Ȥν�����򵭽Ҥ��� */
                          /* P60,1,2   ���� */
                          /* PA0,1,2,3 ���� */

  while (1) {
    play_mode = NOSELECT;
    key_data = menu();                    /* ��˥塼������   */
    /* Ͽ�������������줿��SAMPLE, ���������������줿��PLAY   */
    /* ��play_mode�˳�Ǽ��������򵭽Ҥ���                    */
    
    
    
    
    /* ��*�������Ϥ���Ƥ����Ͽ��/�����δؿ���ƤӽФ������򵭽Ҥ���  */



    
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

  while (cf == 0 ){  /* �������Ϥ���ޤǥ롼�פ��� */
    /* �����˥������Ϥν����򵭽Ҥ��� */


	  
    /* ��key *,# �Τߤ����Ϥ��б�����������򵭽Ҥ��� */
    
    
     
     
    }
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
    while(bufptr <= TIME){           i     /*   �ǡ������Ϥ򷫤��֤�    */
                                           /* ���ġ����˥ǡ��������    */
                                           /* ���Хåե��ݥ��󥿤� +1   */
    }   
  }
  if (mode == SAMPLE){                              /* Ͽ���⡼�ɤν��� */
    /* �����˥��ԡ�����ޥ����Ȥ��ƻ��Ѥ���̿�� */
    speaker_switch(MIC);
    lcd_cursor(0,1);
    lcd_printstr(" Now Sampling...");
    
    /* ��������������Ƥ򵭽Ҥ��� */
    while(bufptr <= TIME){                 /*   �ǡ����ɹ��򷫤��֤�     */
                                           /* ���������Ѵ���������       */
                                           /* ���������Ѵ���λ�Ԥ� ��5us */
                                           /* ���Ѵ��ǡ������Ǽ�� ������*/
                                           /* ���Хåե��ݥ��󥿤� +1    */
    }
  }
  speaker_switch(MIC);      /* ���ԡ���������   */
}

