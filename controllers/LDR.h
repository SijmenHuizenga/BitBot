/*
 * LDR.h
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#ifndef CONTROLLERS_LDR_H_
#define CONTROLLERS_LDR_H_

#include "Arduino.h"

class LightDependentResistor {
	private:
		static const int max = 1020;
		static const int min = 1;
		int lastVal;
		byte pin;
		void ( *callback )( void );
	public:
		LightDependentResistor(byte);
		void setValueChangeCallback(void( * )( void ));
		void update();
		int getLuxValue();
		int getRawValue();
};

#endif /* CONTROLLERS_LDR_H_ */
