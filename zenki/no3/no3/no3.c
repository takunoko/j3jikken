#include "h8-3052-iodef.h"

#include "lcd.h"

#define MS_SLEEP 17500

void sleep_ms(int);
void print_ch(char , int );

int main(void)
{
	unsigned char cf, key_data;

	lcd_init();

	P9DDR = 0x30;  /* ポート9の初期化(P95-P94を出力に設定) */

	P6DDR &= ~0x07;  /* P60,1,2   入力 */
	PADDR |= 0x0f;   /* PA0,1,2,3 出力 */

	//最初に消灯しておく
	P9DR = 0x30;  /* D1(赤)消灯, D2(緑)消灯 */
	
	//表示する座標
	int x=0;
	char old_data = 0;

	while(1) {
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

		//チャタリング防止
		if(key_data != 0 && old_data != key_data){
			sleep_ms(10);
			old_data = key_data;

			print_ch( key_data, x);
			x++;
		}
		if(key_data == 0){
			old_data = 0;
			sleep_ms(10);
		}
	}
}

void print_ch(char c, int x){
	if(x<16){
		lcd_cursor(x,0);
	}else if(x<32){
		lcd_cursor(x-16,1);
	}else{}
	lcd_printch(c);
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
