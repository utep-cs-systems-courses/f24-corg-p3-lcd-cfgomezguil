#ifndef menu_included
#define menu_included
#include "lcdutils.h"

extern u_int ColorShape;
extern char  heartState;
extern char size;

extern unsigned short ColorOptions[];
extern const u_int COLOR_OPTIONS_SIZE;
//Initialize the Menu and place all the values corresponding to the menu
void menu_init();
// Update the menu based off the state that was activated
void update_menu();

#endif
