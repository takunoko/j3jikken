#include "h8-3052-iodef.h"

#define MS_SLEEP 16000

void sleep_ms(int);

int main(void)
{
  P9DDR = 0x30;  /* �|�[�g9�̏�����(P94--P95���o�͂ɐݒ�) */

  while(1)
  {
		//�Ԃ�_������1�b�҂�
		P9DR = 0x20;
		sleep_ms(1000);
		//�΂�_������1�b�҂�
		P9DR = 0x10;
		sleep_ms(1000);
  }
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}
