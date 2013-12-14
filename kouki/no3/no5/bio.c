#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "lcd.h"
#include "ad.h"

#define  HANTEILEVEL 60 /* �����ͤ��礭����Ƚ�꤬�Ť��ʤ�  */

int            main(void);
unsigned char  key_read(void);
void           level_ck(unsigned short);
void           ad_data_get_3ch(void);
char           hikaku_3ch(void);

unsigned short touroku_ad3, touroku_ad4, touroku_ad5, hikaku_ad3, hikaku_ad4, hikaku_ad5;

int main(void)
{
  /* �������Ͼ����������뤿����ѿ���������� */
  unsigned char cf, key_data;

  lcd_init();    /* LCD �ν����            */
  ad_init();     /* A/D �Ѵ���ν����      */

  /* �������ϼ����Τ���Υݡ��Ȥν���� */
  P6DDR &= ~0x07;     /* P60,1,2   ���� */
  PADDR |= 0x0f;      /* PA0,1,2,3 ���� */

  PBDDR = 0xff; /* �Х�����ȥꥯ���ѥݡ������� */
  PBDR  = 0x00; /* ���ݡ���OFF                  */
  P9DDR = 0xff; /* ���ϥݡ��Ȥ�����             */

  while (1) {

    P9DR  = 0x30; /* LED OFF */

    /* ��Ͽ�Ѥλؤ����Ϥ�¥����å�������ɽ�����뵭�Ҥ��   */

    /* �Х�����ȥꥯ�����Ϥ˴ؤ���ݡ��Ȥ����ݡ��Ȥ�ON�ˤ��� */
    /* �ؤ��֤����Τ򸡽Ф��뵭�Ҥ�񤯡�                   */
    /* �ؤ��֤����ޤǤϥ롼�פ���褦�ˤ��뤬��level_ck()   */
    /* ���ɤ�����Ŭ�ڤʵ��Ҥ򤹤뤳��                         */

    P9DR = 0x10;   /* ��LED ON */

    /* AD�Ѵ���ˤ��3chʬ�Υǡ���������൭�Ҥ��        */
    /* Ŭ�ڤʴؿ��λ��Ѥˤ��¸������                       */

    /* ��Ͽ�ѥǡ���������줿���Ȥ򼨤���å�������ɽ�����뵭�Ҥ�� */
    /* [*]���������Ϥ�¥����å�������ɽ�����뵭�Ҥ��              */
   

    /* ���������Ԥ����֤���(�������Ϥ����ޤǥ롼�פ�ȴ���ʤ�)     */
    /* key_read()���Ѥ��Ƶ��Ҥ���                                     */
    
    P9DR  = 0x30; /* LED OFF */

    /* ����Ѥλؤ����Ϥ�¥����å�������ɽ�����뵭�Ҥ��   */

    /* �Х�����ȥꥯ�����Ϥ˴ؤ���ݡ��Ȥ����ݡ��Ȥ�ON�ˤ��� */
    /* �ؤ��֤����Τ򸡽Ф��뵭�Ҥ�񤯡�                   */
    /* �ؤ��֤����ޤǤϥ롼�פ���褦�ˤ��뤬��level_ck()   */
    /* ���ɤ�����Ŭ�ڤʵ��Ҥ򤹤뤳��                         */

    P9DR  = 0x20;  /* �ֿ�LED ON */

    /* AD�Ѵ���ˤ��3chʬ������ѥǡ���������൭�Ҥ��  */
    /* Ŭ�ڤʴؿ��λ��Ѥˤ��¸�����뤬����ӷ�̤��֤���   */
    /* ��������դ��뤳��                                     */ 

    /* �֤��줿Ƚ���̤˱����ơ�ǧ�ڤ��줿���ݤ��򼨤�       */
    /* ��å�������ɽ�����뵭�Ҥ��                         */              
    
    /* [*]���������Ϥ�¥����å�������ɽ�����뵭�Ҥ��      */

    /* �Х�����ȥꥯ�����Ϥ˴ؤ���ݡ��Ȥ����ݡ��Ȥ�OFF��    */
    /* ���뵭�Ҥ��                                         */

    /* ���٥��������Ԥ����֤���(�������Ϥ����ޤǥ롼�פ�ȴ���ʤ�) */
    /* key_read()���Ѥ��Ƶ��Ҥ���                                     */
 
  }
  return 1;
}

