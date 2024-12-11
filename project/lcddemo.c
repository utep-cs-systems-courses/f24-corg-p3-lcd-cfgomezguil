
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "menu.h"
#include "screen.h"
#include "switches.h"

volatile unsigned int global_time = 0;

short redrawScreen = 1;



void main()
{
  P1DIR |= LED;/**< Green led on when CPU on */

  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  menu_init();
  screen_init();
  //  enableWDTInterrupts();
  or_sr(0x08);
  
  while (1) {
    if (global_time % 250000 == 0) { // Example: Update dot every 50 ticks
      update_dot();
    }
    //P1OUT &= ~LED;/* led off */
    //or_sr(0x10);/**< CPU OFF */
    //P1OUT |= LED;/* led on */
  }
}


