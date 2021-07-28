#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "bunnyDraw.h"


short redrawScreen = 1;
short triangleInitX = 100;
short triangleInitY = 20;
short triangleCurrX = 100;
short triangleCurrY = 20;
short triangleCurrW = 1;
short triangleInitColor = (31 << 11) | (63 << 5) | (31);
short triangleCurrColor = (31 << 11) | (63 << 5) | (31);

void interruptsOn(char on) {
  if(on) or_sr(0x8);
  else and_sr(~0x8);
}

void sleepOn(char on) {
  if(on) or_sr(0x10);
  else and_sr(~0x10);
}

void updateTriangle() {
  static char state = 0;
  state = ++state % 16;
  // Position
  triangleCurrX = triangleInitX - 1 * state;
  triangleCurrY = triangleInitY + 1 * state;
  triangleCurrW = 1 + 2 * state;

  // Color
  triangleCurrColor = ((31 - 2 * state) << 11) | ((63 - 4 * state) << 5) | (31);;
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


    fillRectangle(triangleCurrX, triangleCurrY, triangleCurrW, 1, triangleCurrColor);
    updateTriangle();
    
    greenOn(0);
    interruptsOn(1);  //Enable interrupts
    sleepOn(1);   //Sleep


    /*Waking up*/

    
    interruptsOn(0);  //Disable interrupts
    greenOn(1);
  }
}

    
    



