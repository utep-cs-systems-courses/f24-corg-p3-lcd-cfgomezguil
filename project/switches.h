#include <msp430.h>
#ifndef switches_included
#define switches_included

#define LED BIT6

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15 // All Switches

void switch_init();
void switch_interrupt_handler();

#endif
