#include "lcdutils.h"
#include "screen.h"
#include "lcddraw.h"

// Size 1: 50, 30
// Size 2: 25, 20
// Size 3: 40, 25
void screen_init(){
  drawHeart(10,40,50,30,ColorShape);  // Heart 1
  drawHeart(45,60,50,30,COLOR_BLUE);  // Heart 2
  drawHeart(10,80,50,30,COLOR_GREEN); // Heart 3
}

void update_heart() {
  // Erase the previous heart (fill it with the background color)
  switch (heartState) {
  case '1':
    drawHeart(10, 40, 50, 30, ColorShape); // Update Heart 1
    break;
  case '2':
    drawHeart(45, 60, 50, 30, ColorShape); // Update Heart 2
    break;
  case '3':
    drawHeart(10, 80, 50, 30, ColorShape); // Update Heart 3
    break;
  default:
    break; // No update if heartState is invalid
  }
}

