
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "menu.h"
#include "screen.h"
#include "switches.h"
#include "buzzer.h"

volatile unsigned int global_time = 0;

short redrawScreen = 1;



void main()
{
  P1DIR |= LED;/**< Red led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  menu_init();
  screen_init();
  buzzer_init();
  
  enableWDTInterrupts();
  or_sr(0x08);
  
  while (1) {
    if(redrawScreen){
      redrawScreen = 0;
      update_dot();
    }
    P1OUT &= ~LED; /**< Turn off LED (indicating idle state) */
    or_sr(LPM4_bits); /**< Enter low-power mode until interrupt occurs */
    P1OUT |= LED; /**< Turn on LED (indicating active state) */
  }
}
