#include "EEprom.h"

void EEPROM_INIT()
{
	I2C_Init();
}
void EEPROM_Write(char page , char add ,char data)
{
	char page_add = (page<<1)+0xA0;
	I2C_Start(page_add);			/* Start I2C with device write address */
	I2C_Write(add);					/* Write start memory address for data write */
	I2C_Write(data);
	_delay_ms(10);
	I2C_Stop();					/* Stop I2C */
}
char EEPROM_Read(char page , char add)
{
	char data =0;
	char page_write_add = (page<<1)+0xA0;
	char page_read_add  = page_write_add + 1;
	_delay_ms(10);
	I2C_Start(page_write_add);							/* Start I2C with device write address */
	I2C_Write(add);							/* Write start memory address */
	I2C_Repeated_Start(page_read_add);			/* Repeat start I2C SLA+R */
	data = I2C_Read_Ack();
	I2C_Stop();
	return data;							/* Stop I2C */
}

void I2C_Init()
{
	TWBR = BITRATE(TWSR=0x00);	// Get bit rate register value by formula
}
char I2C_Start(char address)// 0x20 -----> 0010 0001
{
	char status;
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate START					*/
	while(readbit(TWCR,TWINT)==0);			/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status!=0x08)						/* Check weather START transmitted or not?		*/
	return 0;								/* Return 0 to indicate start condition fail	*/
	TWDR= address;							/* Write SLA+W in TWI data register				*/
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI & clear interrupt flag			*/
	while(readbit(TWCR,TWINT)==0);			/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register */
	if(status==0x18)						/* Check for SLA+W transmitted &ack received	*/
	return 1;								/* Return 1 to indicate ack received			*/
	if(status==0x20)						/* Check for SLA+W transmitted &nack received	*/
	return 2;								/* Return 2 to indicate nack received			*/
	else
	return 3;								/* Else return 3 to indicate SLA+W failed		*/
}
char I2C_Repeated_Start(char read_address)
{
	char status;							/* Declare variable								*/
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate start					*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status!=0x10)						/* Check for repeated start transmitted			*/
	return 0;								/* Return 0 for repeated start condition fail	*/
	TWDR=read_address;						/* Write SLA+R in TWI data register				*/
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI and clear interrupt flag			*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status==0x40)						/* Check for SLA+R transmitted &ack received	*/
	return 1;								/* Return 1 to indicate ack received			*/
	if(status==0x48)						/* Check for SLA+R transmitted &nack received	*/
	return 2;								/* Return 2 to indicate nack received			*/
	else
	return 3;								/* Else return 3 to indicate SLA+W failed		*/
}
char I2C_Write(char data)	/* I2C write function */
{
	char status;				/* Declare variable */
	TWDR=data;					/* Copy data in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;			/* Read TWI status register */ // 1111 1000
	if(status==0x28)			/* Check for data transmitted &ack received */
	return 0;					/* Return 0 to indicate ack received */
	if(status==0x30)			/* Check for data transmitted &nack received */
	return 1;					/* Return 1 to indicate nack received */
	else
	return 2;					/* Else return 2 for data transmission failure */
}

char I2C_Read_Ack()
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);	/* Enable TWI, generation of ack */
	while(readbit(TWCR,TWINT)==0);				/* Wait until TWI finish its current job */
	return TWDR;							/* Return received data */
}

char I2C_Read_Nack()
{
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;				/* Return received data */
}
void I2C_Stop()								/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);	/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));					/* Wait until stop condition execution */
}
