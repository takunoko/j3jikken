#include "h8-3052-iodef.h"

#define MS_SLEEP 175

void sleep_ms(int);


int main(void)
{
  P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */

	int i=0;
	while(1){	
		//�ɤ��������
		P9DR = 0x00;
		sleep_ms(i/50);
		//�Ф�������
		P9DR = 0x10;
		sleep_ms(90);
			
		i++;
		if(i>2000)	i=0;
	}
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}