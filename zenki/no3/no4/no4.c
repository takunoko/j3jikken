#include "h8-3052-iodef.h"

#include "lcd.h"

#define MS_SLEEP 17500

void sleep_ms(int);
void print_ch(char , int );

int main(void)
{
	unsigned char cf, key_data;

	P9DDR = 0x30;  /* $B%]!<%H(B9$B$N=i4|2=(B(P95-P94$B$r=PNO$K@_Dj(B) */

	P6DDR &= ~0x07;  /* P60,1,2   $BF~NO(B */
	PADDR |= 0x0f;   /* PA0,1,2,3 $B=PNO(B */

	//$B:G=i$K>CEt$7$F$*$/(B
	P9DR = 0x30;  /* D1($B@V(B)$B>CEt(B, D2($BNP(B)$B>CEt(B */
	
	//$BI=<($9$k:BI8(B
	int x=0;
	char old_key_data = 0;

	int type=0;

	lcd_init();

	while(1) {
		key_data = 0;

		//key 1,2,3
		PADR = 0x07; // PA3 = L
		cf = P6DR;   // $B%G!<%?F~NO(B
		cf = ~cf;    // cf$B$NH?E>(B
		cf &= 0x07;  // P60,1,2$B$N$_8+$k(B
		switch(cf) {
			case 1 : key_data = 'a'; break;
			case 2 : key_data = 'b'; break;
			case 4 : key_data = 'c'; break;
		}  

		//key 4,5,6
		PADR = 0x0b;
		cf = P6DR;
		cf = ~cf;
		cf &= 0x07;
		switch(cf) {
			case 1 : key_data = 'd'; break;
			case 2 : key_data = 'e'; break;
			case 4 : key_data = 'f'; break;
		}  

		//key 7,8,9
		PADR = 0x0d;
		cf = P6DR;
		cf = ~cf;
		cf &= 0x07;
		switch(cf) {
			case 1 : key_data = 'g'; break;
			case 2 : key_data = 'h'; break;
			case 4 : key_data = 'i'; break;
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

		//$B%A%c%?%j%s%0KI;_(B
		if(key_data != 0 && old_key_data != key_data){
			sleep_ms(10);
			old_key_data = key_data;
			
			if(key_data == '0'){
				type = (type+1)%3;
			}else if(key_data == '#'){
				// '#' $B2hLL$HF~NO%b!<%I=i4|2=(B
				lcd_init();
				x=0;
				type = 0;
			}else if(key_data == '*'){
				// '*' $B%9%Z!<%9F~NO(B
				print_ch( ' ', x);
				x++;
			}else if(key_data == 'i' && type == 2){
			}else{
				print_ch( key_data + type*9, x);
				x++;
			}
		}
		if(key_data == 0){
			old_key_data = 0;
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
