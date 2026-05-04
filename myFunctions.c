#include "myHeaders.h"

void tic(void)
{
    //Coses a fer periòdicament
    if (increment) ++decimal;
}
// interrupt service routine for handling high priority Timer0
void interrupt rutinaAtencioInterrupcio (void) {

    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE) {
        tic();
	
	TMR0H = 0xFD;
	TMR0L = 0x13;
	INTCONbits.TMR0IF = 0;
    }
    // falling edge detection and debouncing
    //??? inputDetector(·){}

    //
}

//Fcy = Fosc/4 = 2 MHz -> 1 tick = 0.5 microsegons
//1 timer increment = 0.5 * 256 = 128 microsegons
//100 ms / 128 microsegons = 781
//TMR0 overflow a 65536 -> 65536 - 781 = 64755 = 0xFD13
void init_timer0(void) {
   T0CON = 0b10000111;
   //<0:2> = 111 prescale value 1:256
   //<3> = 0 prescalser on
   //<4> = 0 edge is low-high
   //<5> = 0 internal clock
   //<6> = 0 16 bit timer
   //<7> = 1 enable TMR0
   
   TMR0H = 0xFD;
   TMR0L = 0x13;
}

void clear_values(values v) {
   switch(v) {
      case Decimal:
	 clearGLCD(3, 3, 90, 102);
	 break;
	 
      case Second:
	 clearGLCD(3, 3, 78, 90);
	 break;
      
      case Minute:
	 clearGLCD(3, 3, 66, 78);
	 break;
      
      case Hour:
	 clearGLCD(3, 3, 54, 66);
	 break;
   }
}

void reset_values() {
   decimal = 0;
   second = 0;
   minute = 0;
   hour = 0;
}

int inputDetector() {
   int btn = PORTEbits.RE0;
   if (btn && prev_btn == 0) {
      __delay_ms(10);
      btn = PORTEbits.RE0;
      if (btn) {
	 prev_btn = btn;
	 return 1;
      }
   }
   prev_btn = btn;
   return 0;
}

void paint_values() {
    if (hour < 10) {
      
      writeNum(3, 8, 0);
      writeNum(3, 9, hour);
    }
    else {
      writeNum(3, 8, hour);
    }
    
    writeTxt(3,10, ":");
    
    if (minute < 10) {
      writeNum(3, 11, 0);
      writeNum(3,12, minute);
    }
    else {
      writeNum(3,11, minute);
    }
    
    writeTxt(3,13,":");
    
    if (second < 10) {
      writeNum(3, 14, 0);
      writeNum(3, 15, second);
    }
    else {
      writeNum(3,14,second);
    }
    writeTxt(3,16,".");
    writeNum(3,17, decimal);
}

void paint_state(state_t s) {
   clearGLCD(0, 0, 12, 54);
   if (s == Ready) writeTxt(0, 2, "Ready");
   if (s == Running) writeTxt(0, 2, "Running");
   if (s == Stopped) writeTxt(0, 2, "Stopped!");
}

void updateGLCD() {
   if (decimal >= 10) {
      ++second;
      decimal = 0;
      clear_values(Decimal);
      if (second == 10) {
	 state = Stopped;
	 increment = 0;
	 transition = 1;
      }
   }
   if (second >= 60) {
      ++minute;
      second = 0;
      clear_values(Second);
   }
   if (minute >= 60) {
      ++hour;
      minute = 0;
      clear_values(Minute);
   }
   if (hour >= 24) {
      reset_values();
      clear_values(Hour);
   }
   
   if (transition) {
      paint_state(state);
      transition = 0;
   }
   
   paint_values();
   update_progress_bar();
}

char* get_state_char(state_t state) {
   if (state == Ready) return "Ready";
   if (state == Running) return "Running";
   return "Stopped!";
}

// initialize PORTs, timer0 and basic PIC resources
void configPIC() {
    ANSELE = 0x00;
    ANSELB = 0x00;
    ANSELD = 0x00;

    TRISE = 0x01;

    PORTB = 0x00;
    PORTD = 0x00;
    
    init_timer0();
    
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    RCONbits.IPEN = 1;
    INTCON2bits.TMR0IP = 1;
    //encendre al final
    INTCONbits.GIEH = 1;
}

void draw_progress_bar(byte p, byte y, byte percent) {
    const int length = 12;
    int totalPixels = length * 5;
    int filledPixels = (totalPixels * percent) / 100;

    for (int i = 0; i < totalPixels; ++i) {
        byte pattern;

        if (i == 0 || i == totalPixels - 1) pattern = 0x7F; 
        else if (i < filledPixels) pattern = 0x7F; 
        else pattern = 0x41; // empty area

        writeByte(p, y + i, pattern);
    }
}

void update_progress_bar() {
    int percentage = second * 10 + decimal;
    draw_progress_bar(5, 36, percentage);
}
