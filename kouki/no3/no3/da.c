#include "h8-3052-iodef.h"

#define MIC     0
#define SPEAKER 1

void da_init();
void da_out(unsigned char ch, unsigned char val);
void da_stop(unsigned char ch);
void speaker_switch(int mode);

void da_init()
     /* D/A �Ѵ��ȥ��ԡ������ؤ��ν�����򤹤�ؿ� */
{
  P9DR = P9DR | 0x10;   
  P9DDR = P9DDR | 0x10; /* �ե���MOS�����ѤΥݡ��� P94 ��������� */
  DACR = 0x1f;          /* D/A�Ѵ����϶ػ�                        */ 
}

void da_out(unsigned char ch, unsigned char val)
     /* D/A�Ѵ�����Ϥ��뤿��δؿ�                      */
     /*   ch: ����ͥ����(0, 1)  val: ������(8�ӥå�Ĺ) */
     /*   ���Ϥ���ȶ��Ѥ��Ƥ���ü�Ҥ� D/A �����Ȥ��ʤ�  */
     /*   DA0: P76, AN6  DA1: P77, AN7 �Ȥ��줾�춦��    */
{
  if (ch == 0){
    DADR0 = val;
    DACR = DACR | 0x40;
  } else {
    DADR1 = val;
    DACR = DACR | 0x80;
  }
}

void da_stop(unsigned char ch)
     /* D/A�Ѵ�����ߤ��뤿��δؿ�                    */
     /*   ��ߤ���ȶ��Ѥ��Ƥ���ü�Ҥ�¾�����Ӥ˻��Ѳ� */
     /*   DA0: P76, AN6  DA1: P77, AN7 �Ȥ��줾�춦��  */
{
  if (ch == 0) DACR = DACR & 0xbf;       /* DA0 ����� */
  else DACR = DACR & 0x7f;               /* DA1 ����� */
}

void speaker_switch(int mode)
     /* ���ԡ����ε�ǽ�����򤹤뤿��δؿ� */
     /*   mode: SPEAKER, MIC               */
{
  if (mode == SPEAKER) P9DR = P9DR & 0xef; /* �ե���MOS��ON (D/A 0 ����³) */
  else P9DR = P9DR | 0x10;                 /* �ե���MOS��OFF               */
}
