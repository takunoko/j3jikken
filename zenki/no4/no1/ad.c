#include "h8-3052-iodef.h"

void ad_init();
void ad_start(unsigned char ch, unsigned char int_sw);

void ad_init()
     /* A/D �Ѵ����Ȥ�����ν�����ؿ� */
     /* ñ�쥹�����Τ��б�             */
{
  unsigned char dmy;

  ADCR = 0x7e;  /* �����ȥꥬ�Ѵ����Ϥζػ� */
  dmy = ADCSR;  /* �Ѵ���λ�ե饰���ꥢ�Τ���Υ��ߡ��꡼�� */
  ADCSR = 0x08; /* ñ�쥹�����, �����߶ػ�, A/D�Ѵ����, */
                /* 134���ơ����Ѵ�����, ����ͥ� 0 ����     */
}

void ad_start(unsigned char ch, unsigned char int_sw)
     /* A/D�Ѵ��򥹥����Ȥ�����ؿ�                                */
     /* ch:���ϥ���ͥ��ֹ�(0-7), int_sw:�Ѵ���λ�����ߵ���(0,1) */
     /* �����ߵ��Ĥξ��, ���ӳ����ߥϥ�ɥ餬ɬ��             */
     /* �ޤ�, CPU������ߵ��ľ��֤ˤ��ʤ��ȳ����ߤ�ȯ�����ʤ�  */
     /* �����߽����ˤϿ�us�λ��֤������뤳�Ȥ��θ���뤳��       */
{
  if (int_sw != 0) int_sw = 0x40;
  else int_sw = 0;
  ADCSR = (ADCSR & 0xd8) | (ch & 0x07);   /* �Ѵ����, ����ͥ�ν񤭴��� */
  ADCSR = (ADCSR & 0x1f) | 0x20 | int_sw; /* ����ɥե饰���ꥢ, �Ѵ����� */
}
