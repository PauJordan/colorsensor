/*
 * color.h
 *
 *  Created on: 3 de gen. 2021
 *      Author: pau
 */

#ifndef COLOR_H_
#define COLOR_H_
#include "Arduino.h"

#define F_500_KHz 3
#define F_100_KHz 1
#define F_10_KHz 2
#define F_off 0

#define RED 0
#define BLUE 2
#define CLEAR 1
#define GREEN 3



class TCS3200 {
public:
	TCS3200(volatile unsigned char *port, volatile unsigned char *DDRx, const uint8_t *sensorPinMap);
	void setup(uint8_t f);
	void toggle();
	void on();
	void off();
	void select_filter(uint8_t n);
	void select_frequency(uint8_t n);
private:
	volatile uint8_t *port;
	volatile uint8_t *DDRx;
	void setBit(uint8_t bit);
	void flipBit(uint8_t bit);
	void clearBit(uint8_t bit);
	const uint8_t *sensorPinMap;

};



#endif /* COLOR_H_ */
