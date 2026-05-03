// a proposal for main.c ..... just to inspire you
#include <xc.h>
#include "config.h"
#include "GLCD.h"
....
#define _XTAL_FREQ 8000000 // needed for __delay_ms function
typedef enum{
Ready=0,
Running,
Stopped
}state_t;
// global Variables
....
void tic(void)
{
//Coses a fer periòdicament
}
// interrupt service routine for handling high priority Timer0
void interrupt rutinaAtencioInterrupcio (void)
...
if (timer0Flag) {
tic();
}
// falling edge detection and debouncing
??? inputDetector(·) {
....
}
// initialize PORTs, timer0 and basic PIC resources
void configPIC() {
....
}
void main(void) {
....
configPIC();
....
while (1) { // MAIN LOOP starts here
if ( inputDetector(·) ) { // check raising edge
switch(state) {
// depending on the current state, handle the transition
....
}
}
updateGLCD(·); // show things on the GLCD smartly!
....
}// MAIN LOOP ends here
}
