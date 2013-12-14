#include "h8-3052-iodef.h"

/* ��������å��դΤȤ���1us�������GRA�� */
#define TCONST1us 25
#define CLKDIV1MAX 2621
#define CLKDIV2MAX 5242
#define CLKDIV4MAX 10485
#define CLKDIV8MAX 20971

int timer_set(int ch, unsigned int time_us);
void timer_start(int ch);
void timer_stop(int ch);
void timer_init(void);
void timer_intflag_reset(int ch);

int timer_set(int ch, unsigned int time_us)
     /* �������ͥ�Υ����ޤ������ֳִ֤ǳ��������ꤹ��ؿ� */
     /* ch:0-4, time_us:1-20971 ���ϰϤǤʤ�������ư��ʤ�     */
     /* ��=25MHz �ΤȤ�, ��/1 : 2621.4 us   ��/2 : 5242.8 us     */
     /* ����λ�������� ��/4 : 10485.6 us  ��/8 : 20971.2 us    */
     /* ch = x (x = 0-4) �ΤȤ� int_imiax() �����椬�ܤ�         */
     /* CPU���Τγ����ߵ��Ĥ�Ф��ʤ����ư���ʤ�              */
     /* �����: ���꤬Ŭ���ʤȤ���1��Ŭ���Ǥʤ��Ȥ��� -1         */
     /* ���: ���ꤷ�������ޤ���ߤ���Τ����ӥ������Ȥ����뤳�� */
{
  unsigned long tcr_addr,tsr_addr,tior_addr,tier_addr;
  unsigned long grah_addr,gral_addr,tcnth_addr,tcntl_addr;
  unsigned int gra,rf;
  unsigned char dmy,clk_div,chmask;

  switch (ch){
  case 1:
    tcr_addr = 0xffff6e;   tior_addr = 0xffff6f;
    tsr_addr = 0xffff71;   tier_addr = 0xffff70;
    tcnth_addr = 0xffff72; tcntl_addr = 0xffff73;
    grah_addr = 0xffff74;  gral_addr = 0xffff75;
    break;
  case 2:
    tcr_addr = 0xffff78;   tior_addr = 0xffff79;
    tsr_addr = 0xffff7b;   tier_addr = 0xffff7a;
    tcnth_addr = 0xffff7c; tcntl_addr = 0xffff7d;
    grah_addr = 0xffff7e;  gral_addr = 0xffff7f;
    break;
  case 3:
    tcr_addr = 0xffff82;   tior_addr = 0xffff83;
    tsr_addr = 0xffff85;   tier_addr = 0xffff84;
    tcnth_addr = 0xffff86; tcntl_addr = 0xffff87;
    grah_addr = 0xffff88;  gral_addr = 0xffff89;
    break;
  case 4:
    tcr_addr = 0xffff92;   tior_addr = 0xffff93;
    tsr_addr = 0xffff95;   tier_addr = 0xffff94;
    tcnth_addr = 0xffff96; tcntl_addr = 0xffff97;
    grah_addr = 0xffff98;  gral_addr = 0xffff99;
    break;
  case 0:
  default:
    ch = 0;
    tcr_addr = 0xffff64;   tior_addr = 0xffff65;
    tsr_addr = 0xffff67;   tier_addr = 0xffff66;
    tcnth_addr = 0xffff68; tcntl_addr = 0xffff69;
    grah_addr = 0xffff6a;  gral_addr = 0xffff6b;
    break;
  }
  clk_div = 0;
  if (time_us > 0) rf = 1;
  else rf = -1;
  if (time_us > CLKDIV1MAX) clk_div = 1; /* �� = ��/2 */
  if (time_us > CLKDIV2MAX) clk_div = 2; /* �� = ��/4 */
  if (time_us > CLKDIV4MAX) clk_div = 3; /* �� = ��/8 */
  if (time_us > CLKDIV8MAX) rf = -1;
  /* ���ꤹ�륿���ޤ�ư���ߤ�� */
  chmask = 1;
  chmask = ~(chmask << ch);
  TSTR = TSTR & chmask;
  /* TCNT(������)�� 0 �˥ꥻ�å� */
  *((volatile unsigned char *)tcnth_addr) = 0;
  *((volatile unsigned char *)tcntl_addr) = 0;
  /* GRA����ڥ��ޥå����ꥢ, ��������å���(��ư����) */
  *((volatile unsigned char *)tcr_addr) = 0xa0 | (clk_div & 0x02);
  /* GRA�ϥ����ȥץåȥ���ڥ��쥸���� */
  *((volatile unsigned char *)tior_addr)
    = (*((volatile unsigned char *)tior_addr) & 0xf0) | 0x08;
  /* TSR�Υե饰��ꥻ�å� */
  dmy = *((volatile unsigned char *)tsr_addr);
  *((volatile unsigned char *)tsr_addr) = 0xf8;
  /* GRA=TCNT�ΤȤ��γ����ߵ��� */
  *((volatile unsigned char *)tier_addr) = 0xf9;
  /* ���ꤵ�줿���ֳִ֤ˤʤ�褦��GRA�򥻥å� */
  gra = (unsigned int)(time_us * TCONST1us / (1 << clk_div));
  *((volatile unsigned char *)gral_addr) = gra & 0xff;
  *((volatile unsigned char *)grah_addr) = (gra >> 8) & 0xff;
  return rf;
}

