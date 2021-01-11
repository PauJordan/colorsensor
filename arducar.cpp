#include "arducar.h"

#define S0_bit 4
#define S2_bit 6
#define OE_bit 3
#define MOS_bit 2

#define INT2_ICSpos 4
#define INT2_EIMSKpos 2

const uint8_t sensorPinsMap[] = {S0_bit, S2_bit, OE_bit, MOS_bit};
TCS3200 sensor(&PORTA, &DDRA, sensorPinsMap);
Timer counter(&TCNT5, &TCCR5A, &TCCR5B);
Timer timer(&TCNT4, &TCCR4A, &TCCR4B);

//Interrupció boto.
volatile bool but = false;
ISR(INT2_vect){
	but = true;
}
volatile bool timer_ovf = false;
ISR(TIMER4_COMPA_vect){
	timer_ovf = true;
}

void printRegister(const char *name, unsigned int value){
	Serial.print(name);
	Serial.print(" = ");
	Serial.println(value);
}
void setup()
{
	pinMode(19, INPUT_PULLUP);
	sensor.setup(F_500_KHz);
	sensor.on();
	delay(10);
	//sensor.off();
	counter.set_mode(NORMAL);
	counter.select_clock(EXTERNAL_NE);
	//Interrupt freq = sys_clk/(2*presc*(OCRnA+1)) = 16e6/(2*1024*(77+1) = 100,81 Hz
	timer.set_mode(CTC_OCRnA);
	OCR4A = 256;
	TIMSK4 |= 1 << 1; //Enable timer 4 interrupt
	timer.select_clock(SYS_1024);

	//testing
	pinMode(6, OUTPUT);
	timer.set_OC_mode(A, TOGGLEonCM);

	//Interrupts
	EICRA &= ~(2 << INT2_ICSpos);
	EICRA |= 2 << INT2_ICSpos;
	EIMSK |= 1 << INT2_EIMSKpos;
	sei();
	Serial.begin(921600);
}


void loop()
{
	if(but){
		delay(50);
		if(!digitalRead(19)){
			sensor.toggle();
		};
		delay(150);
		counter.clear();
		but = 0;
	}
	if(timer_ovf and sensor.get_state()){
		plot(counter.reset());
		Serial.println();
		timer_ovf = false;
	}

}