void level_ck(unsigned short level_data)
     /* �ؤ��֤��줿���ɤ����򸡽Ф���ؿ� */
     /* �ؤ��֤����ޤǥ롼�פ���         */
     /* ����ϰ����Ȥ���204��Ϳ���뤳��    */
{
  unsigned short data;

  data = 0;

  while (data < level_data)
    {
      ADCSR = 0x04;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRAH;
      data <<= 8;
      data += ADDRAL;
      data >>= 6;
    }
}

void ad_data_get_3ch(void)
     /* �Х�����ȥꥯ����ʬ���б�����AD�Ѵ���� */
     /* �Ѥ���3����ͥ�ʬ�Υǡ����������ؿ�  */
     /* ��Ͽ�ѥǡ�������¸�����                 */
{
  unsigned short data;

      ADCSR = 0x03;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRDH;
      data <<= 8;
      data += ADDRDL;
      data >>= 6;

      touroku_ad3 = data;

      ADCSR = 0x04;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRAH;
      data <<= 8;
      data += ADDRAL;
      data >>= 6;

      touroku_ad4 = data;

      ADCSR = 0x05;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRBH;
      data <<= 8;
      data += ADDRBL;
      data >>= 6;

      touroku_ad5 = data;
}

char hikaku_3ch(void)
     /* �Х�����ȥꥯ����ʬ���б�����AD�Ѵ����     */
     /* �Ѥ���3����ͥ�ʬ�Υǡ���������ࡥ        */
     /* ����ѥǡ�������¸�������餫����������Ƥ��� */
     /* ��Ͽ�ѥǡ����Ȥ���Ӥ�Ԥ�Ƚ���̤��֤��ؿ� */
{
   unsigned short data, up_ad3, up_ad4, up_ad5, down_ad3, down_ad4, down_ad5;
   char hantei;

      ADCSR = 0x03;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRDH;
      data <<= 8;
      data += ADDRDL;
      data >>= 6;

      hikaku_ad3 = data;

      ADCSR = 0x04;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRAH;
      data <<= 8;
      data += ADDRAL;
      data >>= 6;

      hikaku_ad4 = data;

      ADCSR = 0x05;
      ADCSR |= 0x20;
      while ((ADCSR & 0x80) == 0);

      ADCSR &= 0x7f;
      data = ADDRBH;
      data <<= 8;
      data += ADDRBL;
      data >>= 6;

      hikaku_ad5 = data;

      hantei = 0;

      if (touroku_ad3 + HANTEILEVEL > 0x3ff) { 
	up_ad3 = 0x3ff;
      } else {
	up_ad3 = touroku_ad3 + HANTEILEVEL;
      }

      if (touroku_ad3 - HANTEILEVEL < 0x00) {
	down_ad3 = 0;
      } else {
	down_ad3 = touroku_ad3 - HANTEILEVEL;
      }

      if (touroku_ad4 + HANTEILEVEL > 0x3ff) { 
	up_ad4 = 0x3ff;
      } else {
	up_ad4 = touroku_ad4 + HANTEILEVEL;
      }

      if (touroku_ad4 - HANTEILEVEL < 0x00) {
	down_ad4 = 0;
      } else {
	down_ad4 = touroku_ad4 - HANTEILEVEL;
      }

      if (touroku_ad5 + HANTEILEVEL > 0x3ff) { 
	up_ad5 = 0x3ff;
      } else {
	up_ad5 = touroku_ad5 + HANTEILEVEL;
      }

      if (touroku_ad5 - HANTEILEVEL < 0x00) {
	down_ad5 = 0;
      } else {
	down_ad5 = touroku_ad5 - HANTEILEVEL;
      }

      if (hikaku_ad3 <= up_ad3 && down_ad3 <= hikaku_ad3) {
	 if (hikaku_ad4 <= up_ad4 && down_ad4 <= hikaku_ad4) {
	    if (hikaku_ad5 <= up_ad5 && down_ad5 <= hikaku_ad5) {
	      hantei = 1;
	    }
	 }
      }

      return hantei;
}

unsigned char  key_read(void)
    /* �������Ͼ��֤��������ؿ� */
{
  /* �������ϼ����Τ�����ѿ���������� */
  unsigned char cf, key_data;

  /* ��������Ƚ�����ѿ��ν����*/
  cf = 0;
  key_data = 0;

  while (cf == 0 ){  /* �������Ϥ���ޤǥ롼�פ��� */
    PADR = 0x0e;
    cf   = P6DR;
    cf   = ~cf;
    cf  &= 0x07;
    switch(cf) {
      case 1: key_data = '*'; break;
    }
  }

  /* ���Ϥ��줿�����ξ�����֤� */
  return key_data;
}
