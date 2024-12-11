#ifndef timerLib_included
#define timerLib_included

extern volatile unsigned int global_time;

void configureClocks();
void enableWDTInterrupts();
void timerAUpmode();

#endif
