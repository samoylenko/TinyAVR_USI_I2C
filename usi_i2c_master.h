#ifndef USI_I2C_MASTER_H_
#define USI_I2C_MASTER_H_

//==============================================================================

#include <avr/io.h>
#include <avr/cpufunc.h>

#include <stdint.h>

//------------------------------------------------------------------------------
// Custom definitions

// ACK not received
#define USI_I2C_NACK		0
// ACK received
#define USI_I2C_ACK			1
// Timeout waiting for SCL to be released
#define USI_I2C_SCL_BUSY	2

// Write mode
#define USI_I2C_WRITE		0
// Read mode
#define USI_I2C_READ		1

//------------------------------------------------------------------------------
// Macro definitions

// Macro to generate a byte with slave address and data direction
#define USI_I2C_ADDR(addr, mode) ((addr << 1) | mode)

//------------------------------------------------------------------------------
// Function prototypes

void USI_I2C_Init();
void USI_I2C_Start();
void USI_I2C_Stop();
uint8_t USI_I2C_SendByte(uint8_t);

//==============================================================================

#endif /* USI_I2C_MASTER_H_ */