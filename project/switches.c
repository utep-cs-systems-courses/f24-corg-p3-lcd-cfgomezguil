#include <msp430.h>
#include "switches.h"
#include "screen.h"
#include "menu.h"
#include "stateMachine.h"

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
void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val * SWITCHES;

  if (switches & SW1) {
    update_heart();
  }
  if (switches & SW2) {
    color_state_advance();
  }
  if(switches & SW3) {
    heart_state_advance();
  }
}
void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if(P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}                                     
