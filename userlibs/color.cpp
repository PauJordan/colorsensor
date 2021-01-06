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

TCS3200::TCS3200(volatile unsigned char *port, volatile unsigned char *DDRx, const uint8_t *sensorPinMap){
	this->port = port;
	this->DDRx = DDRx;
	this->sensorPinMap = sensorPinMap;
}
void TCS3200::setup(uint8_t f) {
		uint8_t mask = 0;
		for(unsigned char i = 0; i < ctrl_pins_qty; i++){ //Construeix la mascara per configurar els pins com a outputs
			mask |= 1 << this->sensorPinMap[i];
		}
		mask |= 3 << this->sensorPinMap[S0]; //Aquests pins van en parella
		mask |= 3 << this->sensorPinMap[S2];
		this->off();
		this->select_frequency(f);
		this->select_filter(CLEAR);
		*(this->DDRx) |= mask; //posa els pins seleccionats en mode output.
}

void TCS3200::setBit(uint8_t bit){
	*(this->port) |= 1 << this->sensorPinMap[bit];
};
void TCS3200::flipBit(uint8_t bit){
	*(this->port) ^= 1 <<  this->sensorPinMap[bit];
};
void TCS3200::clearBit(uint8_t bit){
	*(this->port) &= ~(1 <<  this->sensorPinMap[bit]);
};

void TCS3200::toggle(){
	this->flipBit(MOS);
	this->flipBit(OE);
}

void TCS3200::select_filter(uint8_t n){
	*(this->port) &= ~(3 << this->sensorPinMap[S2]);
	*(this->port) |= n << this->sensorPinMap[S2];
}

void TCS3200::select_frequency(uint8_t n){
	*(this->port) &= ~(3 << this->sensorPinMap[S0]);
	*(this->port) |= n << this->sensorPinMap[S0];
}

void TCS3200::on(){
	this->setBit(MOS);
	this->clearBit(OE);
}

void TCS3200::off(){
	this->clearBit(MOS);
	this->setBit(OE);
}
