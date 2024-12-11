#include "lcdutils.h"
#include "screen.h"
#include "lcddraw.h"
#include "menu.h"


// Size 1: 50, 30
// Size 2: 25, 20
// Size 3: 40, 25

static u_char dot_col = 1;   // Starting column of the dot
static const u_char dot_row = 10; // Fixed row for the dot
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

void update_timer_dot() {
  static u_int timer_count = 0;
  timer_count++;

  // Update dot position every few timer counts
  if (timer_count % 10 == 0) {  // Adjust modulus value to control speed
    // Erase the previous dot by drawing it in the background color
    drawPixel(dot_col, dot_row, COLOR_WHITE);

    // Move the dot to the next position
    dot_col++;

    // If the dot reaches the end, reset it and change the size
    if (dot_col > 120) {
      dot_col = 1;
      size_index = (size_index + 1) % 3; // Cycle through size states

      // Update the size indicator
      size = size_states[size_index];

      // Reflect the new size in the menu
      update_menu();
    }

    // Draw the dot in the new position
    drawPixel(dot_col, dot_row, COLOR_BLACK);
  }
}

