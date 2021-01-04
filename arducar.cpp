// Do not remove the include below
#include "arducar.h"

//The setup function is called once at startup of the sketch
TCS3200 sensor = TCS3200(&PORTA);
Timer timer = Timer(&TCNT5, &TCCR5A, &TCCR5B);
volatile bool but = 0;
void ISR2(){
	but = 1;
}

void printRegister(const char *name, unsigned int value){
	Serial.print(name);
	Serial.print(" = ");
	Serial.println(value);
}
void setup()
{
	pinMode(19, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(19), ISR2, FALLING);
	sensor.setup();
	Serial.begin(115200);
	sensor.on();
	delay(10);
	sensor.off();
	timer.setup(true, 3);
}


void loop()
{
	if(but){
		delay(50);
		if(!digitalRead(19)){
			sensor.toggle();
		};
		delay(150);
		but = 0;
	}
	delay(100);
	Serial.println(timer.read());
	timer.reset();
}
