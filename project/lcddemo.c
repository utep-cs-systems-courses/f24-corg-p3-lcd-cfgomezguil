#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "menu.h"
#include "screen.h"

int main()
{
  configureClocks();
  lcd_init();

  clearScreen(COLOR_WHITE);
  menu_init();
  screen_init();
  
  or_sr(0x18);
}

