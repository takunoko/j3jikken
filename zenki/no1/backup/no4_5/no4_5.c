#include "h8-3052-iodef.h"

#define MS_SLEEP 17500

void sleep_ms(int);


int main(void)
{
  P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */

	int i=0;
	//Ŭ���ʴֳ֤��Ф��֤��ڤ��ؤ���
	while(1){	
		//�п��Υƥ���
		if(i<200){
			P9DR = 0x20;
			sleep_ms(15);
			P9DR = 0x30;
			sleep_ms(15);
		}//�ֿ��Υƥ���
		else{
			P9DR = 0x10;
			sleep_ms(13);
			P9DR = 0x30;
			sleep_ms(13);
		}
		i++;
		if(i>400)	i=0;
	}
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
