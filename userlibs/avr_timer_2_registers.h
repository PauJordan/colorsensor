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

//Clock source. Bits CSn2:0
#define T2_HALT			0
#define T2_SYS			1
#define T2_SYS_8		2
#define T2_SYS_32		3
#define T2_SYS_64		4
#define T2_SYS_128		5
#define T2_SYS_256		6
#define T2_SYS_1024		7


typedef struct {
	volatile uint8_t WGMn_10 : 2;
	volatile uint8_t  : 2; // COMnC no existeix al timer 2;
	volatile uint8_t COMnB : 2;
	volatile uint8_t COMnA : 2;

} RegTCCR2A ;



typedef struct {
	uint8_t CSn : 3;
	uint8_t WGMn_2 : 1;
	bool FOCnB : 1;
	bool FOCnA : 1;

} RegTCCR2B ;


typedef struct {
	bool TOIEn : 1;
	bool OCIEnA : 1;
	bool OCIEnB : 1;
	uint8_t : 5;



} RegTIMSK2;

struct Timer2_registers {
	volatile uint8_t* TCNTn;
	volatile uint8_t* TCCRnA;
	volatile uint8_t* TCCRnB;
	volatile uint8_t* OCRnA;
	volatile uint8_t* OCRnB;
	volatile uint8_t* ASSRaddr;
	volatile uint8_t* TIMSKn;
};



#endif /* USERLIBS_AVR_TIMER_2_REGISTERS_H_ */
