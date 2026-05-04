#include <xc.h>
#include "config.h"
#include "GLCD.h"

#define _XTAL_FREQ 8000000 // needed for __delay_ms function


typedef enum{
    Ready=0,
    Running,
    Stopped
} state_t;

typedef enum{
    Decimal, 
    Second, 
    Minute,
    Hour
} values;


// global Variables
const char * s1 = "L4B GLCD\n";
const char * s2 = "--------\n";
state_t state = Ready;

unsigned int hour = 0;
unsigned int minute = 0;
unsigned int second = 0;
unsigned int decimal = 0;

int prev_btn = 0;
int transition = 0;
int increment = 0;

//si increment = 1, ++decimal
void tic(void);

// interrupt service routine for handling high priority Timer0
void interrupt rutinaAtencioInterrupcio (void);

//inicialitza el TMR0:

//Fcy = Fosc/4 = 2 MHz -> 1 tick = 0.5 microsegons
//1 timer increment = 0.5 * 256 = 128 microsegons
//100 ms / 128 microsegons = 781
//TMR0 overflow a 65536 -> 65536 - 781 = 64755 = 0xFD13
   //<0:2> = 111 prescale value 1:256
   //<3> = 0 prescalser on
   //<4> = 0 edge is low-high
   //<5> = 0 internal clock
   //<6> = 0 16 bit timer
   //<7> = 1 enable TMR0
void init_timer0(void);

//inicialitza tots els valors del chrono a 0
void reset_values();

//detector de flancs, si flanc ascendent retorna 1. En cas contrari retorna 0
int inputDetector();

//actualitza valors del chrono, pinta els valors i la barra de progressió
void updateGLCD();

//configuració de pins, interrupts i timers
void configPIC();

//dibuixa barra de progressió fins a un percentage a una posició (p,y) -> p [0:7], y [0:128] 
void draw_progress_bar(byte p, byte y, byte percent);

void update_progress_bar();

//dibuixa titol d'un estat
void paint_state(state_t state);

//dibuixa tots els valors
void paint_values();

//dibuixa valors de tipus v
void clear_values(values v);
