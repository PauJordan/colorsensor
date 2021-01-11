/*
 * Timer.h
 *
 *  Created on: 4 de gen. 2021
 *      Author: pau
 */

#ifndef AVRTIMER_H_
#define AVRTIMER_H_
#include "Arduino.h"

//Clock source. Bits CSn2:0 atmega2560 datasheet 17.11
#define HALT		0
#define SYS			1
#define SYS_8		2
#define SYS_64		3
#define SYS_256		4
#define SYS_1024	5
#define EXTERNAL_NE	6
#define EXTERNAL_PE 7

//Mode of operation. Bits WGMn3:0 atmega2560 datasheet 17.11
#define NORMAL		0
#define PWM_PC_8	1
#define PWM_PC_9	2
#define PWM_PC_10	3
#define CTC_OCRnA	4
#define FPWM_8		5
#define FPWM_9		6
#define FPWM_10		7
#define PWM_FPC_ICRn	8
#define PWM_FPC_OCRnA	9
#define PWM_PC_ICRn		10
#define PWM_PC_OCRnA	11
#define CTC_ICRn		12
#define FPWM_ICRn		14
#define FPWM_OCRnA		15

class Timer {
public:
	Timer(volatile uint16_t *TCNTn, volatile uint8_t *TCCRnA, volatile uint8_t *TCCRnB);
	void select_clock(unsigned char clk_sel);
	void set_mode(unsigned char mode);
	unsigned int read();
	unsigned int reset();
	void clear();
	void write(uint16_t i);
private:
	volatile uint16_t *TCNTn;
	volatile uint8_t *TCCRnA;
	volatile uint8_t *TCCRnB;

};




#endif /* AVRTIMER_H_ */
