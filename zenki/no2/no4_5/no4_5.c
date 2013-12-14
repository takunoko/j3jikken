#include "h8-3052-iodef.h"
#include "lcd.h"

#include <string.h>

#define MS_SLEEP 17500

void sleep_ms(int);

//右に揃えて表示
void draw_num(int num){
	int x;
	int keta;
	//一文字ずつ表示していく
	keta=1, x=15;
	do{
		lcd_cursor(x,0);
		if(keta > 3){
			lcd_printch(',');
			keta=0;
		}else{
			lcd_printch(num%10+'0');
			num /= 10;
		}
		x--,	keta++;
	}while(num != 0);
	
}


int main(void)
{
	int num = 0;

	lcd_init();

	draw_num(num);

	return 0;
}
