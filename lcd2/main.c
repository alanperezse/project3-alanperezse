#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "bunnyDraw.h"


short redrawScreen = 1;

void interruptsOn(char on) {
  if(on) or_sr(0x8);
  else and_sr(~0x8);
}

void sleepOn(char on) {
  if(on) or_sr(0x10);
  else and_sr(~0x10);
}

void wdt_c_handler() {
  static char state = 0;
  state = ++state % 125;
  if(state == 0) redrawScreen = 1;
}  

void main() {
  led_init();
  configureClocks();
  lcd_init(); 
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  drawString5x7(20, 20, "Stop?", COLOR_GREEN, COLOR_BLACK);
  drawBunny(0, 100, 0, 2, COLOR_WHITE);
  sleepOn(1);

  short slide = 2;
  while(1) {
    redrawScreen = 0;
    drawBunny(0, 100, slide, 2, COLOR_BLACK);
    slide = ++slide % 2;  //Set next slide
    drawStreet();
    drawBunny(0, 100, slide, 2, COLOR_WHITE);
    
    greenOn(0);
    interruptsOn(1);  //Enable interrupts
    sleepOn(1);   //Sleep


    /*Waking up*/

    
    interruptsOn(0);  //Disable interrupts
    greenOn(1);
  }
}

    
    



