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

For uno:
TC3200 <->   atmega328p 
OUT			->  PD5 (5) Timer/Counter5 Clock Input (Datasheet 13.3.11) (328p[PD5] Datasheet 13.3.3)  
S0			<-	PB0 (8)  
S1			<-	PB1 (9)  
S2			<-	PB2 (10)  
S3			<-	PB3 (11)  
OE			<-	PB4 (12)  

MOSFET Gate <- PB5 (13) 
  
![alt text](http://paupro.ddns.net/downloads/mega_pinout.png)

Timer, es provarà d'utilitzar el input capture per mesurar la... fuckit. Ho farem configurable.
