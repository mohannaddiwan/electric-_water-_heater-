#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>
#include "utily.h"
#include "clock.h"
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
#define SCL_CLK 10000

#include <math.h>



void I2C_Stop();
char I2C_Read_Nack();
char I2C_Read_Ack();

char I2C_Write(char data);
char I2C_Repeated_Start(char read_address) ;
char I2C_Start(char address);
void I2C_Init()	;

void EEPROM_Write(char page , char add ,char data);
char EEPROM_Read(char page , char add);
void EEPROM_INIT();



#endif 