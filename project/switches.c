#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "screen.h"
#include "menu.h"
#include "stateMachine.h"
#include "buzzer.h"

int switches = 0;

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init(){
  P2REN |= SWITCHES; // enables resistors for switches
  P2IE |= SWITCHES; // enables interrupts from switches
  P2OUT |= SWITCHES; // pull-ups for switches 
  P2DIR &= ~SWITCHES; // set switches' bits for input
  switch_update_interrupt_sense();
}

void switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES; // Update switches state

  if (switches & SW1) {
    update_heart();
    buzzer_set_period(2500);
  }
  if (switches & SW2) {
    color_state_advance();
    buzzer_set_period(1000);
  }
  if (switches & SW3) {
    heart_state_advance();
    buzzer_set_period(400);
  }
  if (switches & SW4) {
    // Low-power mode handling moved to interrupt vector
    P1OUT &= ~LED; // Optional: Turn off LED
  }
}


void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCHES) {      // Check if interrupt is caused by switches
    P2IFG &= ~SWITCHES;        // Clear pending interrupts
    switch_interrupt_handler(); // Handle switch logic
    _bic_SR_register_on_exit(LPM4_bits); // Exit LPM4 on any switch interrupt
  }
}
