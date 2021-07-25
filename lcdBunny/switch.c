#include <msp430.h>
#include "switch.h"


void switch_init() {    
  P2REN |= SWITCHES;		// enables resistors for switches 
  P2IE |= SWITCHES;		// enable interrupts from switches
  P2OUT |= SWITCHES;		// pull-ups for switches 
  P2DIR &= ~SWITCHES;		// set switches' bits for input
}
