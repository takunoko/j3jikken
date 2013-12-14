#include "h8-3052-iodef.h"
/* #include "h8-3052-int.h" */
#include "lcd.h"
#include "ad.h"
#include "da.h"
/* #include "limits.h" */

#define BUFSIZE       30 /* バッファの大きさ(kB) */
#define SAMPLE         0 /* 動作選択(録音)       */
#define PLAY           1 /* 動作選択(再生)       */
#define INVERSE        2 /* 動作選択(逆再生)     */
#define NOSELECT      -1 /* 動作選択値(末選択)   */
#define TIME      120000 /* 録音/再生時間        */

#define MS_SLEEP 17500	/* sleepの基準 */

volatile unsigned char databuf[(unsigned long)BUFSIZE * 1024];
volatile unsigned long bufptr;
volatile int play_mode;

unsigned char oto[] = { 
125,
150,
175,
198,
217,
233,
243,
250,
249,
243,
233,
217,
198,
175,
150,
125,
99,
74,
51,
32,
16,
6,
0,
0,
6,
16,
32,
51,
74,
99,
125,
}

int            main(void);
unsigned char  menu(void);
void           sample_replay(int mode);

void           onkai(void);

void sleep_ms(int);

// 音階
int timer=TIME/8;
unsigned char doremi=0;

int main(void)
{
  /* キー入力情報を取得するための変数を宣言する */
  unsigned char key_data;

  lcd_init();    /* LCD の初期化            */
  ad_init();     /* A/D 変換器の初期化      */
  da_init();     /* D/A 変換器の初期化      */

  /* ◎ここにキー入力取得のためのポートの初期化を記述する */

	/* 追記	*/
	P6DDR &= ~0x07;  /* P60,1,2   入力 */
	PADDR |= 0x0f;   /* PA0,1,2,3 出力 */
	/* ここまで */

  while (1) {
    play_mode = NOSELECT;
    key_data = menu();                    /* メニューを選ぶ   */
    /* 録音キーが押されたらSAMPLE, 再生キーが押されたらPLAY   */
    /* をplay_modeに格納する処理を記述する                    */
		
		/*追記*/
		if(key_data == '*'){
			play_mode = SAMPLE;
		}
		if(key_data == '5'){
			play_mode = INVERSE;
		}	
		if(key_data == '#'){
			play_mode = PLAY;
		}
		/*ここまで*/
    
    
    /* ◎*キー入力されていれば録音/再生の関数を呼び出す処理を記述する  */
		sample_replay(play_mode);	
    
  }
  return 1;
}

unsigned char  menu(void)
     /* LCD にメニューを書いて動作を選択するための関数 */
     /* 戻り値は入力キー情報                           */
{
  /* キー入力取得のための変数を宣言する */
  unsigned char cf, key_data;

  lcd_cursor(0,0);                   /* LCD にメッセージ表示 */
  lcd_printstr("Rec:[*] Play:[#]");
  lcd_cursor(0,1);
  lcd_printstr(" Push * or # key");

  /* キー入力判定用変数の初期化 */
  cf = 0;
  key_data = 0;


	char old_data=0;

  while (cf == 0 ){  /* キー入力するまでループする */
    /* ここにキー入力の処理を記述する */

		/* ここから追記 */
		key_data = 0;

		//key 1,2,3
		PADR = 0x07; // PA3 = L
		cf = P6DR;   // データ入力
		cf = ~cf;    // cfの反転
		cf &= 0x07;  // P60,1,2のみ見る

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

		//チャタリング防止
		if(key_data != 0 && old_data != key_data){
			sleep_ms(10);
			old_data = key_data;
		}
		if(key_data == 0){
			old_data = 0;
			sleep_ms(10);
		}

		/* ここまで追記 */
	  
    /* ◎key *,# のみの入力に対応させる処理を記述する */

		/*追記*/
		if(key_data == '*' || key_data == '5' || key_data == '#')
			cf = 1;
		/*ここまで*/
  }

  /* 入力されたキーの情報を返す */
  return key_data;
}
void sample_replay(int mode)
     /* 録音または再生を行う関数 */
     /*   mode: PLAY, SAMPLE     */
{
   bufptr = 0;                             /* バッファポインタを初期化  */
	 if (mode == PLAY){                      /* 再生モードの処理 */
    /* ここにスピーカをスピーカとして使用する命令 */
    speaker_switch(SPEAKER);
    lcd_init();
		lcd_cursor(0,0);
		lcd_printstr(" Push * or # key");
		lcd_cursor(0,1);
		lcd_printstr(" Now Playing... ");
		
    /* 音声出力処理内容を記述する */
    while(bufptr <= TIME){                 /*   データ出力を繰り返す    */
			da_out( 0, databuf[bufptr]);    /* ◎Ｄ／Ａにデータを出力    */
			bufptr++;                            /* ◎バッファポインタを +1   */
    }   
  }
  if (mode == INVERSE){                    /* 再生モードの処理 */
    /* ここにスピーカをスピーカとして使用する命令 */
    speaker_switch(SPEAKER);
    lcd_init();
		lcd_cursor(0,0);
		lcd_printstr(" Push * or 5 key");
		lcd_cursor(0,1);
		lcd_printstr(" Now Inverse... ");
		
    /* 音声出力処理内容を記述する */
    while(bufptr <= TIME){                 /*   データ出力を繰り返す    */
			da_out( 0, databuf[TIME-bufptr]);    /* ◎Ｄ／Ａにデータを出力    */
			bufptr++;                            /* ◎バッファポインタを +1   */
    }   
  }
  if (mode == SAMPLE){                           
		onkai();
	}
}

void sleep_ms(int ms){
	int i,i2;
	for(i=0; i<ms; i++){
		for(i2=0; i2<MS_SLEEP; i2++){
		}
	}
}

void onkai(void){
	bufptr = 0;                         /* バッファポインタを初期化  */
	while(bufptr <= TIME){              /*   データ読込を繰り返す     */
		//databuf[bufptr] = doremi;	  	    /* ◎変換データを格納　 　　　*/
		databuf[bufptr] = oto[bufptr/31];
		bufptr++;												  /* ◎バッファポインタを +1    */
	}
	lcd_init();
	lcd_cursor(0,0);
	lcd_printstr(" Push           ");
	lcd_cursor(0,1);
	lcd_printstr(" Now Writing...  ");
	sleep_ms(1000);
}
