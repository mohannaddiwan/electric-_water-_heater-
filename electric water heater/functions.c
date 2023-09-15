#include "functions.h"
#include "EEprom.h"
#include "ADC.h"

int sensed_num = 0;
char data=0;
enum HeaterState {
	OFF,
	ON
};
enum HeaterState heaterState = OFF;
int temperature = 60 ;
int btn_state = 0;


void Port_init(){
		DDRC = 0b10011101;
		DDRA = 0b01111111;
		DDRB = 255;
		setbit(DDRD,0);
}
unsigned char segment(char NO )
{
	
	switch(NO)
	{
		case 0:
		
		return 0b1000000;
		break;
		case 1:
		
		return 0b1111001;
		break;
		case 2:
		
		return 0b0100100;
		break;
		case 3:
		
		return 0b0110000;
		break;
		case 4:
		
		return 0b0011001;
		break;
		case 5:
		
		return 0b0010010;
		break;
		case 6:
		
		return 0b0000010;
		break;
		case 7:
		
		return 0b1111000;
		break;
		case 8:
		
		return 0b0000000;
		break;
		case 9:
		
		return 0b0010000;
		break;
		default:
		return 0b1111111;
		break;
	}

}

void _count (char count){
	char left = count/10;
	char right = count%10;

	PORTA=segment (right);
	PORTB=segment (left);
	_delay_ms(100);


}

void blink(int value){
	
	

		
		PORTA = 0b01111111;
		PORTB = 0b01111111;
		_delay_ms(100);
		_count(value);
		

	
}

void ctrl_btn(int blink_counter){
	btn_state++;
	while(btn_state > 0 )
	{
		if(blink_counter == 25){
			btn_state=0;
			
		}
		++blink_counter;
		
		blink(temperature);
		if(readbit(PINC,5) == 0){
			blink_counter=0;
			_delay_ms(10);
			_count(temperature);
			if(temperature < MAX_VALUE){
				temperature +=5;
				EEPROM_Write(1,0x12,temperature);

			}
		}
		if(readbit(PINC,6) == 0){
			blink_counter=0;
			_delay_ms(10);
			_count(temperature);

			if(temperature > MIN_VALUE){
				temperature -=5;
				EEPROM_Write(1,0x12,temperature);

			}
		}
		
		
	}
}

void turn_off(){
	clearbit(PORTC,2);
	clearbit(PORTC,7);
	clearbit(PORTC,4);
	clearbit(PORTC,3);
	_delay_ms(100);
	PORTA = 255;
	_delay_ms(50);
	PORTB = 255;
	btn_state=0;

}

void toggleHeaterState() {
	if (heaterState == 0) {
		heaterState = 1;
		} else {
		heaterState = 0;
	}
}


void start(){
	
		if (heaterState == ON) {
		data  = EEPROM_Read(1,0x12);
		temperature = data;
		unsigned long x = ADC_read(7); //Select chanel
		unsigned long res = (x*500)/1023; 
		setbit(PORTD,0);
		sensed_num++;
		
		if(sensed_num ==10){
			_count(res);
		if(res < (temperature - 5)){					
			setbit(PORTC,2);
			toggelbit(PORTC,7);
			_delay_ms(100);			

		}else{
		clearbit(PORTC,2);
	}
	
		
	 
	   if (res > (temperature + 5)){
			
			setbit(PORTC,3);
			setbit(PORTC,7);
			
			}else{
			clearbit(PORTC,7);
			clearbit(PORTC,3);
		}
		sensed_num=0;
 }
			
		if(readbit(PINC,5) == 0 || readbit(PINC,6) == 0){
			int static blink_counter = 0;
			ctrl_btn(blink_counter);
		}
		
		}else{
	   
	   turn_off();
	
	}
}