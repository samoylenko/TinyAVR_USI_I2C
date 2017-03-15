/*
* Target MCU = ATTiny85(V)
*
* PB2 = SCL = USCK
* PB0 = SDA = DI
*/




/*

What we learned:
1) PORTB must be set to HIGH
2) It does not draw power in HIGH MODE! (WOW!)

*/


#define USI_PORT	PORTB
#define USI_DDR		DDRB
#define USI_SCL		PB2
#define USI_SDA		PB0

#include <avr/io.h>
#include "usi_i2c_master.h"

int main(void)
{
	//-[ Init ]----------------------------------------------------------------
	// Release lines - USI will ignore SDA if it's set to ground in USI_PORT
	USI_PORT |= _BV( USI_SDA ) | _BV( USI_SCL );
	
	// Set SDA and SCL pins to output
	USI_DDR |= _BV( USI_SDA ) | _BV( USI_SCL );
	USI_I2C_Init();

	//-[ Main cycle ]----------------------------------------------------------
	while (1)
	{
		
		//    TODO: rewrite start and stop into USI code
		USI_I2C_Start();
		uint8_t retval = USI_I2C_SendByte( USI_I2C_ADDR( 0x3C, USI_I2C_WRITE ) );
		retval = USI_I2C_SendByte( 0x33 );
		USI_I2C_Stop();
		
		
		//set_sleep_mode();
		//sei();
		//sleep_mode();
	}}
