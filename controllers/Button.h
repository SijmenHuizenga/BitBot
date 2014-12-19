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
		byte pin;  //digital
		bool state;
		void ( *callback )( void );
	public:
		Button(byte);
		void setCallback(void ( * )( void ));
		void update();
		bool getState();

};

class AntiBounceButton{
	private:
		byte pin;
		byte msBounceCheck;
		unsigned long bounceCheckStart;
		void ( *callback )( void );
		enum State{PRESSED, RELEASED, BOUNCE_TO_RELEASE, BOUNCE_TO_PRESS} state;
	public:
		AntiBounceButton(byte);
		void setCallback(void ( * )( void ));
		void update();
		bool getState();
		void setBounceTimeout(byte);
};
#endif
