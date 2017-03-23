An attempt to create a TinyAVR library for TWI (I2C) communication which uses USI hardware.  
The hardware I am using is ATtiny85, but should be compatible with other TinyAVRs.

It is being developed for use primarily with SSD1306 OLED display driver - main.c code will contain the code examples based on graphics.
  
Currently at a very early stage - note the frequency slowdown at the screenshot, it was over 100khz before moved to a separate c file with header (MCU frequency is 1Mhz)  
  
Being tested at a real hardware (ATtiny85) with a real oscilloscope - I was not satisfied with USI support in Atmel Studio simulator (but I am amazed with it's debugWire support!)
  
Important notes:  
1. USI won't use SDA if a corresponding PORTx bit is not set to HIGH. Just in case, ensure doing the same with SCL (DDRx bit also must be set to output for both).  
2. Notably, in USI TWI (I2C) mode, when SDA or SCL are released, corresponding pins are not set as HIGH, and they produce no voltage. I find this a huge benefit of using USI instead of just driving PORTx/DDRx  
3. The library does not provide checking of SCL state and waiting for slaves to release it - USI does not provide this capability, and it requires direct quering of PINx bit. Please refer to main.c for sample implementation.  
  
![Screenshot1](/_pictures/1.png)  