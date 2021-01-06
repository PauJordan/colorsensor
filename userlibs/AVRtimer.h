/*
 * Timer.h
 *
 *  Created on: 4 de gen. 2021
 *      Author: pau
 */

#ifndef AVRTIMER_H_
#define AVRTIMER_H_
#include "Arduino.h"

#define NORMAL_COUNTER 0
#define NEG_EDGE 0
#define EXTERNAL_CLK 1



class Timer {
public:
	Timer(volatile uint16_t *TCNTn, volatile uint8_t *TCCRnA, volatile uint8_t *TCCRnB);
	void setup(bool external, uint8_t prescbits, uint8_t mode);
	void setMode(unsigned char mode);
	unsigned int read();
	unsigned int reset();
	void clear();
	void write(uint16_t i);
private:
	volatile uint8_t *TCCRnA;
	volatile uint8_t *TCCRnB;
	volatile uint16_t *TCNTn;
};




#endif /* AVRTIMER_H_ */
