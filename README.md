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

17/01/2021 Bè. ho hem conseguit. ara podem fer servir els timers 1, 3, 4 i 5. El problema es que si volem que funcioni amb el atmega 328p, ens haurem de conformar amb el input capture register per mesurar el periode. Si bè es veritat que podriem fer servir un sol timer i anar canviant el source clock, em sembla una solució poc efectiva. En canvi, seria millor utilitzar el clock del sistema per mesurar la frequència. D'aquesta manera, el fet de tenir un temps de mostreig no tant constant no afecta. Anem a implementar-ho. Ara farem servir el timer 0 per les interrupcions. Que collons, anem a fer servir el timer 2.

OOOOO deu meu... coses: Exemple: per accedir al TCCR2A, accedim a la adreça 0xB0. El nostre estimat iom_328P.h, on estan definides totes aquestes coses, fa servir uns MACROS raros de collons per assignar totes aquestes addreçes dels SFR.  El compilador interpreta aquestes adreçes com a `volatile unsigned char * ` Fins ara, he provat de fer servir bitfields per tocar aquestes coses. Crec que el mes adient abans de res es parar, tornar enrere, i fer servir el codi en el mega, provar que funciona. Un cop tenim això, canviarem alguna cosa fent servir els bitfields. Si funciona, llavors passarem a implementar la classe del Timer 2.