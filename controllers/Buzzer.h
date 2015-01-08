/*
 * Buzzer.h
 *
 *  Created on: 8 jan. 2015
 *      Author: Sijmen
 */

#ifndef CONTROLLERS_BUZZER_H_
#define CONTROLLERS_BUZZER_H_

#include "Arduino.h"

class Buzzer {
	private:
		byte pin;

		unsigned int toneHz;
		unsigned int onTime;
		unsigned int offTime;

		bool onOrOff;
		unsigned long lastUpdate;
	public:
		Buzzer(byte pin);
		void setTone(unsigned int);
		void setOnTime(unsigned int);
		void setOffTime(unsigned int);

		void update();
};



#endif /* CONTROLLERS_BUZZER_H_ */
