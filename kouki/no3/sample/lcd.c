#include <string.h>
#include "h8-3052-iodef.h"

#define TCONST40us 500
#define TCONST1ms 10000
#define LCD_RS 0x40
#define LCD_RW 0x20
#define LCD_E 0x10

void lcd_init(void);
void lcd_cursor(int x, int y);
void lcd_clear(void);
void lcd_printstr(unsigned char *str);
void lcd_printch(unsigned char ch);
void lcd_putch(unsigned char ch, unsigned char rs);
void wait1ms(int ms);

void lcd_init(void)
     /* LCD $BI=<(4o$r;H$&$?$a$N=i4|2=4X?t(B             */
     /* $B0lIt(B, $B%-!<%;%s%9$H$N7s$M9g$$$,$"$k$,BP:v:Q$_(B */
     /* LCD $BI=<(4o$N=i4|2=$K$O;~4V$,$+$+$k$N$GCm0U(B   */
{
  wait1ms(15);
  PADR = 0x0f;       /* PA0-3 $B$O(B0$B%"%/%F%#%V(B, PA4-6 $B$O(B1$B%"%/%F%#%V(B */
  PADDR = 0x7f;      /* PA4-6 $B$O=PNO$K@_Dj(B(LCD$B@)8f(B E,R/W,RS) */
                     /* PA0-3 $B$O%-!<%\!<%I%^%H%j%/%9$N=PNOMQ(B */
  P4DR = 0;          /* LCD $B%G!<%?(B */
  P4DDR = 0xff;      /* P40-7 $BA4$F=PNO$K@_Dj(B(LCD DB0-7) */
  lcd_putch(0x3f,0); /* $B%G!<%?E>AwI}(B(8$B%S%C%H(B) */
  wait1ms(5);
  lcd_putch(0x3f,0);
  wait1ms(100);
  lcd_putch(0x3f,0);
  lcd_putch(0x3f,0); /* $B%G!<%?E>AwI}(B8$B%S%C%H(B, 2$B%i%$%s(B, 5x10$B%I%C%H(B */
  lcd_putch(0x04,0); /* $B%G%#%9%W%l%$(BON/OFF$B@)8f(B(OFF) */
  lcd_putch(0x01,0); /* $B%G%#%9%W%l%$A4%/%j%"(B */
  wait1ms(2);        /* $B=hM}BT$A(B > 1.64ms */
  lcd_putch(0x06,0); /* $B%(%s%H%j!<%b!<%I%;%C%H(B Inc. without Disp.shift */
  lcd_putch(0x0c,0); /* $B%G%#%9%W%l%$(BON/OFF$B@)8f(B(ON) */
  lcd_putch(0x80,0); /* DDRAM$B%"%I%l%9%;%C%H(B */
}

void lcd_cursor(int x, int y)
     /* $BI=<(0LCV$rJQ99$9$k4X?t(B */
     /* $BI=<(4o:8>e$,(B (0,0) $B$H$J$k(B */
{
  char adr;

  if ((x < 16) && (y < 4)) {
    switch (y) {
    case 1: adr = 0xc0; break; /* 2$B9TL\$N@hF,(B */
    case 2: adr = 0x94; break; /* 4$B7e(BLCD(SC2004C, L2034)$B$J$I$N(B3$B9TL\$N@hF,(B */
    case 3: adr = 0xd4; break; /* 4$B7e(BLCD(SC2004C, L2034)$B$J$I$N(B4$B9TL\$N@hF,(B */
    default: adr = 0x80;       /* 1$B9TL\$N@hF,(B */
    }
    lcd_putch(adr+x,0);
  }
}

void lcd_clear(void)
     /* $BI=<(4o$NA42hLL$r%/%j%"$9$k$?$a$N4X?t(B */
{
  lcd_putch(0x01,0); /* $B%G%#%9%W%l%$A4%/%j%"(B */
  wait1ms(2);        /* $B=hM}BT$A(B > 1.64ms */
}

void lcd_printstr(unsigned char *str)
     /* $BI=<(4o$KJ8;zNs$rI=<($9$k4X?t(B */
     /* $BJ8;z%3!<%I$O(B ASCII $B%3!<%I$NHO0O$J$iLdBj$J$$(B */
{
  int l, i;

  l = strlen(str);
  for (i = 0; i < l; i++) lcd_printch(str[i]);
}

void lcd_printch(unsigned char ch)
     /* $BI=<(4o$K(B1$BJ8;z$@$1I=<($9$k4X?t(B */
     /* $BJ8;z%3!<%I$O(B ASCII $B%3!<%I$NHO0O$J$iLdBj$J$$(B */
{
  lcd_putch(ch,1);  /* $B%-%c%i%/%?$r(B1$BJ8;zE>Aw(B */
}

void lcd_putch(unsigned char ch, unsigned char rs)
     /* LCD $B$K%3%^%s%I$d%G!<%?$rAw$k$?$a$N4X?t(B   */
     /* ch $B$K%3%^%s%I$^$?$O%G!<%?$rF~$l$k(B        */
     /* rs $B$,(B 0 $B$N$H$-%3%^%s%I(B, 1 $B$N$H$-$O%G!<%?(B */
     /* $BDL>o(B, $B%f!<%6$+$iD>@\8F$S=P$9$3$H$O$J$$(B   */
{
  int i;
  unsigned char st13,st2,key;

  rs = rs << 6;
  st13 = LCD_RS & rs;
  st2 = st13 | LCD_E;
  key = PADR & 0x0f;   /* PA0-4 $B$O%-!<%^%H%j%/%9$G;HMQ(B      */
  st13 = st13 | key;   /* PA5-6 $B$O(BLCD$B$N@)8f@~$@$,(B, $B%-!<B&$N(B */
  st2 = st2 | key;     /* $BCM$rGK2u$7$J$$$h$&$K$9$k(B          */
  PADR = st13;      /* $B%l%8%9%?A*Br$r9T$&(B */
  PADR = st2;       /* E$B?.9f$r(B 1 $B$K$9$k(B */
  P4DR = ch;        /* $B%G!<%?$^$?$O%3%^%s%I$rAw$k(B */
  PADR = st13;      /* E$B?.9f$r(B 0 $B$K$9$k(B */
  for (i = 0; i < TCONST40us; i++); /* 40us $BBT$A(B(LCD$B$N=hM};~4V(B) */
}

void wait1ms(int ms)
     /* ms = 1 $B$N$H$-(B, $BLs(B1ms$B$@$1%`%@$J%k!<%W$GBT$D4X?t(B            */
     /* LCD$B$NF0:n$rJ]>Z$9$k$?$a$KI,MW$J;~4V$r3NJ]$9$k$N$,L\E*(B     */
     /* $B$3$N4V(B, CPU$B$rFH@j$9$k$N$GCm0U$7(B, $BB>$NMQES$K;HMQ$7$J$$$3$H(B */
{
  int i,j;

  for (i = 0; i < ms; i++){
    for (j = 0; j < TCONST1ms; j++);
  }
}
