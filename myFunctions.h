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

const char * s_nom = "Mar Cabrelles\n"; 
const char * s2_nom = "Samuel Bru Mezquita\n"; 


void tic(void);

void interrupt rutinaAtencioInterrupcio (void);

void init_timer0(void);

void reset_values();

int inputDetector();

void updateGLCD();

char* get_state_char(state_t state);

void configPIC();

void draw_progress_bar(byte p, byte y, byte percent);

void update_progress_bar();

void paint_state(state_t state);

void paint_values();

void clear_values(values v);
