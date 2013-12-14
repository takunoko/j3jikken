#include "h8-3052-iodef.h"
#include "h8-3052-int.h"
#include "timer.h"

/* 割り込みの周期 1000us */
#define INT1MS 100

/* duty 0-100 */
#define DUTY 2 

/* P9DR */
#define OUTPUT_HIGH 0x30
#define OUTPUT_LOW 0x20

/* 割り込み処理に必要な変数は大域変数にとる */
/* volatile はプログラムの流れとは無関係に変化する変数に必ずつける */
volatile unsigned int sys_time;

/* 割り込みハンドラのプロトタイプ宣言 */
void int_imia0(void);

int main(void)
{

  ROMEMU(); /* ROMエミュレーションをON (割り込み使用時必須) */

  sys_time = 0; /* 時間を格納する変数の初期化 */

  /* LEDの接続されているポートの初期化をここに書く (実験1参照) */
  P9DDR = 0x30;  /* ポート9の初期化(P94--P95を出力に設定) */

	/* 消灯 */
	P9DR = 0x30;

  timer_init();        /* タイマを使用前に初期化する */
  timer_set(0,INT1MS); /* タイマ0を1ms間隔で動作設定 */
  timer_start(0);      /* タイマ(チャネル0)スタート  */

  ENINT();             /* CPU割り込み許可 */

  while (1) {
    /* 割り込み動作以外はこの無限ループを実行している */

    /* ここに sec_time の値によってLEDを光らせるプログラムを書く */
    /*   1秒ごとに 赤→緑→赤→緑→… と交互に点滅させる         */


  }

  return 1; /* mainからの戻り値はエラーレベルを表す 0:正常終了 */
            /* 永久ループの外なので,戻ったら何かおかしい       */
}

#pragma interrupt
void int_imia0(void)
     /* タイマ0の割り込みハンドラ                                   */
     /*   タイマ0から割り込み要求がくるとこの関数が呼び出される     */
     /* 関数の名前はタイマ0の割り込みはこの名前と決まっている       */
     /* 関数の直前に割り込みハンドラ指定の #pragma interrupt が必要 */
{
  /* 割り込みハンドラの処理が軽くなるように配慮すること */
  /* 外でできる処理はここには書かない */

  /* sys_time の更新 ( +1 する) をここに書く */
	sys_time++;

  /* 再びタイマ割り込みを使用するために必要な操作      */
  /*   タイマ0の割り込みフラグをクリアしないといけない */
  timer_intflag_reset(0);

	if(DUTY >= sys_time){
		P9DR = OUTPUT_HIGH;
	}else{
		P9DR = OUTPUT_LOW;
	}

	if(sys_time >= 10){
		sys_time = 0;
	}

  ENINT();       /* CPUを割り込み許可状態に */
}
