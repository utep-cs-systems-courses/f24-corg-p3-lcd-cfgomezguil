
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "menu.h"
#include "screen.h"
#include "switches.h"

int main()
{
  configureClocks();
  lcd_init();
  switch_init();
  screen_init();
  menu_init();
  
  or_sr(0x8);
}

