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
		/**
		 * fiezieke pin op de arduino
		 */
		byte pin;

		/**
		 * de hoogte van de toon
		 */
		unsigned int toneHz;

		/**
		 * de lengte van het aan gedeelte van de toon
		 */
		unsigned int onTime;

		/**
		 * de lengte van het uit gedeelte van de toon
		 */
		unsigned int offTime;

		/**
		 * wether or not the tone is on
		 */
		bool onOrOff;

		/**
		 * het moment van de laatste update
		 */
		unsigned long lastUpdate;
	public:
		/**
		 * constructor: arument is de fizieke pin
		 */
		Buzzer(byte pin);

		/**
		 * zet de toonhoogte van de toon
		 */
		void setTone(unsigned int);

		/**
		 * zet de aan tijd van de toon
		 */
		void setOnTime(unsigned int);

		/**
		 * zet de uit tijd van de toon
		 */
		void setOffTime(unsigned int);

		/**
		 * update de Buzzer
		 */
		void update();
};



#endif /* CONTROLLERS_BUZZER_H_ */
