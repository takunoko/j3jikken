#include "h8-3052-iodef.h"

//������Τ�MS_SLEEP���ͤ��ѹ�
#define MS_SLEEP 17500

void sleep_ms(int);

int main(void)
{
  P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */

  while(1)
	{
		P9DR = 0x20;
		sleep_ms(1000);
		P9DR = 0x10;
		sleep_ms(1000);
	}
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
