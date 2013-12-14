#include "h8-3052-iodef.h"
#include "lcd.h"

#include <string.h>

#define MS_SLEEP 17500

void sleep_ms(int);

void move_print(char str[], int x, int y){
	int j;
	int x2;


	//$BJ8;zNs$r(B0,0$B$+$i%9%?!<%H(B
	x=0;
	y=0;

	int str_len = strlen(str);

	while(1){
		for(; x<16; x++){
			x2=x;
			//$B0lJ8;z$:$DI=<($7$F$$$/(B
			for(j=0; str[j]!='\0'; j++){
				if(x2<16){
					lcd_cursor(x2,y);
					lcd_printch(str[j]);
				}
				x2++;
			}
			sleep_ms(1000);
			lcd_cursor(x,y);
			lcd_printch(' ');
		}
		//x=-str_len;
		x=0;
	}
}

int main(void)
{
  lcd_init();
	
	char str[] = "Test";

	//move_print($BJ8;zNs(B,x,y);
	move_print(str,5,1);

	return 0;
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
