/*
 * AVRtimer.cpp
 *	Aquesta classe permet utilitzar els timers de 16 bits de la cpu avr.
 *  Created on: 4 de gen. 2021
 *      Author: pau
 */
#include "AVRtimer.h"

#define WGMn1_0_position 0
#define WGMn3_2_position 3
#define CSn2_0_position 0

#define COMnA0_position 6

Timer::Timer(volatile uint16_t *TCNTn, volatile uint8_t *TCCRnA, volatile uint8_t *TCCRnB) :
	TCNTn(TCNTn),
	TCCRnA(TCCRnA),
	TCCRnB(TCCRnB)
	{
	write(0);
	set_mode(HALT);
}

void Timer::set_mode(unsigned char mode){
	//Canvia el mode d'operació del timer. Els bits WGM3:0 estan separats en dos parelles en els registres TCCRnA i B.
	*TCCRnA &= ~(0b11 << WGMn1_0_position);
	*TCCRnA |= (0b11 & mode) << WGMn1_0_position;

	*TCCRnB &= ~(0b11 << WGMn3_2_position);
	*TCCRnB |= (0b11 & (mode >> 2)) << WGMn3_2_position;
}

void Timer::select_clock(unsigned char clk_sel){
	//Selecciona el clock d'entrada.
	*TCCRnB &= ~(0b111 << CSn2_0_position);
	*TCCRnB |= (0b111 & clk_sel) << CSn2_0_position;

}

unsigned int Timer::read(){
	unsigned char sreg;
	unsigned int i;
	//Llegeix el valor del comptador. Registre 16-bits operació atòmica.
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts globally */
	cli();
	/* Read TCNTn into i */
	i = *TCNTn;
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
	cli();
	/* Read TCNTn into i */
	*TCNTn = i;
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
	cli();
	/* Read TCNTn into i */
	i = *TCNTn;
	*TCNTn = 0;
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}
void Timer::clear(){
	//Posa el comptador a 0.
	/* Save global interrupt flag */
	unsigned char sreg = SREG;
	/* Disable interrupts globally */
	cli();
	*TCNTn = 0;
	/* Restore global interrupt flag */
	SREG = sreg;
}

void Timer::set_OC_mode(uint8_t channel, uint8_t mode){
	uint8_t bitpos = COMnA0_position - 2*channel;
	*TCCRnA &= ~(0b11 <<  bitpos);
	*TCCRnA |= (0b11 & mode) << bitpos;
}



