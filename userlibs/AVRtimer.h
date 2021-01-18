/*
 * Timer.h
 *
 *  Created on: 4 de gen. 2021
 *      Author: pau
 */

#ifndef AVRTIMER_H_
#define AVRTIMER_H_
#include "Arduino.h"
#include "avr_timer_2_registers.h"

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



//Output compare match units
enum OC_channel : uint8_t {
	A = 0, B, C
};

//COMnX Compare Match Output Mode
#define OC_DISABLED 0
#define TOGGLEonCM 1
#define CLEARonCM 2
#define SETonCM 3

//Atmega328p patch
#ifndef OCR1C
#define OCR1C OCR1B
#endif

#define TIMER_1 {&TCNT1, &TCCR1A, &TCCR1B, &TCCR1C, &OCR1A, &OCR1B, nullptr, &TIMSK1}
#define TIMER_3 {&TCNT3, &TCCR3A, &TCCR3B, &TCCR3C, &OCR3A, &OCR3B, &OCR3C, &TIMSK3}
#define TIMER_4 {&TCNT4, &TCCR4A, &TCCR4B, &TCCR4C, &OCR4A, &OCR4B, &OCR4C, &TIMSK4}
#define TIMER_5 {&TCNT5, &TCCR5A, &TCCR5B, &TCCR5C, &OCR5A, &OCR5B, &OCR5C, &TIMSK5}




struct TimerRegisters {
	volatile uint16_t* TCNTn;
	volatile uint8_t* TCCRnA;
	volatile uint8_t* TCCRnB;
	volatile uint8_t* TCCRnC;
	volatile uint16_t* OCRnA;
	volatile uint16_t* OCRnB;
	volatile uint16_t* OCRnC;
	volatile uint8_t* TIMSKn;
};



class Timer_base {
public:
	virtual void select_clock(unsigned char clk_sel);
	virtual void set_mode(unsigned char mode);
	virtual void set_OC_mode(OC_channel ch, uint8_t mode);
	virtual ~Timer_base();
};

class Timer : public Timer_base {
public:
	Timer(TimerRegisters timreg);
	TimerRegisters timreg;
	void select_clock(unsigned char clk_sel);
	void set_mode(unsigned char mode);
	unsigned int read() const;
	unsigned int reset();
	void clear();
	void write(uint16_t i);
	void set_OC_mode(OC_channel ch, uint8_t mode);
	void set_OC_value(OC_channel ch, uint16_t value);
private:
	volatile uint16_t *TCNTn;
	volatile uint8_t *TCCRnA;
	volatile uint8_t *TCCRnB;
	volatile uint16_t *OCRnA;
	uint16_t read_16(volatile uint16_t* addr) const;
	void write_16(volatile uint16_t* addr, uint16_t value);
	uint16_t swap_16(volatile uint16_t* addr, uint16_t value);
};


#define TIMER_2 { &TCNT2, &TCCR2A, &TCCR2B, &OCR2A, &OCR2B, &ASSR, &TIMSK2}




class Timer2 : public Timer_base {
public:
	Timer2(Timer2_registers tim2reg_addr);
	Timer2_registers tim2reg;
	void select_clock(unsigned char clk_sel);
	void set_mode(unsigned char mode);
	uint8_t read();
	uint8_t reset(uint8_t i);
	void clear();
	void write(uint8_t i);
	void set_OC_mode(OC_channel ch, uint8_t mode);
	void set_OC_value(OC_channel ch, uint8_t value);
	volatile RegTIMSK2* TIMSKn;
private:
	volatile RegTCCR2A* TCCRnA;
	volatile RegTCCR2B* TCCRnB;


};






#endif /* AVRTIMER_H_ */
