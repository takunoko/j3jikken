#include "h8-3052-iodef.h"
#include "lcd.h"

#include <string.h>

#define MS_SLEEP 17500

void sleep_ms(int);

//$BJ8;zNs(Bstr$B$r(Bx,y$B$N0LCV$+$iI=<($7$F$$$/!#(B
//$B@^$jJV$75!G=IU$-(B
//$BLa$jCM$O:G8e$NJ8;z$N0LCV(B
int draw_str_re(char str[], int ,int);

void move_print(char str[], int x, int y, int chk, int wt){
	int x2=0;

	//$B:8B&%9%/%m!<%k(B
	if(chk == 0){
		while(1){
			for(; x > 0; x--){
				x2 = draw_str_re( str, x, y);

				sleep_ms(wt);
				if(x2<16){
					lcd_cursor(x2,y);
				}else{
					if(y==0){
						lcd_cursor(x2-16,1);
					}else{
						lcd_cursor(x2-16,0);
					}
				}	
				lcd_printch(' ');
			}
			//$BJ8;zNs$N@hF,$,0lHV:8C<$K$-$?$i(B
			x=16;
			if(y==0){
				y=1;
			}else{
				y=0;
			}
		}
	}else{
		//$B1&B&%9%/%m!<%k(B
		while(1){
			for(; x<16; x++){
				draw_str_re( str, x, y);

				sleep_ms(wt);
				lcd_cursor(x,y);
				lcd_printch(' ');
			}
			x=0;
			//$BJ8;zNs$N@hF,$,0lHVC<$K$-$?$i(B
			if(y==0){
				y=1;
			}else{
				y=0;
			}
		}
	}
}

int draw_str_re(char str[], int x2, int y){
	int j;

	//$B0lJ8;z$:$DI=<($7$F$$$/(B
	for(j=0; str[j]!='\0'; j++, x2++){
		if(x2<16){
			lcd_cursor(x2,y);
		}
		//$B$b$7!"J8;zNs$,1&C<$r1[$($F$7$^$C$?$i(B
		//$B:8B&$KLa$9(B
		else{
			if(y==0){
				lcd_cursor(x2-16,1);
			}else{
				lcd_cursor(x2-16,0);
			}
		}
		lcd_printch(str[j]);
	}
	//$BLa$jCM$H$7$F!":G8e$NJ8;z$N0LCV$rJV$9(B
	return x2-1;
}

int main(void)
{
	char str[] = "Test";

	lcd_init();
	//move_print( $BJ8;zNs(B, x, y, 0:$B:8(B 1:$B1&(B, $BBT$A;~4V(B[ms]);
	move_print( str, 5, 1, 0, 1000);

	return 0;
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
