// a proposal for main.c ..... just to inspire you
#include "myFunctions.h"

void main(void) {

    configPIC();
    GLCDinit();
    clearGLCD(0,7,0,127);
    

    writeTxt(2, 8, "L4B GLCD");     
    writeTxt(3, 8, "--------");     
    writeTxt(4, 4, "Mar Cabrelles");  
    writeTxt(5, 4, "Samuel Bru Mezquita");  

    __delay_ms(1000);       
    clearGLCD(0,7,0,127);   

    writeTxt(0,2,"Ready");
    
    paint_values();
    draw_progress_bar(5,36,0);
   
    while (1) { 
        if (inputDetector()) { // check raising edge
            switch(state) {
               // depending on the current state, handle the transition
	            case Ready: 
		            state = Running;
		            transition = 1;
		            increment = 1;
		        break;
	       
	            case Running:
		            state = Stopped;
		            transition = 1;
		            increment = 0;
		            break;
	       
	            case Stopped:
		            state = Ready;
		            transition = 1;
		            increment = 0;
		            reset_values();
		        break;
            }
        }   
	    updateGLCD(); // show things on the GLCD smartly!
    }
}
