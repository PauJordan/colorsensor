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
#define S0_bit 4
#define S2_bit 6
#define OE_bit 3
#define MOS_bit 2

#include "color.h"

Timer::Timer(volatile uint16_t *TCNTn, volatile uint8_t *TCCRnA, volatile uint8_t *TCCRnB){
	this->TCNTn = TCNTn;
	this->TCCRnA = TCCRnA;
	this->TCCRnB = TCCRnB;
}
void Timer::setup(bool external, uint8_t prescbits){
	*(this->TCCRnA) = 0;
	if (external) {
		if(prescbits > 1) prescbits = 1;
		*(this->TCCRnB) = 0x06 + prescbits;
	}
	else
		*(this->TCCRnB) = prescbits;
}

unsigned int Timer::read(){
	unsigned char sreg;
	unsigned int i;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts globally */
	SREG &= ~(1 << 7);
	/* Read TCNTn into i */
	i = *(this->TCNTn);
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}
void Timer::reset(){
	/* Save global interrupt flag */
	unsigned char sreg = SREG;
	/* Disable interrupts globally */
	SREG &= ~(1 << 7);
	*(this->TCNTn) = 0;
	/* Restore global interrupt flag */
	SREG = sreg;
}

TCS3200::TCS3200(volatile unsigned char *port){
	this->port = port;
}
int TCS3200::setup() {
		DDRA =  0b11111100;
		PORTA = 0b11111000;
		return 0;
}

void TCS3200::setBit(uint8_t bit){
	*(this->port) |= 1 << bit;
};
void TCS3200::flipBit(uint8_t bit){
	*(this->port) ^= 1 << bit;
};
void TCS3200::clearBit(uint8_t bit){
	*(this->port) &= ~(1 << bit);
};

void TCS3200::toggle(){
	this->flipBit(MOS_bit);
}

void TCS3200::on(){
	this->setBit(MOS_bit);

}

void TCS3200::off(){
	this->clearBit(MOS_bit);
}
