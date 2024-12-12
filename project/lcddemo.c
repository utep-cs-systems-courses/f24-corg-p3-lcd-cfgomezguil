
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "menu.h"
#include "screen.h"
#include "switches.h"
#include "buzzer.h"

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
  
  //oenableWDTInterrupts();
  or_sr(0x08);
  
  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      update_dot();
    }
    // P1OUT &= ~LED;           /**< Turn off LED (idle state) */
    //or_sr(LPM4_bits + GIE);  /**< Enter LPM4 with interrupts enabled */
    // P1OUT |= LED;            /**< Turn on LED (awake state) */
    redrawScreen = 1;
  }
}



void wdt_c_handler() {
  global_time++;            // Increment global time to track watchdog interrupts
  redrawScreen = 1;         // Request screen redraw
}
