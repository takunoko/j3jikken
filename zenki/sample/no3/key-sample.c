#include "h8-3052-iodef.h"

int main(void)
{
  unsigned char cf, key_data;

  P9DDR = 0x30;  /* $B%]!<%H(B9$B$N=i4|2=(B(P95-P94$B$r=PNO$K@_Dj(B) */

  P6DDR &= ~0x07;  /* P60,1,2   $BF~NO(B */
  PADDR |= 0x0f;   /* PA0,1,2,3 $B=PNO(B */

  while(1) {
    key_data = 0;

    //key 1,2,3
    PADR = 0x07; // PA3 = L
    cf = P6DR;   // $B%G!<%?F~NO(B
    cf = ~cf;    // cf$B$NH?E>(B
    cf &= 0x07;  // P60,1,2$B$N$_8+$k(B
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
    PADR = 0x0b; /* This is a mistake code. */
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
    
    if(key_data == '1' ) {
      P9DR = 0x20;  /* D1($B@V(B)$BE@Et(B, D2($BNP(B)$B>CEt(B */
    }
    else {
      P9DR = 0x30;  /* D1($B@V(B)$B>CEt(B, D2($BNP(B)$B>CEt(B */
    }

  }

}
