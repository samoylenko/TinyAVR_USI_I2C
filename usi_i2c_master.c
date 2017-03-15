/*
 * USI_I2C_Master.c
 *
 * Created: 3/13/2017 10:55:21 PM
 *  Author: pm
 */ 

#include "usi_i2c_master.h"

// TODO: Do we need NOPs and other means to implement delays?
// TODO: Return values in a fancy ENUM

void USI_I2C_Init()
{
	// Reset interrupt flags (release lines)
	USISR = _BV( USIOIF ) | _BV( USISIF );

	// Release SDA (set HIGH)
	USIDR |= ( 1 << 7 );
	
	// Enable USI TWI (I2C) mode
	USICR = _BV( USIWM1 );
	
	// P.S. Assumed we don't need an 'un-init' function in this code since I2C lines are unlikely to be disconnected during runtime
}

// TODO: Remove NOPs?
void USI_I2C_Start()
{
	/*
	* http://i2c.info/i2c-bus-specification
	* "... SCL has to be high. A high to low transition of SDA is considered as START ..."
	*
	* We expect that SCL is high at this point
	*/
	
	// Reset interrupt flags
	// USISR |= _BV( USIOIF ) | _BV( USISIF );

	// When this command runs, SDA switches to HIGH
	USIDR = 0b10000000;
	
	// Give it some time
	_NOP();
	
	// This command shifts USI Data Register left (SDA becomes LOW)
	USICR |= _BV( USICLK );
}

void USI_I2C_Stop()
{
	/*
	* http://i2c.info/i2c-bus-specification
	* "...SCL has to be high. ... SDA ... low to high transition as STOP."
	*
	* We expect that SCL is high at this point
	*
	*/
	
	// Reset interrupt flags
	// USISR |= _BV( USIOIF ) | _BV( USISIF );

	// When this command runs, SDA switches to LOW
	USIDR = 0b01111111;
	
	// Give it some time
	_NOP();
	
	// This command shifts USI Data Register left (SDA becomes HIGH)
	USICR |= _BV( USICLK );
}

uint8_t USI_I2C_SendByte( uint8_t data )
{
	/*
	* http://i2c.info/i2c-bus-specification
	* "For each clock pulse one bit of data is transferred. The SDA signal can only change when the SCL signal is low – when the clock is high the data should be stable."
	*
	* Assumed SCL is HIGH
	*
	* Returns:
	* 0 - ACK
	* 1 - NACK
	*/
	
	// Reset interrupt flags
	USISR |= _BV( USIOIF ) | _BV( USISIF );
	
	// Set counter to overflow after sending 7 bits ( Counter = 9 )
	// The below complexity is because we don't want to mess with user's interrupt flags
	USISR &= ~(  _BV( USICNT1 ) | _BV( USICNT2 ) );
	USISR |= _BV( USICNT3 ) | _BV( USICNT0 );

	// TODO: WAIT UNTIL SCL is LOW / SET LOW
	// TODO: this probably has to be smart (LOW check on SCL)
	// SCL = low
	USICR |= _BV( USITC );

	// DR = data, and the SDA now represents the MSB (Most Significant Bit)
	USIDR = data;
	
	// SCL = HIGH --> First bit sent manually
	USICR |= _BV( USITC );
	
	_NOP();

	// TODO: Check the comment below validity after implementing a slave address, restart condition etc
	// Not using USI counter here because the plans is to make this custom
	do
	{
		// SCL = LOW
		USICR |= _BV( USITC );
		
		// Shift data register left (this increments counter in USISR)
		USICR |= _BV( USICLK );
		
		// SCL = HIGH
		USICR |= _BV( USITC );
		
		// Some CPU cycles will pass due to the loop code
	} // repeat until USI counter overflows
	while( bit_is_clear( USISR, USIOIF ) );
	
	// Reading acknowledgment
	
	// SCL = LOW
	USICR |= _BV( USITC );

	// Release SDA (HIGH)
	USIDR = 0xff;
	
	// SCL = high
	USICR |= _BV( USITC );

	// Allow slave some time
	_NOP();
	
	// Shift data register left and keep SCL high
	USICR |= _BV( USICLK );
	
	// Use of USI Buffer register here to return ACK value
	// TODO: SCL remains high here?
	return ( USIBR & 1 );
	
	// TODO: return values / error codes for functions, ACK waiting true/false, # cycles to wait
}
