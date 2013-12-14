#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"

#include "lcd.h"

/* �����ߤμ��� 1000us */
#define INT1MS 1000
#define MS_SLEEP 17500

/* �����߽�����ɬ�פ��ѿ�������ѿ��ˤȤ� */
/* volatile �ϥץ�����ή��Ȥ�̵�ط����Ѳ������ѿ���ɬ���Ĥ��� */
volatile unsigned int sys_time;

/* �����ߥϥ�ɥ�Υץ�ȥ�������� */
void int_imia0(void);

//
void sec_str(int ,char *);
void print_lcd(char *, int, int);
void sleep_ms(int);

int main(void)
{
	/* unsigned int �ˤ�����ͤ���������ե������Ȥ������ˤʤäƤ��ޤ� */
  unsigned int sec_time; /* 1s�� +1 ������ѿ������ */
	int status = 0;

	unsigned char cf, key_data, old_key_data; /* �������Ϥ˻��Ѥ����ѿ� */

	char str[9] = {'\0'}; /* ɽ������ʸ���� */

  ROMEMU(); /* ROM���ߥ�졼������ON (�����߻��ѻ�ɬ��) */

  sys_time = 0; sec_time = 0; /* ���֤��Ǽ�����ѿ��ν���� */

  /* LED����³����Ƥ���ݡ��Ȥν�����򤳤��˽� (�¸�1����) */
  P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */

	/* �������� */
	P6DDR &= ~0x07;  /* P60,1,2   ���� */
	PADDR |= 0x0f;   /* PA0,1,2,3 ���� */

  lcd_init();
	P9DR = 0x30;	/* LED��Ȥꤢ�����ä��Ƥ��� */
	
  timer_init();        /* �����ޤ�������˽�������� */
  timer_set(0,INT1MS); /* ������0��1ms�ֳ֤�ư������ */
  timer_start(0);      /* ������(����ͥ�0)��������  */

  ENINT();             /* CPU�����ߵ��� */

	/* �Ȥꤢ�����ǽ�˽���� */
	sec_str( sec_time, str);
	print_lcd( str,0,0);
	old_key_data = 0;

  while (1) {
    /* ������ư��ʳ��Ϥ���̵�¥롼�פ�¹Ԥ��Ƥ��� */
		key_data = 0;

		{
			//key 1,2,3
			PADR = 0x07; // PA3 = L
			cf = P6DR;   // �ǡ�������
			cf = ~cf;    // cf��ȿž
			cf &= 0x07;  // P60,1,2�Τ߸���
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

		//���㥿����ɻ�
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
	    /* ������ sec_time �ι��� ( +1 ����) ��� */
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
  return 1; /* main���������ͤϥ��顼��٥��ɽ�� 0:���ｪλ */
            /* �ʵץ롼�פγ��ʤΤ�,��ä��鲿����������       */
}

#pragma interrupt
void int_imia0(void)
     /* ������0�γ����ߥϥ�ɥ�                                   */
     /*   ������0����������׵᤬����Ȥ��δؿ����ƤӽФ����     */
     /* �ؿ���̾���ϥ�����0�γ����ߤϤ���̾���ȷ�ޤäƤ���       */
     /* �ؿ���ľ���˳����ߥϥ�ɥ����� #pragma interrupt ��ɬ�� */
{
  /* �����ߥϥ�ɥ�ν������ڤ��ʤ�褦����θ���뤳�� */
  /* ���ǤǤ�������Ϥ����ˤϽ񤫤ʤ� */

  /* sys_time �ι��� ( +1 ����) �򤳤��˽� */
	sys_time++;

  /* �Ƥӥ����޳����ߤ���Ѥ��뤿���ɬ�פ����      */
  /*   ������0�γ����ߥե饰�򥯥ꥢ���ʤ��Ȥ����ʤ� */
  timer_intflag_reset(0);

  ENINT();       /* CPU������ߵ��ľ��֤� */
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

//lcd�˻��ꤷ�����֤���ɽ��
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
