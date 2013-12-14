#include <string.h>
#include "h8-3052-iodef.h"

#define TIMECONST 500
#define TCONST40us 100*6
#define TCONST1ms 2500*10
#define LCD_RS 0x40
#define LCD_RW 0x20
#define LCD_E 0x10

void lcd_init(void);
void lcd_cursor(int x, int y);
void lcd_clear(void);
void lcd_printstr(unsigned char *str);
void lcd_printch(unsigned char ch);
void lcd_putch(unsigned char ch, unsigned char rs);
void wait1ms(int ms);

void lcd_init(void)
     /* LCD ɽ�����Ȥ�����ν�����ؿ�             */
     /* ����, �������󥹤Ȥη�͹礤�����뤬�к��Ѥ� */
     /* LCD ɽ����ν�����ˤϻ��֤�������Τ����   */
{
  wait1ms(15);
  PADR = 0x0f;       /* PA0-3 ��0�����ƥ���, PA4-6 ��1�����ƥ��� */
  PADDR = 0x7f;      /* PA4-6 �Ͻ��Ϥ�����(LCD���� E,R/W,RS) */
                     /* PA0-3 �ϥ����ܡ��ɥޥȥꥯ���ν����� */
  P4DR = 0;          /* LCD �ǡ��� */
  P4DDR = 0xff;      /* P40-7 ���ƽ��Ϥ�����(LCD DB0-7) */
  lcd_putch(0x3f,0); /* �ǡ���ž����(8�ӥå�) */
  wait1ms(5);
  lcd_putch(0x3f,0);
  wait1ms(100);
  lcd_putch(0x3f,0);
  lcd_putch(0x3f,0); /* �ǡ���ž����8�ӥå�, 2�饤��, 5x10�ɥå� */
  lcd_putch(0x04,0); /* �ǥ����ץ쥤ON/OFF����(OFF) */
  lcd_putch(0x01,0); /* �ǥ����ץ쥤�����ꥢ */
  wait1ms(2);        /* �����Ԥ� > 1.64ms */
  lcd_putch(0x06,0); /* ����ȥ꡼�⡼�ɥ��å� Inc. without Disp.shift */
  lcd_putch(0x0c,0); /* �ǥ����ץ쥤ON/OFF����(ON) */
  lcd_putch(0x80,0); /* DDRAM���ɥ쥹���å� */
  wait1ms(100);
}

void lcd_cursor(int x, int y)
     /* ɽ�����֤��ѹ�����ؿ� */
     /* ɽ���ﺸ�夬 (0,0) �Ȥʤ� */
{
  char adr;

  if ((x < 16) && (y < 4)) {
    switch (y) {
    case 1: adr = 0xc0; break; /* 2���ܤ���Ƭ */
    case 2: adr = 0x94; break; /* 4��LCD(SC2004C, L2034)�ʤɤ�3���ܤ���Ƭ */
    case 3: adr = 0xd4; break; /* 4��LCD(SC2004C, L2034)�ʤɤ�4���ܤ���Ƭ */
    default: adr = 0x80;       /* 1���ܤ���Ƭ */
    }
    lcd_putch(adr+x,0);
  }
}

void lcd_clear(void)
     /* ɽ����������̤򥯥ꥢ���뤿��δؿ� */
{
  lcd_putch(0x01,0); /* �ǥ����ץ쥤�����ꥢ */
  wait1ms(2);        /* �����Ԥ� > 1.64ms */
}

void lcd_printstr(unsigned char *str)
     /* ɽ�����ʸ�����ɽ������ؿ� */
     /* ʸ�������ɤ� ASCII �����ɤ��ϰϤʤ�����ʤ� */
{
  int l, i;

  l = strlen(str);
  for (i = 0; i < l; i++) lcd_printch(str[i]);
}

void lcd_printch(unsigned char ch)
     /* ɽ�����1ʸ������ɽ������ؿ� */
     /* ʸ�������ɤ� ASCII �����ɤ��ϰϤʤ�����ʤ� */
{
  lcd_putch(ch,1);  /* ����饯����1ʸ��ž�� */
}

void lcd_putch(unsigned char ch, unsigned char rs)
     /* LCD �˥��ޥ�ɤ�ǡ��������뤿��δؿ�   */
     /* ch �˥��ޥ�ɤޤ��ϥǡ����������        */
     /* rs �� 0 �ΤȤ����ޥ��, 1 �ΤȤ��ϥǡ��� */
     /* �̾�, �桼������ľ�ܸƤӽФ����ȤϤʤ�   */
{
  int i;
  unsigned char st13,st2,key;

  rs = rs << 6;
  st13 = LCD_RS & rs;
  st2 = st13 | LCD_E;
  key = PADR & 0x0f;   /* PA0-4 �ϥ����ޥȥꥯ���ǻ���      */
  st13 = st13 | key;   /* PA5-6 ��LCD������������, ����¦�� */
  st2 = st2 | key;     /* �ͤ��˲����ʤ��褦�ˤ���          */
  PADR = st13;      /* �쥸���������Ԥ� */
  PADR = st2;       /* E����� 1 �ˤ��� */
  P4DR = ch;        /* �ǡ����ޤ��ϥ��ޥ�ɤ����� */
  PADR = st13;      /* E����� 0 �ˤ��� */
  for (i = 0; i < TCONST40us; i++); /* 40us �Ԥ�(LCD�ν�������) */
}

void wait1ms(int ms)
     /* ms = 1 �ΤȤ�, ��1ms��������ʥ롼�פ��ԤĴؿ�            */
     /* LCD��ư����ݾڤ��뤿���ɬ�פʻ��֤���ݤ���Τ���Ū     */
     /* ���δ�, CPU�����ꤹ��Τ���դ�, ¾�����Ӥ˻��Ѥ��ʤ����� */
{
  int i,j;

  for (i = 0; i < ms; i++){
    for (j = 0; j < TCONST1ms; j++);
  }
}
