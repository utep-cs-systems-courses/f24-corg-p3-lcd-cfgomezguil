#include "lcdutils.h"
#include "screen.h"
#include "lcddraw.h"
#include "menu.h"

// Size 1: 50, 30
// Size 2: 25, 20
// Size 3: 40, 25

static char size_states[] = {'B', 'M', 'S'};
static u_char size_index = 0; // Index for the current size state

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


static u_char dot_x = 10; // Initial x-coordinate for the dot
static u_char dot_y = screenHeight - 19; // Initial y-coordinate for the dot
static char dx = 1;       // Movement direction along x-axis
static char dy = 0;       // Movement direction along y-axis
static u_char prev_x = 10;
void update_dot() {

  // Clear the previous dot position
  fillRectangle(prev_x, dot_y, 2, 2, COLOR_GRAY);

  // Update coordinates
  dot_x += dx;
  dot_y += dy;

  // Boundary checking and direction reversal
  if (dot_x >= screenWidth - 2 || dot_x <= 0) {
    dx = -dx; // Reverse direction on x-axis
    dot_x += dx; // Adjust to stay within bounds
  }
  if (dot_y >= screenHeight - 2 || dot_y <= 0) {
    dy = -dy; // Reverse direction on y-axis
    dot_y += dy; // Adjust to stay within bounds
  }

  // Draw the dot at the new position
  fillRectangle(dot_x, dot_y, 2, 2, COLOR_BLACK);

  // Store the current position for the next update
  prev_x = dot_x;
}

