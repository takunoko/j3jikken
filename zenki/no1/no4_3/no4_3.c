#include "h8-3052-iodef.h"

//より正確にMS_SLEEPの値を変更
#define MS_SLEEP 17500

void sleep_ms(int);

int main(void)
{
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

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
