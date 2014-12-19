/*
 * PotentioMeter.h
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#ifndef CONTROLLERS_POTENTIOMETER_H_
#define CONTROLLERS_POTENTIOMETER_H_

#include "Arduino.h"

class PotentioMeter {
	private:
		byte pin;
		void ( *callback )( void );
		int lastVal;
	public:
		PotentioMeter(byte);
		void setValueChangeCallback(void( * )( void ));
		void update();
		int getValuePersentage();
		int getRawValue();
};

#endif /* CONTROLLERS_POTENTIOMETER_H_ */
