/*
 * Button.h
 *
 *  Created on: 1 dec. 2014
 *      Author: Sijmen
 */

#ifndef CONTROLLERS_BUTTON_H_
#define CONTROLLERS_BUTTON_H_

#include "Arduino.h"

class Button{
	private:
		/**
		 * de digital pin op de arduino
		 */
		byte pin;

		/**
		 * de huidigge status van de knop
		 */
		bool state;

		/**
		 * de functie die moet worden aangeroepen bij verandering van status
		 */
		void ( *callback )( void );
	public:

		/**
		 * constructor met de pin als argument
		 */
		Button(byte);

		/**
		 * zet de veranderings callback
		 */
		void setCallback(void ( * )( void ));

		/**
		 * update de button. Zo vaak mogelijk aanroepen!
		 */
		void update();

		/**
		 * wat is de huidigge status van de knop?
		 */
		bool getState();

};

class AntiBounceButton{
	private:
		/**
		 * de digital pin op de arduino
		 */
		byte pin;

		/**
		 * aantal ms dat er gechecked moet worden op problemen
		 */
		byte msBounceCheck = 10;

		/**
		 * wanneer is er gestart met checken?
		 */
		unsigned long bounceCheckStart;

		/**
		 * de functie die moet worden aangeroepen bij verandering van status
		 */
		void ( *callback )( void );

		/**
		 * de verschillende statussen vna de antibounce button
		 */
		enum State{PRESSED, RELEASED, BOUNCE_TO_RELEASE, BOUNCE_TO_PRESS} state;
	public:

		/**
		 * constructor met de pin als argument
		 */
		AntiBounceButton(byte);

		/**
		 * zet de veranderings callback
		 */
		void setCallback(void ( * )( void ));

		/**
		 * update de button. Zo vaak mogelijk aanroepen!
		 */
		void update();

		/**
		 * wat is de huidigge status van de knop?
		 */
		bool getState();

		/**
		 * hoe lang is de tijd dat gechecedmoet worden?
		 */
		void setBounceTimeout(byte);
};
#endif
