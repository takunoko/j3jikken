#include "h8-3052-iodef.h"

#define MS_SLEEP 16000

void sleep_ms(int);

int main(void)
{
  P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */

  while(1)
  {
		//�֤���������1���Ԥ�
		P9DR = 0x20;
		sleep_ms(1000);
		//�Ф���������1���Ԥ�
		P9DR = 0x10;
		sleep_ms(1000);
  }
}

//��������(ms)�������꡼��
void sleep_ms(int ms){
	int i, i2;

	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
