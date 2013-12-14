#include "h8-3052-iodef.h"
#include "lcd.h"

#include <string.h>

#define MS_SLEEP 17500

void sleep_ms(int);

//文字列strをx,yの位置から表示していく。
//折り返し機能付き
//戻り値は最後の文字の位置
int draw_str_re(char str[], int ,int);

void move_print(char str[], int x, int y, int chk, int wt){
	int x2=0;

	//左側スクロール
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
			//文字列の先頭が一番左端にきたら
			x=16;
			if(y==0){
				y=1;
			}else{
				y=0;
			}
		}
	}else{
		//右側スクロール
		while(1){
			for(; x<16; x++){
				draw_str_re( str, x, y);

				sleep_ms(wt);
				lcd_cursor(x,y);
				lcd_printch(' ');
			}
			x=0;
			//文字列の先頭が一番端にきたら
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

	//一文字ずつ表示していく
	for(j=0; str[j]!='\0'; j++, x2++){
		if(x2<16){
			lcd_cursor(x2,y);
		}
		//もし、文字列が右端を越えてしまったら
		//左側に戻す
		else{
			if(y==0){
				lcd_cursor(x2-16,1);
			}else{
				lcd_cursor(x2-16,0);
			}
		}
		lcd_printch(str[j]);
	}
	//戻り値として、最後の文字の位置を返す
	return x2-1;
}

int main(void)
{
	char str[] = "Test";

	lcd_init();
	//move_print( 文字列, x, y, 0:左 1:右, 待ち時間[ms]);
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
