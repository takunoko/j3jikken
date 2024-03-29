#include "h8-3052-iodef.h"
/* #include "h8-3052-int.h" */
#include "lcd.h"
#include "ad.h"
#include "da.h"

#define BUFSIZE       30 /* バッファの大きさ(kB) */
#define SAMPLE         0 /* 動作選択(録音)       */
#define PLAY           1 /* 動作選択(再生)       */
#define NOSELECT      -1 /* 動作選択値(末選択)   */
#define TIME      120000 /* 録音/再生時間        */

volatile unsigned char databuf[(unsigned long)BUFSIZE * 1024];
volatile unsigned long bufptr;
volatile int play_mode;

int            main(void);
unsigned char  menu(void);
void           sample_replay(int mode);

int main(void)
{
  /* キー入力情報を取得するための変数を宣言する */
  unsigned char key_data;

  lcd_init();    /* LCD の初期化            */
  ad_init();     /* A/D 変換器の初期化      */
  da_init();     /* D/A 変換器の初期化      */

  /* ◎ここにキー入力取得のためのポートの初期化を記述する */
                          /* P60,1,2   入力 */
                          /* PA0,1,2,3 出力 */

  while (1) {
    play_mode = NOSELECT;
    key_data = menu();                    /* メニューを選ぶ   */
    /* 録音キーが押されたらSAMPLE, 再生キーが押されたらPLAY   */
    /* をplay_modeに格納する処理を記述する                    */
    
    
    
    
    /* ◎*キー入力されていれば録音/再生の関数を呼び出す処理を記述する  */



    
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

  while (cf == 0 ){  /* キー入力するまでループする */
    /* ここにキー入力の処理を記述する */


	  
    /* ◎key *,# のみの入力に対応させる処理を記述する */
    
    
     
     
    }
  }

  /* 入力されたキーの情報を返す */
  return key_data;
}

void sample_replay(int mode)
     /* 録音または再生を行う関数 */
     /*   mode: PLAY, SAMPLE     */
{
   bufptr = 0;                             /* バッファポインタを初期化  */
  if (mode == PLAY){                                /* 再生モードの処理 */
    /* ここにスピーカをスピーカとして使用する命令 */
    speaker_switch(SPEAKER);
    lcd_cursor(0,1);
    lcd_printstr(" Now playing... ");
    
    /* 音声出力処理内容を記述する */
    while(bufptr <= TIME){           i     /*   データ出力を繰り返す    */
                                           /* ◎Ｄ／Ａにデータを出力    */
                                           /* ◎バッファポインタを +1   */
    }   
  }
  if (mode == SAMPLE){                              /* 録音モードの処理 */
    /* ここにスピーカをマイクとして使用する命令 */
    speaker_switch(MIC);
    lcd_cursor(0,1);
    lcd_printstr(" Now Sampling...");
    
    /* 音声取込処理内容を記述する */
    while(bufptr <= TIME){                 /*   データ読込を繰り返す     */
                                           /* ◎Ａ／Ｄ変換スタート       */
                                           /* ◎Ａ／Ｄ変換終了待ち 約5us */
                                           /* ◎変換データを格納　 　　　*/
                                           /* ◎バッファポインタを +1    */
    }
  }
  speaker_switch(MIC);      /* スピーカーオフ   */
}

