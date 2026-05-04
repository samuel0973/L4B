// a proposal for main.c ..... just to inspire you
#include <xc.h>
#include "config.h"
#include "GLCD.h"

#define _XTAL_FREQ 8000000 // needed for __delay_ms function

typedef enum{
    Ready=0,
    Running,
    Stopped
} state_t;
// global Variables
const char * s1 = "L4B GLCD\n";
const char * s2 = "--------\n";

const char * s_nom = "Mar Cabrelles\n"; // Canvia-ho pel teu
const char * s2_nom = "Samuel Bru Mezquita\n"; // Canvia-ho pel teu

void tic(void)
{
    //Coses a fer periòdicament
}
// interrupt service routine for handling high priority Timer0
void interrupt rutinaAtencioInterrupcio (void) 

    if (timer0Flag) {
        tic();
    }
    // falling edge detection and debouncing
    ??? inputDetector(·) {

    }
// initialize PORTs, timer0 and basic PIC resources
void configPIC() {
    ANSELE = 0x00;
    ANSELB = 0x00;
    ANSELD = 0x00;

    TRISE = 0x01;

    PORTB = 0x00;
    PORTD = 0x00;
}

void main(void) {

    configPIC();

    writeTxt(2, 8, s1);     // "L4A GLCD" al centre
    writeTxt(3, 8, s2);     // "L4A GLCD" al centre
    writeTxt(4, 4, s_nom);  // El teu nom a sota
    writeTxt(5, 4, s2_nom);  // El teu nom a sota

    __delay_ms(1000);       // Esperem 1 segon
    clearGLCD(0,7,0,127);   // Tornem a esborrar per al bucle principal


    while (1) { // MAIN LOOP starts here
        if ( inputDetector(·) ) { // check raising edge
            switch(state) {
            // depending on the current state, handle the transition

            }
        }   
    updateGLCD(·); // show things on the GLCD smartly!

    }// MAIN LOOP ends here
}
