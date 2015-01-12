/*
 * TimedActionImpl.cpp
 *
 *  Created on: 12 jan. 2015
 *      Author: Sijmen
 */

TimedAction::TimedAction(){
	this->callback = 0;
	this->lastMils = 0;
}

void TimedAction::setCallback(void ( *callback )( void )){
	this->callback = callback;
}

void TimedAction::setDelay(unsigned int newDelay){
	this->delay = newDelay;
}

void TimedAction::update(){
	unsigned long curMils = millis();
	if(lastMils + delay >= curMils){
		if(this->callback != 0)
			this->callback();
		lastMils = curMils;
	}
}
