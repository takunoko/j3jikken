#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"

#include "lcd.h"

/* 割り込みの周期 1000us */
#define INT1MS 1000
#define MS_SLEEP 17500

/* 割り込み処理に必要な変数は大域変数にとる */
/* volatile はプログラムの流れとは無関係に変化する変数に必ずつける */
volatile unsigned int sys_time;

/* 割り込みハンドラのプロトタイプ宣言 */
void int_imia0(void);

//
void sec_str(int ,char *);
void print_lcd(char *, int, int);
void sleep_ms(int);

int main(void)
{
	/* unsigned int にすると値がアンダーフローしたときに正になってしまう */
  unsigned int sec_time; /* 1sに +1 される変数を確保 */
	int status = 0;

	unsigned char cf, key_data, old_key_data; /* キー入力に使用する変数 */

	char str[9] = {'\0'}; /* 表示する文字列 */

  ROMEMU(); /* ROMエミュレーションをON (割り込み使用時必須) */

  sys_time = 0; sec_time = 0; /* 時間を格納する変数の初期化 */

  /* LEDの接続されているポートの初期化をここに書く (実験1参照) */
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

	/* キー入力 */
	P6DDR &= ~0x07;  /* P60,1,2   入力 */
	PADDR |= 0x0f;   /* PA0,1,2,3 出力 */

  lcd_init();
	P9DR = 0x30;	/* LEDをとりあえず消しておく */
	
  timer_init();        /* タイマを使用前に初期化する */
  timer_set(0,INT1MS); /* タイマ0を1ms間隔で動作設定 */
  timer_start(0);      /* タイマ(チャネル0)スタート  */

  ENINT();             /* CPU割り込み許可 */

	/* とりあえず最初に初期化 */
	sec_str( sec_time, str);
	print_lcd( str,0,0);
	old_key_data = 0;

  while (1) {
    /* 割り込み動作以外はこの無限ループを実行している */
		key_data = 0;

		{
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
		
			switch(key_data){
				case '*'	:
					status = 0;
					break;
				case '#'	:
					status = 1;
					sys_time = 0;
					break;

				case '1'	:
					if(status == 0){
						sec_time += 3600;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				case '7'	:
					if(status == 0){
						sec_time -= 3600;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				case '2'	:
					if(status == 0){
						sec_time += 60;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				case '8'	:
					if(status == 0){
						sec_time -= 60;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				case '3'	:
					if(status == 0){
						sec_time += 1;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				case '9'	:
					if(status == 0){
						sec_time -= 1;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				case '0'	:
					if(status == 0){
						sec_time = 0;
						sec_str( sec_time, str);
						print_lcd( str,0,0);
					}
					break;
				default :
					break;
			}
		}

		if(key_data == 0){
			old_key_data = 0;
			sleep_ms(1);
		}
	    /* ここに sec_time の更新 ( +1 する) を書く */
		if(status == 1){
			if(sys_time == 1000){
				sec_time++;
				sys_time = 0;
				//sec_time = sys_time;
				sec_str( sec_time, str);
				print_lcd( str,0,0);

			}
		}
  }
  return 1; /* mainからの戻り値はエラーレベルを表す 0:正常終了 */
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

  ENINT();       /* CPUを割り込み許可状態に */
}

void sec_str(int time, char str[]){
	unsigned int num = time;

	str[0] = '0';
	str[1] = '0';
	str[2] = '0';
	str[3] = '0';
	str[4] = '0';
	str[5] = '0';
	str[6] = '0';
	str[7] = '0';
	str[8] = '0';
	str[9] = '0';
	str[10] = '0';
	str[11] = '0';
	str[12] = '0';
	str[13] = '0';
	str[14] = '\0';

	int hour = num / 3600;
	num = num % 3600;
	int min = num / 60;
	num = num % 60;
	int sec = num;

	str[0] = hour / 10000000+'0';
	hour = hour - (hour / 10000000)*10000000;
	str[1] = hour / 1000000+'0';
	hour = hour - (hour / 1000000)*1000000;
	str[2] = hour / 100000+'0';
	hour = hour - (hour / 100000)*100000;
	str[3] = hour / 10000+'0';
	hour = hour - (hour / 10000)*10000;
	str[4] = hour / 1000+'0';
	hour = hour - (hour / 1000)*1000;
	str[5] = hour / 100+'0';
	hour = hour - (hour / 100)*100;
	str[6] = hour / 10+'0';
	str[7] = hour % 10+'0';

	str[8] = ':';
	str[9] = min / 10+'0';
	str[10] = min % 10+'0';
	str[11] = ':';
	str[12] = sec / 10+'0';
	str[13] = sec % 10+'0';

}

//lcdに指定した位置から表示
void print_lcd(char str[], int x, int y){
	int i;
	for(i=0; str[i]!='\0' && i<32; i++){
		if(x<16){
			lcd_cursor(x,y);
			lcd_printch(str[i]);
			x++;
		}else{
			x=0;
			if(y==0){
				y=1;
			}else{
				y=0;
			}
			i--;
		}
	}
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
