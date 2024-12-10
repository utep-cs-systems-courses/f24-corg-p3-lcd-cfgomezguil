#ifndef menu_included
#define menu_included
#include "lcdutils.h" 

extern u_int ColorShape;
extern char  heartState;
unsigned short ColorOptions[] = {COLOR_RED,COLOR_BLUE, COLOR_GREEN, COLOR_ORANGE, COLOR_YELLOW, COLOR_PURPLE};
//Initialize the Menu and place all the values corresponding to the menu
void menu_init();

// Update the menu based off the state that was activated
void update_menu(char state, u_int newColor);

//Use simple shape to show passage of time
void update_shape();

#endif
