#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"

#include "lcd.h"

/* 割り込みの周期 1000us */
#define INT1MS 100

/* sleep_ms に使う */
#define MS_SLEEP 17500

/* P9DR */
#define HIGH 0x30
#define LOW 0x20

int duty;

/* 割り込み処理に必要な変数は大域変数にとる */
/* volatile はプログラムの流れとは無関係に変化する変数に必ずつける */
volatile unsigned int sys_time;

/* 割り込みハンドラのプロトタイプ宣言 */
void int_imia0(void);

void sleep_ms(int);

int main(void)
{
	unsigned char cf, key_data, old_key_data; /* キー入力に使用する変数 */

	/* duty 0-100 */

	ROMEMU(); /* ROMエミュレーションをON (割り込み使用時必須) */

	sys_time = 0; /* 時間を格納する変数の初期化 */

	/* LEDの接続されているポートの初期化をここに書く (実験1参照) */
	P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

	/* キー入力 */
	P6DDR &= ~0x07;  /* P60,1,2   入力 */
	PADDR |= 0x0f;   /* PA0,1,2,3 出力 */

	lcd_init();

	/* 消灯 */
	P9DR = 0x30;

	timer_init();        /* タイマを使用前に初期化する */
	timer_set(0,INT1MS); /* タイマ0を1ms間隔で動作設定 */
	timer_start(0);      /* タイマ(チャネル0)スタート  */

	ENINT();             /* CPU割り込み許可 */

	/* dutyはデフォルトで80%に設定しておく */
	duty = 8;
	old_key_data = 0;

	while (1) {
		/* 割り込み動作以外はこの無限ループを実行している */

		/* キー入力 */
		{
			key_data = 0;

			//key 1,2,3
			PADR = 0x07; // PA3 = L
			cf = P6DR;   // データ入力
			cf = ~cf;    // cfの反転
			cf &= 0x07;  // P60,1,2のみ見る
			switch(cf) {
				case 1 : key_data = '1'; break;
				case 2 : key_data = '2'; break;
				case 4 : key_data = '3'; break;
			}  

			//key 4,5,6
			PADR = 0x0b;
			cf = P6DR;
			cf = ~cf;
			cf &= 0x07;
			switch(cf) {
				case 1 : key_data = '4'; break;
				case 2 : key_data = '5'; break;
				case 4 : key_data = '6'; break;
			}  

			//key 7,8,9
			//PADR = 0x0b; /* This is a mistake code. */
			PADR = 0x0d;
			cf = P6DR;
			cf = ~cf;
			cf &= 0x07;
			switch(cf) {
				case 1 : key_data = '7'; break;
				case 2 : key_data = '8'; break;
				case 4 : key_data = '9'; break;
			}  

			//key *,0,#
			PADR = 0x0e;
			cf = P6DR;
			cf = ~cf;
			cf &= 0x07;
			switch(cf) {
				case 1 : key_data = '*'; break;
				case 2 : key_data = '0'; break;
				case 4 : key_data = '#'; break;
			}  
		}

		//チャタリング防止
		if(key_data != 0 && old_key_data != key_data){
			sleep_ms(1);
			old_key_data = key_data;

			if(key_data >= '0' && key_data <= '9'){
				duty = key_data - '0';
			}else if(key_data == '*'){
				duty = 10;
			}
		}

		if(key_data == 0){
			old_key_data = 0;
			sleep_ms(1);
		}
	}

	return 1; 
	/* mainからの戻り値はエラーレベルを表す 0:正常終了 */
	/* 永久ループの外なので,戻ったら何かおかしい       */
}

#pragma interrupt
void int_imia0(void)
	/* タイマ0の割り込みハンドラ                                   */
	/*   タイマ0から割り込み要求がくるとこの関数が呼び出される     */
	/* 関数の名前はタイマ0の割り込みはこの名前と決まっている       */
	/* 関数の直前に割り込みハンドラ指定の #pragma interrupt が必要 */
{
	/* 割り込みハンドラの処理が軽くなるように配慮すること */
	/* 外でできる処理はここには書かない */

	/* sys_time の更新 ( +1 する) をここに書く */
	sys_time++;

	/* 再びタイマ割り込みを使用するために必要な操作      */
	/*   タイマ0の割り込みフラグをクリアしないといけない */
	timer_intflag_reset(0);

	if(duty >= sys_time){
		P9DR = HIGH;
	}else{
		P9DR = LOW;
	}
	if(sys_time >= 10){
		sys_time = 0;
	}

	ENINT();       /* CPUを割り込み許可状態に */
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
