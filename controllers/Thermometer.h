/*
 * Thermometer.h
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#ifndef CONTROLLERS_THERMOMETER_H_
#define CONTROLLERS_THERMOMETER_H_

#include "Arduino.h"

class Thermometer{
	private:
		byte pin;
		int lastVal;
		static const int deg0 = 560;
		static const int deg22 = 369;
		void ( *callback )( void );
	public:
		Thermometer(byte);
		void setValueChangeCallback(void( * )( void ));
		void update();
		int getCurDegrees();
		int getRawValue();
};

#endif /* CONTROLLERS_THERMOMETER_H_ */
