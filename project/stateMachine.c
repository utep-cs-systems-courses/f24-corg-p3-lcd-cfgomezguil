#include "stateMachine.h"
#include "menu.h"


void color_state_advance() {
  ColorShape = ColorOptions[(ColorShape + 1) % COLOR_OPTIONS_SIZE];
  update_menu(); // Update the display
}


void heart_state_advance() {
  // Increment the heartState and wrap around from '3' back to '1'
  heartState = (heartState == '3') ? '1' : (heartState + 1);
  // Update the menu to reflect the new heart state
  update_menu();
}
