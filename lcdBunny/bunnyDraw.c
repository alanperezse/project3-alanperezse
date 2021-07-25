#include "lcdutils.h"
#include "bunnyDraw.h"

void drawStreet() {
  char blue = 1;
  char green = 2;
  char red = 1;
  fillRectangle(0, 120, 128, 3, (blue) << 11 | (green) << 5 | red);
}

void drawBunny(u_char colMin, u_char rowMin, char slide, char size, u_int fgColorBGR) {
  static unsigned long bunny[3][16]  = {
    0x00000000,
    0x00000000,
    0x0000C000,
    0x0000A000,
    0x00009E00,
    0x06008200,
    0x027F9100,
    0x01800880,
    0x02000080,
    0x02000080,
    0x02000F80,
    0x01000800,
    0x01001000,
    0x009F2000,
    0x00A14000,
    0x00A14000,    
    
    0x00000000,
    0x00000000,
    0x0000C000,
    0x0000A000,
    0x00009E00,
    0x06008200,
    0x027F9100,
    0x01800880,
    0x02000080,
    0x02000080,
    0x02000F80,
    0x01000800,
    0x01001000,
    0x009F2000,
    0x01209000,
    0x02404800,

    0x00000000,
    0x00000000,
    0x0000C000,
    0x0000A000,
    0x00009E00,
    0x00008200,
    0x00039100,
    0x003C0880,
    0x00C00080,
    0x0D000080,
    0x05000F80,
    0x02000800,
    0x02301000,
    0x020D2000,
    0x01034000,
    0x00FF4000
  };

  char rowMax = 32 * size;
  char colMax = 16 * size;
  for(int row = 0; row < 16; row++) {
    for(int col = 0; col < 32; col++) {
      // Draw rectangle if bit is 1
      if(bunny[slide][row] & (0x80000000 >> col)) fillRectangle(colMin + col * size, rowMin + row * size, size, size, fgColorBGR);
    }
  }
}


void drawApple(u_char colMin, u_char rowMin, char size, u_int fgColorBGR) {
  static unsigned short apple[16]  = {
    0x0000,
    0x0060,
    0x00C0,
    0x0080,
    0x0E70,
    0x1FFC,
    0x3FF8,
    0x3FF0,
    0x3FF0,
    0x3FF0,
    0x3FF8,
    0x3FFC,
    0x3FFC,
    0x3FF8,
    0x0E70,
    0x0000
  };

  char rowMax = 16 * size;
  char colMax = 16 * size;
  for(int row = 0; row < 16; row++) {
    for(int col = 0; col < 16; col++) {
      // Draw rectangle if bit is 1
      if(apple[row] & (0x8000 >> col)) fillRectangle(colMin + col * size, rowMin + row * size, size, size, fgColorBGR);
    }
  }
}
