#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"

#include "lcd.h"

/* �����ߤμ��� 1000us */
#define INT1MS 100

/* sleep_ms �˻Ȥ� */
#define MS_SLEEP 17500

/* P9DR */
#define HIGH 0x30
#define LOW 0x20

int duty;

/* �����߽�����ɬ�פ��ѿ�������ѿ��ˤȤ� */
/* volatile �ϥץ�����ή��Ȥ�̵�ط����Ѳ������ѿ���ɬ���Ĥ��� */
volatile unsigned int sys_time;

/* �����ߥϥ�ɥ�Υץ�ȥ�������� */
void int_imia0(void);

void sleep_ms(int);

int main(void)
{
	unsigned char cf, key_data, old_key_data; /* �������Ϥ˻��Ѥ����ѿ� */

	/* duty 0-100 */

	ROMEMU(); /* ROM���ߥ�졼������ON (�����߻��ѻ�ɬ��) */

	sys_time = 0; /* ���֤��Ǽ�����ѿ��ν���� */

	/* LED����³����Ƥ���ݡ��Ȥν�����򤳤��˽� (�¸�1����) */
	P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */

	/* �������� */
	P6DDR &= ~0x07;  /* P60,1,2   ���� */
	PADDR |= 0x0f;   /* PA0,1,2,3 ���� */

	lcd_init();

	/* ���� */
	P9DR = 0x30;

	timer_init();        /* �����ޤ�������˽�������� */
	timer_set(0,INT1MS); /* ������0��1ms�ֳ֤�ư������ */
	timer_start(0);      /* ������(����ͥ�0)��������  */

	ENINT();             /* CPU�����ߵ��� */

	/* duty�ϥǥե���Ȥ�80%�����ꤷ�Ƥ��� */
	duty = 8;
	old_key_data = 0;

	while (1) {
		/* ������ư��ʳ��Ϥ���̵�¥롼�פ�¹Ԥ��Ƥ��� */

		/* �������� */
		{
			key_data = 0;

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
	/* main���������ͤϥ��顼��٥��ɽ�� 0:���ｪλ */
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

	if(duty >= sys_time){
		P9DR = HIGH;
	}else{
		P9DR = LOW;
	}
	if(sys_time >= 10){
		sys_time = 0;
	}

	ENINT();       /* CPU������ߵ��ľ��֤� */
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
