#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "utily.h"
#include "clock.h"
#include <avr/io.h>



void start();
unsigned char segment(char NO );
void _count (char count);
void blink(int value);
void ctrl_btn(int r);
void turn_off();
void toggleHeaterState();
void Port_init();



#endif