#ifndef led_included
#define led_included

#define GREEN_LED BIT6             // P1.6
#define LEDS BIT6

void led_init();
void greenOn(char on);

#endif
