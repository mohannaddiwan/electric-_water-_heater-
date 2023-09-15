#include "ADC.h"


void ADC_init()
{
	
	ADMUX|=(1<<REFS0);//Select voltage ref AVCC with external capacitor at AREF pin (from table in datasheet)
	ADCSRA |=(1<<ADEN);//ADC Enable
	//ADC speed must be in range of 50k to 200k HZ
	ADCSRA |=(1<<ADPS2);//PRESCALER 16 --> freq = 62500 Hz (from table in datasheet)

}
int ADC_read(int ADC_chanel)
{
	int adc_value=0;


	ADMUX = (ADMUX&0xE0)|ADC_chanel;//choose which ADC will work
	//0xE0 ==> 0b11100000 to save previous value wh have used in ADC_init func 
	
	ADCSRA |=(1<<ADSC);//ADC Start Conversion
	
	while(readbit(ADCSRA,ADIF)==0) //wait until Conversion complete using polling not int
	{    
	}    // ADIF it will be 1 when Conversion complete
	
	
	_delay_us(10); // white until value store in ADC reg
	
	// ADLAR VALUE = 0 
	adc_value =(int)ADCL+(int)ADCH*256; //calculate the ADC value
	//adc_value = ADCL | (ADCH<<8);

	return adc_value ;
	
}
