#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include "clock.h"
#include "utily.h"
#include <math.h>

void ADC_init();
int ADC_read(int ADC_chanel);

#endif 