/*
 * TimedActionImpl.cpp
 *
 *  Created on: 12 jan. 2015
 *      Author: Sijmen
 */

#include "TimedAction.h"
#include "Arduino.h"

TimedAction::TimedAction(){
	this->callback = 0;
	this->lastMils = 0;
	this->delay = 500;
}

void TimedAction::setCallback(void ( *callback )( void )){
	this->callback = callback;
}

void TimedAction::setDelay(unsigned int newDelay){
	this->delay = newDelay;
}

void TimedAction::update(){
	unsigned long curMils = millis();
	if(curMils - lastMils > delay){
		if(this->callback != 0)
			this->callback();
		lastMils = curMils;
	}
}
