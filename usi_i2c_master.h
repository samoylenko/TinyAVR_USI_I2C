/*
 * usi_i2c_master.h
 *
 * Created: 3/13/2017 10:56:17 PM
 *  Author: pm
 */ 

#ifndef USI_I2C_MASTER_H_
#define USI_I2C_MASTER_H_

#include <avr/io.h>
#include <avr/cpufunc.h>

#include <stdint.h>


// ACK not received
#define USI_I2C_NACK 0
// ACK received
#define USI_I2C_ACK 1
// Timeout waiting for SCL to be released
#define USI_I2C_SCL_BUSY 2
// Timeout waiting for SDA to be released
#define USI_I2C_SDA_BUSY 3

#define USI_I2C_WRITE 0
#define USI_I2C_READ  1

#define USI_I2C_ADDR( addr, mode ) ( ( addr << 1 ) | mode )

void USI_I2C_Init();
void USI_I2C_Start();
void USI_I2C_Stop();
uint8_t USI_I2C_SendByte( uint8_t);



#endif /* USI_I2C_MASTER_H_ */