/*
 * AVR_timer_2.cpp
 *
 *  Created on: 17 de gen. 2021
 *      Author: pau
 */

#include "AVRtimer.h"
#include <avr_timer_2_registers.h>



Timer2::Timer2(Timer2_registers tim2reg) : tim2reg(tim2reg) {
	// TODO Auto-generated constructor stub

}

void Timer2::set_mode(unsigned char mode){
	//Canvia el mode d'operació del timer. Els bits WGM3:0 estan separats en dos parelles en els registres TCCRnA i B.
	tim2reg.TCCRnA.WGMn_10 = 0b11 & mode;
	tim2reg.TCCRnB.WGMn_2 = (0b100 & mode) >> 2;
	return;
}

void Timer2::select_clock(unsigned char clk_sel){
	//Selecciona el clock d'entrada.
	tim2reg.TCCRnB.CSn = clk_sel;

}

uint8_t Timer2::read() const {
	return tim2reg.TCNTn;
}
void Timer::write(uint16_t i){

}
