#include "h8-3052-iodef.h"

#define MS_SLEEP 175

void sleep_ms(int);


int main(void)
{
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

	int i=0;
	while(1){	
		//どちらも点灯
		P9DR = 0x00;
		sleep_ms(i/50);
		//緑だけ点灯
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
