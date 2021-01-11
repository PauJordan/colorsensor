/*
 * color.cpp
 *
 *  Created on: 3 de gen. 2021
 *      Author: pau
 *      S0 -> PA4 (26)
		S1 -> PA5 (27)
		S2 -> PA6 (28)
		S3 -> PA7 (29)
		OE -> PA3 (25)
MOSFET 	   <- PA2 (24)
 */
//bits order in pin mapping
#define S0 0
#define S2 1
#define OE 2
#define MOS 3
#define ctrl_pins_qty 4

#include "color.h"

TCS3200::TCS3200(volatile uint8_t* port, volatile unsigned char *DDRx, const uint8_t *sensorPinMap) :
	port(port),
	DDRx(DDRx),
	sensorPinMap(sensorPinMap),
	state(0)
	{
		off();
}
void TCS3200::setup(uint8_t f) {
		uint8_t mask = 0;
		for(unsigned char i = 0; i < ctrl_pins_qty; i++){ //Construeix la mascara per configurar els pins com a outputs
			mask |= 1 << sensorPinMap[i];
		}
		mask |= 3 << sensorPinMap[S0]; //Aquests pins van en parella
		mask |= 3 << sensorPinMap[S2];
		off();
		select_frequency(f);
		select_filter(CLEAR);
		*(DDRx) |= mask; //posa els pins seleccionats en mode output.
}

void TCS3200::setBit(uint8_t bit){
	*port |= 1 << sensorPinMap[bit];
};
void TCS3200::flipBit(uint8_t bit){
	*port ^= 1 <<  sensorPinMap[bit];
};
void TCS3200::clearBit(uint8_t bit){
	*port &= ~(1 <<  sensorPinMap[bit]);
};

void TCS3200::toggle(){
	flipBit(MOS);
	flipBit(OE);
	state = !state;
}

void TCS3200::select_filter(uint8_t n){
	*port &= ~(3 << sensorPinMap[S2]);
	*port |= n << sensorPinMap[S2];
}

void TCS3200::select_frequency(uint8_t n){
	*port &= ~(3 << sensorPinMap[S0]);
	*port |= n << sensorPinMap[S0];
}

void TCS3200::on(){
	setBit(MOS);
	clearBit(OE);
	state = 1;
}

void TCS3200::off(){
	clearBit(MOS);
	setBit(OE);
	state = 0;
}
bool TCS3200::get_state(){
	return state;
}