void timer_start(int ch)
     /* �������ͥ�Υ�����ư��򳫻Ϥ���ؿ�                    */
     /* �������ͥ���ϰ� ch: 0-4                                */
     /* CPU�γ����ߵ��Ĥ�Ԥ�ʤ��ȳ����ߤ�ȯ�����ʤ��Τ���� */
{
  unsigned char chmask;

  if ((ch < 0) || (ch > 4)) ch = 0;
  chmask = 1;
  chmask = chmask << ch;
  TSTR = TSTR | chmask;
}

void timer_stop(int ch)
     /* �������ͥ�Υ�����ư�����ߤ���ؿ�                    */
     /* �������ͥ���ϰ� ch: 0-4                                */
{
  unsigned char chmask;

  if ((ch < 0) || (ch > 4)) ch = 0;
  chmask = 1;
  chmask = ~(chmask << ch);
  TSTR = TSTR & chmask;
}

void timer_init(void)
     /* 16�ӥåȥ����ޤν������Ԥ��ؿ�                 */
     /* �����ޤ���Ѥ���Ȥ��ˤ�, �ǽ��ɬ���ƤӽФ����� */
{
  TSNC = 0xe0; /* ����ͥ�0-4 ������Ωư�� */
  TMDR = 0x80; /* ����ͥ�0-4 �����̾�ư��⡼�� */
  TFCR = 0xc0; /* ����ͥ�3,4 ���̾�ư�� */
  TOER = 0xc0; /* ����ͥ�3,4 ��ü�ҽ��Ϥ�ػ� */
  TOCR = 0xff; /* �̾�ư��Ǥ������̣�ʤ�������ͤ����� */
}

void timer_intflag_reset(int ch)
     /* �������ͥ�Υ����ޤγ����ߥե饰�Υꥻ�åȤ�Ԥ��ؿ�   */
     /* �������ͥ���ϰ� ch: 0-4                                 */
     /* �����ߥϥ�ɥ���γ����ߤ���Ĥ�������ɬ���ƤӽФ����� */
{
  unsigned char dmy;

  switch (ch){
  case  1: dmy = TSR1; TSR1 = 0xf8; break; /* ������1�ν��� */
  case  2: dmy = TSR2; TSR2 = 0xf8; break; /* ������2�ν��� */
  case  3: dmy = TSR3; TSR3 = 0xf8; break; /* ������3�ν��� */
  case  4: dmy = TSR4; TSR4 = 0xf8; break; /* ������4�ν��� */
  case  0:
  default: dmy = TSR0; TSR0 = 0xf8;        /* ������0�ν��� */
  }
}
