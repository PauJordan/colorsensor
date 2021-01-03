# colorsensor

Objectiu: Sensor de color utilitzant TCS3200 i atmega328p/atmega2560  

Requeriments: fsample 100Hz x RGBW = 400 Hz.  

S'utilitza timer 1 com a comptador, timer 2 com a generador d'interrupts.  
For mega:  
TC3200 <-   atmega2560  
OUT			->  PL2 (47) Timer/Counter5 Clock Input (Datasheet 13.3.11) (328p[PD5] Datasheet 13.3.3)  
S0			->	PA4 (26)  
S1			->	PA5 (27)  
S2			->	PA6 (28)  
S3			->	PA7 (29)  
OE			->	PA3 (25)  

MOSFET Gate <- PA2 (24)  
![alt text](http://paupro.ddns.net/downloads/mega_pinout.png)
