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

Timer::Timer(TimerRegisters timreg ) :
	timreg(timreg),
	TCNTn(timreg.TCNTn),
	TCCRnA(timreg.TCCRnA),
	TCCRnB(timreg.TCCRnB),
	OCRnA(timreg.OCRnA)
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
	return read_16(TCNTn);
}

void Timer::write(uint16_t i){
	write_16(TCNTn, i);
}

unsigned int Timer::reset(){
	//Recupera el valor al comptador i el torna a 0. 16 bits. Operació atòmica.
	return swap_16(timreg.TCNTn, 0);
}
void Timer::clear(){
	write_16(TCNTn, 0);
}

void Timer::set_OC_mode(OC_channel ch, uint8_t mode){
	uint8_t bitpos = COMnA0_position - 2*ch;
	*TCCRnA &= ~(0b11 <<  bitpos);
	*TCCRnA |= (0b11 & mode) << bitpos;
}

void Timer::set_OC_value(OC_channel ch, uint16_t value){
	volatile uint16_t* OCRnX;
	switch(ch){
	case A: OCRnX = OCRnA; break;
	default: break;
	}
	write_16(OCRnX, value);
}
//Private:

uint16_t Timer::read_16(volatile uint16_t* addr){
	//Llegeix el valor del comptador. Registre 16-bits operació atòmica.
	uint8_t sreg;
	uint16_t value;
	sreg = SREG; //Save global interrupt flag
	cli();
	value = *addr;
	SREG = sreg; //Restore global interrupt flag
	return value;
}

void Timer::write_16(volatile uint16_t* addr, uint16_t value){
	//Escriu un valor al comptador. 16 bits. Operació atòmica.
	uint8_t sreg;
	sreg = SREG; //Save global interrupt flag
	cli();
	*addr = value;
	SREG = sreg; //Restore global interrupt flag
}


uint16_t Timer::swap_16(volatile uint16_t* addr, uint16_t value){
	//Llegeix el valor del comptador. Registre 16-bits operació atòmica.
	uint8_t sreg;
	uint16_t old_value;
	sreg = SREG; //Save global interrupt flag
	cli();
	old_value = *addr;
	*addr = value;
	SREG = sreg; //Restore global interrupt flag
	return old_value;
}




