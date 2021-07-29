#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "switch.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "bunnyDraw.h"

char redrawScreen = 1;
short notes[] = {3405, 2863, 3822, 2551};

/*For button presses*/
char buttonDown = 0;  //Indicates if button is being pressed down
char wasPressed = 0;  //Indicates if button was pressed in this window


/*For bunny movement*/
char bunnyStop = 0;


/*For apple*/
char appleSpawn = 0;
char appleX = 100;
char appleY = 113;


void interruptButtonsOn(char on) {
  if(on) P2IE |= SWITCHES;
  else P2IE &= ~SWITCHES;
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

void appleUpdtState() {
  static char state = 0;
  static char stride = 20;
  
  appleX = 100 - (20 * state);
  if(state == 3) appleSpawn = 0;
  state = ++state % 4;
}

void main() {
  led_init();
  configureClocks();
  switch_init();
  buzzer_init();
  lcd_init(); 
  enableWDTInterrupts();      /**< enable periodic interrupt */
  greenOn(1);
  or_sr(0x8);
  
  clearScreen(COLOR_BLACK);
  drawString5x7(20, 20, "STOP?", COLOR_GREEN, COLOR_BLACK);
  drawString5x7(20, 40, "FEED?", COLOR_GREEN, COLOR_BLACK);
  bunnyStop = 1;
  appleSpawn = 1;
  

  short slide = 0;
  short noteIdx = 0;

  while(1) {
    redrawScreen = 0;

    // Draw the appropiate pixels according to the state of the bunny
    if(bunnyStop) {
      if(slide != 2) {// Prevents updating screen
	//Play pause note
	buzzer_set_period(4545);

	//Eliminate previous foreground
	drawBunny(0, 100, slide, 2, COLOR_BLACK);
	if(appleSpawn) drawApple(appleX, appleY, 1, COLOR_BLACK);

	// Update slides/states
	slide = 2;
	noteIdx = 0;

	//Background
	drawStreet();  

	//Foreground
	drawBunny(0, 100, slide, 2, COLOR_WHITE);
	if(appleSpawn) drawApple(appleX, appleY, 1, COLOR_RED);
      }
      
      else buzzer_set_period(0);
    }
    
    else {
      //Play next note
      buzzer_set_period(notes[noteIdx]);

      //Eliminate previous foreground
      drawBunny(0, 100, slide, 2, COLOR_BLACK);
      if(appleSpawn) drawApple(appleX, appleY, 1, COLOR_BLACK);

      //Update slides/states
      slide = ++slide % 2;
      if(appleSpawn) appleUpdtState();
      noteIdx = ++noteIdx % 4;
      
      //Background
      drawStreet();
      
      //Foreground
      if(appleSpawn) drawApple(appleX, appleY, 1, COLOR_RED);
      drawBunny(0, 100, slide, 2, COLOR_WHITE);
    }

    // Prepare to sleep
    greenOn(0);
    interruptButtonsOn(1);  //Enable interrupts SW
    sleepOn(1);   //Sleep


    
    /*Waking up*/

    

    // After waking up
    interruptButtonsOn(0);  //Disable interrupts SW
    greenOn(1);
    wasPressed = 0;
  }
}

void switch_interrupt_handler_2() {
  P2IES |= (P2IN & SWITCHES);
  P2IES &= (P2IN | ~SWITCHES);

  // No buttons are being pressed
  if((P2IN & SWITCHES) == SWITCHES) {
    buttonDown = 0;
    return;
  }

  // If button currently pressed
  if(wasPressed || buttonDown) return;

  // Detect which button is being pressed
  if(!(P2IN & SW1)) { // SW1 is pressed
    buttonDown = 1;
    wasPressed = 1;
    bunnyStop = !bunnyStop;
  }

  if(bunnyStop == 1) return;

  // Spawns apple
  else if(!(P2IN & SW2)) { // SW2 is pressed
    buttonDown = 1;
    wasPressed = 1;
    appleSpawn = 1;
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES) { // did a button cause this interrupt?
    P2IFG &= ~SWITCHES;// clear pending sw interrupts
    switch_interrupt_handler_2(); // single handler for all switches
  }
}

