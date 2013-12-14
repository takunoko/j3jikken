#include "h8-3052-iodef.h"

#define MS_SLEEP 17500

void sleep_ms(int);


int main(void)
{
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

	int i=0;
	//適当な間隔で緑と赤を切り替える
	while(1){	
		//緑色のテスト
		if(i<200){
			P9DR = 0x20;
			sleep_ms(15);
			P9DR = 0x30;
			sleep_ms(15);
		}//赤色のテスト
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
