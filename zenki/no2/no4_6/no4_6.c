#include "h8-3052-iodef.h"
#include "lcd.h"

#include <string.h>

#define MS_SLEEP 17500

void sleep_ms(int);

void pri_cal( int, int, int);
int int_leng( int);
void draw_num( int, int);

int draw_num_p( int, int);
int pri_en( int, int);


int calc( int, int, int);


int main(void)
{
	lcd_init();
	
	int a = 34531;
	int b = 131;
	int enzan = 1; /* +:0 -:1 *:2 /:3 */

	pri_cal( a, b, enzan);

	return 0;
}

//x���ܤ���','��Ϥ��ߤʤ���ʸ����ɽ�����Ƥ���
int draw_num_p(int num, int x){
	//�������','�ο�����Ƥ���������˰�ư�������֤���ɽ�����Ƥ���
	int keta = int_leng(num);	
	int ten = keta/3;
	draw_num( num, keta+ten+x);
	
	return x+keta+ten+1;
}

//��������
int int_leng(int num){
	int i;
	if(num==0){
		return 0;
	}
	for(i=0; num != 0;i++){
		num /= 10;
	}	
	return i-1;
}

//x���麸¦�˸����ä�ɽ��
void draw_num(int num, int x){
	int keta=1;
	do{		
		if(x < 16)
			lcd_cursor(x,0);
		else
			lcd_cursor(x-16,1);

		if(keta > 3){
			lcd_printch(',');
			keta=0;
		}else{
			lcd_printch(num%10+'0');
			num /= 10;
		}
		keta++, x--;
	}while(num != 0);
}

//�黻�Ҥ�ɽ������ͤ�x�κ�ɸ
int pri_en(int enzan, int x){
	if(x < 16)
		lcd_cursor( x, 0);
	else
		lcd_cursor( x-16, 1);

	char ch=' ';
	/* +:0 -:1 *:2 /:3 */
	switch (enzan){
		case 0 :	ch = '+';	break;
		case 1 :	ch = '-';	break;
		case 2 :	ch = '*';	break;
		case 3 :	ch = '/'; break;
		case 4 :	ch = '='; break;
		default:
				break;
	}
	lcd_printch(ch);
		
	return x+1;
}

//�׻������ͤ��֤��ؿ�
int calc(int a, int b, int enzan){
	int re=0;
	/* +:0 -:1 *:2 /:3 */
	switch (enzan){
		case 0 :	re = a + b;	break;
		case 1 :	re = a - b;	break;
		case 2 :	re = a * b;	break;
		case 3 :	re = a / b; break;
		case 4 :	re = 0; break;
		default:
				break;
	}
	return re;
}

//�����Τ�ɽ������ؿ�
void pri_cal(int a,int b,int enzan){
	int x=0;
	x = draw_num_p( a, x);
	x = pri_en( enzan, x);
	x = draw_num_p( b, x);
	x = pri_en( 4, x);
	x = draw_num_p( calc( a, b, enzan), x);
}
