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
		/**
		 * de fizieke pin op de arduino
		 */
		byte pin;

		/**
		 * het laatst doorgegeven value aan de callback
		 */
		int lastVal;

		/**
		 * calibratie waarden: de rauwe waarde bij 0 graden
		 */
		static const int deg0 = 560;

		/**
		 * calibratie waarden: de rauwe waarde bij 22 graden
		 */
		static const int deg22 = 369;

		/**
		 * functie die moet  worden aangeroepen bij verandering temepratuur
		 */
		void ( *callback )( void );
	public:
		/**
		 * constructor. Arument is fizieke pin
		 */
		Thermometer(byte);

		/**
		 * zet functie die moet worden aangereoepen bij verandering licht
		 */
		void setValueChangeCallback(void( * )( void ));

		/**
		 * update. Moet zo vaak mogelijk worden aangeroepen
		 */
		void update();

		/**
		 * geef het aantal graden tussen 0 en 360
		 */
		int getCurDegrees();

		/**
		 * geef het rauwe value.
		 */
		int getRawValue();
};

#endif /* CONTROLLERS_THERMOMETER_H_ */
