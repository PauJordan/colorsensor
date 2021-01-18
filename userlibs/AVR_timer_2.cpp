/*
 * AVR_timer_2.cpp
 *
 *  Created on: 17 de gen. 2021
 *      Author: pau
 */

#include "AVRtimer.h"
#include <avr_timer_2_registers.h>



Timer2::Timer2(Timer2_registers tim2reg_addr) :
tim2reg(tim2reg_addr),
TCCRnA(reinterpret_cast <volatile RegTCCR2A*> (tim2reg.TCCRnA)),
TCCRnB(reinterpret_cast <volatile RegTCCR2B*> (tim2reg.TCCRnB)),
TIMSKn(reinterpret_cast <volatile RegTIMSK2*> (tim2reg.TIMSKn))
{


}

void Timer2::set_mode(unsigned char mode){
	//Canvia el mode d'operació del timer. Els bits WGM3:0 estan separats en dos parelles en els registres TCCRnA i B.
	TCCRnA->WGMn_10 = 0b11 & mode;
	TCCRnB->WGMn_2 = (0b100 & mode) >> 2;
	return;
}

void Timer2::select_clock(unsigned char clk_sel){
	//Selecciona el clock d'entrada.
	TCCRnB->CSn = clk_sel;

}

uint8_t Timer2::read(){
	return *(tim2reg.TCNTn);
}
void Timer2::write(uint8_t i){
	*(tim2reg.TCNTn) = i;
	return;
}
uint8_t Timer2::reset(uint8_t i){
	uint8_t old_i = *(tim2reg.TCNTn);
	*(tim2reg.TCNTn) = i;
	return old_i;
}
void Timer2::clear(){
	*(tim2reg.TCNTn) = 0;
	return;
}

void Timer2::set_OC_mode(OC_channel ch, uint8_t mode){
	switch(ch){
	case A: TCCRnA->COMnA = mode; break;
	case B: TCCRnA->COMnB = mode; break;
	default: break;
	}
	return;
}

void Timer2::set_OC_value(OC_channel ch, uint8_t value){
	switch(ch){
	case A: *(tim2reg.OCRnA) = value; break;
	case B: *(tim2reg.OCRnB) = value; break;
	default: break;
	}
	return;
}

