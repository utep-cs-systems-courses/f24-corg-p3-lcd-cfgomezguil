#include "menu.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "screen.h"


u_int ColorShape = COLOR_RED;
char heartState = '1';
char size = 'B';
u_char width = screenWidth;
u_char height = screenHeight;
unsigned short ColorOptions[] = {COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_MAGENTA, COLOR_ORANGE, COLOR_CYAN};
const u_int COLOR_OPTIONS_SIZE = sizeof(ColorOptions) / sizeof(ColorOptions[0]);

void menu_init(){
  clearScreen(COLOR_WHITE);
  fillRectangle(0, height - 20, width, 20, COLOR_GRAY);
  drawString5x7(1,height - 13, "Current Color: ", COLOR_BLACK, COLOR_GRAY);
  fillRectangle(width - 40, height - 17, 20, 14, ColorShape);
  drawChar8x12(width-33, height - 15, heartState, COLOR_BLACK, ColorShape);
  drawChar8x12(width - 15, height - 15, size, COLOR_BLACK, COLOR_WHITE);
}

void update_menu(){
  //Rewrite the new state information
  fillRectangle(width - 40, height - 17, 20, 14, ColorShape);
  drawChar8x12(width-33, height - 15, heartState, COLOR_BLACK, ColorShape);
}
