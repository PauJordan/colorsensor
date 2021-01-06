/*
 * AVRtimer.cpp
 *	Aquesta classe permet utilitzar els timers de 16 bits de la cpu avr.
 *  Created on: 4 de gen. 2021
 *      Author: pau
 */
#include "AVRtimer.h"

Timer::Timer(volatile uint16_t *TCNTn, volatile uint8_t *TCCRnA, volatile uint8_t *TCCRnB){
	this->TCNTn = TCNTn;
	this->TCCRnA = TCCRnA;
	this->TCCRnB = TCCRnB;
}
void Timer::setup(bool external, uint8_t prescbits, uint8_t mode){
	//Configura el timer
	if (external) { //Si la font de clock es externa, configuració del registre TTCRnB. El prescaler no te efecte, limitem 1 o 0 per seleccionar edge.
		if(prescbits > 1) prescbits = 1;
		*(this->TCCRnB) = 0x06 + prescbits;
	}
	else
		*(this->TCCRnB) = prescbits;
	this->setMode(mode);
}

void Timer::setMode(unsigned char mode){
	//Canvia el mode d'operació del timer
	*(this->TCCRnA) = mode;
}

unsigned int Timer::read(){
	unsigned char sreg;
	unsigned int i;
	//Llegeix el valor del comptador. Registre 16-bits operació atòmica.
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

void Timer::write(uint16_t i){
	//Escriu un valor al comptador. 16 bits. Operació atòmica.
	unsigned char sreg;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts globally */
	SREG &= ~(1 << 7);
	/* Read TCNTn into i */
	*(this->TCNTn) = i;
	/* Restore global interrupt flag */
	SREG = sreg;
}

unsigned int Timer::reset(){
	//Recupera el valor al comptador i el torna a 0. 16 bits. Operació atòmica.
	unsigned char sreg;
	unsigned int i;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts globally */
	SREG &= ~(1 << 7);
	/* Read TCNTn into i */
	i = *(this->TCNTn);
	*(this->TCNTn) = 0;
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}
void Timer::clear(){
	//Posa el comptador a 0.
	/* Save global interrupt flag */
	unsigned char sreg = SREG;
	/* Disable interrupts globally */
	SREG &= ~(1 << 7);
	*(this->TCNTn) = 0;
	/* Restore global interrupt flag */
	SREG = sreg;
}




