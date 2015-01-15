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
		/**
		 * maximaal rauwe waarde van de ldr
		 */
		static const int max = 1020;

		/**
		 * minimale rauwe waarde van ldr
		 */
		static const int min = 1;

		/**
		 * laatst doorgegeven waarde aan callback
		 */
		int lastVal;

		/**
		 * fizieke pin op de arduino waar de ldr is aangesloten
		 */
		byte pin;

		/**
		 * functie die wordt aangeroepen
		 */
		void ( *callback )( void );
	public:
		/**
		 * constructor. arument is de pin op de arduino
		 */
		LightDependentResistor(byte);

		/**
		 * Zet de functie die moet worden aangeroepen bij verandering van
		 * lichtsterkte
		 */
		void setValueChangeCallback(void( * )( void ));

		/**
		 * deze functie moet zo vaak mogelijk worden aangeroepen.
		 * Hier wordt de callback checks gedaan.
		 */
		void update();

		/**
		 * geef mij het huidigge lux value. Lux gaat tussen 0 en 100
		 */
		int getLuxValue();

		/**
		 * geef mij het rauwe licht value. Dit getal gaat tussen min en max
		 */
		int getRawValue();
};

#endif /* CONTROLLERS_LDR_H_ */
