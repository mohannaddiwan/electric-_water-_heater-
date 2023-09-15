#include "interrupt.h"
#include "functions.h"

void int0_init()
{
	clearbit(DDRD,2);
	setbit(MCUCR,ISC01); // The rising edge of INT0 generates an interrupt request.
	setbit(MCUCR,ISC00); //The rising edge of INT0 generates an interrupt request.
	setbit(GICR,INT0);   // external interrupt  EN INT0
	sei();               // global interrupt EN
}

ISR(INT0_vect)
{
	toggleHeaterState();
		
}
