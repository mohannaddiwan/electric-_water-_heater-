#include <avr/io.h>
#include "utily.h"
#include "EEprom.h"
#include "ADC.h"
#include "interrupt.h"
#include "functions.h"
#include "clock.h"

int main(void)
{
	int0_init();
	ADC_init();
	EEPROM_INIT();
	Port_init();
	while (1)
	{
	start();
	}
}

