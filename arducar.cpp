#include "arducar.h"

#define S0_bit 4
#define S2_bit 6
#define OE_bit 3
#define MOS_bit 2


const uint8_t sensorPinsMap[] = {S0_bit, S2_bit, OE_bit, MOS_bit};
TCS3200 sensor = TCS3200(&PORTA, &DDRA, sensorPinsMap);
Timer counter = Timer(&TCNT5, &TCCR5A, &TCCR5B);
//Timer timer = Timer(&TCNT4, &TCCR4A, &TCCR4B);


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
	Serial.begin(115200);
	pinMode(19, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(19), ISR2, FALLING);
	sensor.setup(F_100_KHz);
	sensor.on();
	delay(10);
	sensor.off();
	counter.setup(EXTERNAL_CLK, NEG_EDGE, NORMAL_COUNTER);
	//timer.setup(false, 3);
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
	Serial.print(0);
	Serial.print(" ");
	Serial.println(counter.reset());
}
