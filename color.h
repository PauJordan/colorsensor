/*
 * color.h
 *
 *  Created on: 3 de gen. 2021
 *      Author: pau
 */

#ifndef COLOR_H_
#define COLOR_H_
#include "Arduino.h"

class TCS3200 {
public:
	TCS3200(volatile unsigned char *port);
	int setup();
	void toggle();
	void on();
	void off();

private:
	volatile uint8_t *port;
	void setBit(uint8_t bit);
	void flipBit(uint8_t bit);
	void clearBit(uint8_t bit);

};

class Timer {
public:
	Timer(volatile uint16_t *TCNTn, volatile uint8_t *TCCRnA, volatile uint8_t *TCCRnB);
	void setup(bool external, uint8_t prescbits);
	unsigned int read();
	void reset();
private:
	volatile uint8_t *TCCRnA;
	volatile uint8_t *TCCRnB;
	volatile uint16_t *TCNTn;
};


#endif /* COLOR_H_ */
