/*
 * ButtonControl.cpp
 *
 *  Created on: 1 dec. 2014
 *      Author: Sijmen
 */

#include "Arduino.h"
#include "../controllers/Button.h"

Button::Button(byte digitalPin) {
	this->pin = digitalPin;
	this->state = false;
	this->callback = 0;
	pinMode(pin, INPUT);
}
void Button::update() {
	if(this->callback == 0)
		return;
	int s = digitalRead(pin);
	if (s == HIGH && this->state == false) {
		this->state = true;
		this->callback();
	} else if (s == LOW && this->state == true) {
		this->state = false;
		this->callback();
	}
}
void Button::setCallback(void ( *callback )( void )) {
	this->callback = callback;
}

bool Button::getState(){
	return state;
}

///////////////////////
//Anti Bounce Button///
///////////////////////

AntiBounceButton::AntiBounceButton(byte pin){
	this->pin = pin;
	this->callback = 0;
	this->state = RELEASED;
	this->msBounceCheck = 10;
	this->bounceCheckStart = 0;
	pinMode(this->pin, INPUT);
}

void AntiBounceButton::setCallback(void ( *callback )( void )) {
	this->callback = callback;
}

void AntiBounceButton::setBounceTimeout(byte newVal){
	this->msBounceCheck = newVal;
}

bool AntiBounceButton::getState(){
	//als hij los is of hij is bezig met los laten, dan is de state false.
	//want op dit moment is hij niet ingedrukt.
	return state == RELEASED || state == BOUNCE_TO_PRESS ? false : true;
}

void AntiBounceButton::update() {
	bool s = digitalRead(pin);
	unsigned long curMils = millis() & 0XFF;
	if(state == RELEASED && s == HIGH){
		state = BOUNCE_TO_PRESS;
		bounceCheckStart = curMils;
	}else if(state == PRESSED && s == LOW){
		state = BOUNCE_TO_RELEASE;
		bounceCheckStart = curMils;
	}else if(state == BOUNCE_TO_PRESS &&
			curMils - bounceCheckStart >= msBounceCheck){
		state = s == HIGH ? PRESSED : RELEASED;
		if(this->callback != 0)
			this->callback();
	}else if(state == BOUNCE_TO_RELEASE &&
			curMils - bounceCheckStart >= msBounceCheck){
		state = s == LOW ? RELEASED : PRESSED;
		if(this->callback != 0)
			this->callback();
	}
}
