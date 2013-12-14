#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"

#include "lcd.h"

/* �����ߤμ��� 1000us */
#define INT1MS 1000

/* �����߽�����ɬ�פ��ѿ�������ѿ��ˤȤ� */
/* volatile �ϥץ�����ή��Ȥ�̵�ط����Ѳ������ѿ���ɬ���Ĥ��� */
volatile unsigned int sys_time;

/* �����ߥϥ�ɥ�Υץ�ȥ�������� */
void int_imia0(void);

//
void int_str(int ,char *);
void print_lcd(char *, int, int);

int main(void)
{
  unsigned int sec_time; /* 1����� +1 ������ѿ������ */

	char str[3] = {'\0'}; /* ɽ������ʸ���� */

  ROMEMU(); /* ROM���ߥ�졼������ON (�����߻��ѻ�ɬ��) */

  sys_time = 0; sec_time = 0; /* ���֤��Ǽ�����ѿ��ν���� */

  /* LED����³����Ƥ���ݡ��Ȥν�����򤳤��˽� (�¸�1����) */
  P9DDR = 0x30;  /* �ݡ���9�ν����(P94--P95����Ϥ�����) */
	P9DR = 0x30;	/* LED��Ȥꤢ�����ä��Ƥ��� */

  lcd_init();
	
  timer_init();        /* �����ޤ�������˽�������� */
  timer_set(0,INT1MS); /* ������0��1ms�ֳ֤�ư������ */
  timer_start(0);      /* ������(����ͥ�0)��������  */

  ENINT();             /* CPU�����ߵ��� */

  while (1) {
    /* ������ư��ʳ��Ϥ���̵�¥롼�פ�¹Ԥ��Ƥ��� */

    /* ������ sec_time �ι��� ( +1 ����) ��� */
		if(sys_time == 1000){
			sec_time++;
			sys_time = 0;
			int_str( sec_time, str);
			print_lcd( str,0,0);
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

void int_str(int num, char str[]){
	int i;

	str[0] = '0';
	str[1] = '0';
	str[2] = '\0';

	for(i=1; num != 0; i--){
		str[i] = num%10+'0';
		num = num/10;
	}
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
