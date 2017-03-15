An attempt to create a TinyAVR library for TWI (I2C) communication which uses USI hardware.  
The hardware I am using is ATtiny85, but should be compatible with other TinyAVRs.
  
Currently at a very early stage - note the frequency slowdown at the screenshot, it was over 100khz before moved to a separate c file with header (MCU frequency is 1Mhz)  
  
Being tested at a real hardware (ATtiny85) with a real oscilloscope - I was not satisfied with USI support in AtmelStudio simulator.  
  
Discoveries so far:  
1. USI won't use SDA if a corresponding PORTx bit is not set to HIGH. Just in case, ensure doing the same with SCL (DDRx bit also must be set to output for both).  
2. Notably, in TWI (I2C) mode USI when SDA or SCL are released, they are not set as HIGH, and they produce no voltage. I find this a huge benefit of using USI instead of just PORTx/DDRx  
  
![Screenshot1](/_pictures/1.png)  