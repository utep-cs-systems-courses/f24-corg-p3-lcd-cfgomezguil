#include "lcdutils.h"
#include "screen.h"
#include "lcddraw.h"

// Size 1: 50, 30
// Size 2: 25, 20
// Size 3: 40, 25


void screen_init(){
  drawHeart(10,40,50,30,ColorShape);
  drawHeart(45,60,50,30,COLOR_BLUE);
  drawHeart(10,80,50,30,COLOR_GREEN);
}

void update_heart(){
  drawHeart(10,40,50,30,ColorShape);
}
