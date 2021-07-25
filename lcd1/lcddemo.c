/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  drawString5x7(20, 20, "Stop?", COLOR_GREEN, COLOR_BLACK);

  while(1) {
    drawBunny(0, 100, 0, 2, COLOR_WHITE);
    or_sr(0x10);
  }
}
