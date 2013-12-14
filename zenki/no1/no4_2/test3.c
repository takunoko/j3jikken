#include "h8-3052-iodef.h"

#define MS_SLEEP 16000

void sleep_ms(int);

int main(void)
{
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

  while(1)
  {
		//赤を点灯して1秒待つ
		P9DR = 0x20;
		sleep_ms(1000);
		//緑を点灯して1秒待つ
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
