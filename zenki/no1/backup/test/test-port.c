#include "h8-3052-iodef.h"


int main(void)
{
  P9DDR = 0x30;  /* $B%]!<%H(B9$B$N=i4|2=(B(P94--P95$B$r=PNO$K@_Dj(B) */

  P9DR = 0x20;  /* $B=PNO%G!<%?$r%;%C%H(B */

  while(1)
  {
    /* $BFC$K2?$b$;$:L58B%k!<%W(B */
  }
}
