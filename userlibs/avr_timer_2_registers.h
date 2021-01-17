/*
 * atmel328p_timers.h
 *
 *  Created on: 17 de gen. 2021
 *      Author: pau
 */


#ifndef USERLIBS_AVR_TIMER_2_REGISTERS_H_
#define USERLIBS_AVR_TIMER_2_REGISTERS_H_
//Un altre dia implementarem això:
//Mode of operation for Timer 2 Bits WGMn2:0
#define T2_NORMAL		0
#define T2_PWM_PC_8		1
#define T2_CTC_OCRnA	2
#define T2_FPWM_8		3
#define T2_PWM_PC_OCRnA	5
#define T2_FPWM_OCRnA	7

typedef struct {
	volatile uint8_t COMnA : 2;
	volatile uint8_t COMnB : 2;
	volatile uint8_t  : 2; // COMnC no existeix al timer 2;
	volatile uint8_t WGMn_10 : 2;
} BitmapTCCR2A ;

typedef union {
	BitmapTCCR2A as_bits;
	volatile uint8_t as_byte;
} RegTCCR2A;

struct RegTCCR2B {
	bool FOCnA : 1;
	bool FOCnB : 1;
	uint8_t WGMn_2 : 1;
	uint8_t CSn : 3;
};

struct RegTCCRnC {
	bool FOCnA : 1;
	bool FOCnB : 1;
	bool FOCnC : 1;
	uint8_t : 5;
};

struct RegTIMSK2 {
	uint8_t : 5;
	bool OCIEnB : 1;
	bool OCIEnA : 1;
	bool TOIEn : 1;
};

struct Timer2_registers {
	volatile uint8_t* TCNTn;
	volatile RegTCCR2A* TCCRnA;
	volatile RegTCCR2B* TCCRnB;
	volatile uint8_t* OCRnA;
	volatile uint8_t* OCRnB;
	volatile uint16_t* ASSRaddr;
	volatile RegTIMSK2* TIMSKn;
};



#endif /* USERLIBS_AVR_TIMER_2_REGISTERS_H_ */
