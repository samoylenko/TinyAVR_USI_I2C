/*
* Target MCU = ATTiny85(V)
* Frequency = 1 Mhz
*
* PB2 = SCL = USCK
* PB0 = SDA = DI
*/

#define USI_PORT	PORTB
#define USI_DDR		DDRB
#define USI_SCL		PB2
#define USI_SDA		PB0

#define SSD1306_RST PB3

#include <avr/io.h>
#include "usi_i2c_master.h"

void SSD1306_Init() 
{
		_NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
	
		// Power On Sequence SSD1603
		// SSD1306 reset pin = LOW
		PORTB &= ~( _BV( SSD1306_RST ) );
		
		// Set SSD1306 reset pin to output mode
		DDRB |= _BV( SSD1306_RST );
		
		_NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
		
		// SSD1306 reset pin = HIGH
		PORTB |= _BV( SSD1306_RST );
		
		_NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP(); _NOP();
		
		USI_I2C_SendByte( 0xAE );
		USI_I2C_SendByte( 0xD5 );
		USI_I2C_SendByte( 0x80 );
		USI_I2C_SendByte( 0xA8 );
		USI_I2C_SendByte( 31 );
		USI_I2C_SendByte( 0xD3 );
		USI_I2C_SendByte( 0 );
		USI_I2C_SendByte( 0x40 );
		USI_I2C_SendByte( 0x8D );
		USI_I2C_SendByte(  );
		USI_I2C_SendByte(  );
		USI_I2C_SendByte(  );
		USI_I2C_SendByte(  );

/*
  // Init sequence
  ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
  ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
  ssd1306_command(0x80);                                  // the suggested ratio 0x80

  ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
  ssd1306_command(SSD1306_LCDHEIGHT - 1);

  ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
  ssd1306_command(0x0);                                   // no offset
  ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0
  ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
  if (vccstate == SSD1306_EXTERNALVCC)
  { ssd1306_command(0x10); }
  else
  { ssd1306_command(0x14); }
  ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
  ssd1306_command(0x00);                                  // 0x0 act like ks0108
  ssd1306_command(SSD1306_SEGREMAP | 0x1);
  ssd1306_command(SSD1306_COMSCANDEC);

  #if defined SSD1306_128_32
  ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
  ssd1306_command(0x02);
  ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
  ssd1306_command(0x8F);

  #elif defined SSD1306_128_64
  ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
  ssd1306_command(0x12);
  ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
  if (vccstate == SSD1306_EXTERNALVCC)
  { ssd1306_command(0x9F); }
  else
  { ssd1306_command(0xCF); }

  #elif defined SSD1306_96_16
  ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
  ssd1306_command(0x2);   //ada x12
  ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
  if (vccstate == SSD1306_EXTERNALVCC)
  { ssd1306_command(0x10); }
  else
  { ssd1306_command(0xAF); }

  #endif

  ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
  if (vccstate == SSD1306_EXTERNALVCC)
  { ssd1306_command(0x22); }
  else
  { ssd1306_command(0xF1); }
  ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
  ssd1306_command(0x40);
  ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
  ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6

  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

  ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
	*/	
}


int main(void)
{
	//-----------------------------------------------------------------------------
	// Initialization
	
	// Release I2C lines - USI will ignore SDA if it's set to ground in USI_PORT
	USI_PORT |= _BV(USI_SDA) | _BV(USI_SCL);

	// Set SDA and SCL pins to output
	USI_DDR |= _BV(USI_SDA) | _BV(USI_SCL);
	USI_I2C_Init();
	
	SSD1306_Init();

	//-----------------------------------------------------------------------------
	// Main cycle
	while (1)
	{
		USI_I2C_Start();
		uint8_t retval = USI_I2C_SendByte(USI_I2C_ADDR(0x3C, USI_I2C_WRITE));
		retval = USI_I2C_SendByte(0xAF);
		USI_I2C_Stop();
	}
}

