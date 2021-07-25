#include <msp430.h>
#include "led.h"

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

void greenOn(char on) {
  if(on) P1OUT |= GREEN_LED;
  else P1OUT &= ~GREEN_LED;
}
