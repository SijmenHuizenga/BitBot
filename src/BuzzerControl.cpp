/*
 * BuzzerControl.cpp
 *
 *  Created on: 8 jan. 2015
 *      Author: Sijmen
 */

#include "Buzzer.h"

Buzzer::Buzzer(byte pin){
	this->pin = pin;
	this->offTime = 0;
	this->onTime = 0;
	this->toneHz = 0;
	this->lastUpdate = 0;
	this->onOrOff = false;
}

void Buzzer::setOffTime(unsigned int offTime){
	this->offTime = offTime;
}

void Buzzer::setOnTime(unsigned int onTime){
	this->onTime = onTime;
}

void Buzzer::setTone(unsigned int tone){
	this->toneHz = tone;
}

void Buzzer::update(){
	unsigned long curMils = millis();
	if(this->onTime != 0 && onOrOff && curMils - this->lastUpdate >= this->onTime){
		//ik ben aan geweest en ben klaar met aan zijn. Nu uit:
		noTone(this->pin);
		this->lastUpdate = curMils;
		onOrOff = false;
	}else if(this->offTime != 0 && !onOrOff && curMils - this->lastUpdate >= this->offTime){
		//ik was uit en ben klaar met uit zijn. Nu aan:
		tone(this->pin, this->toneHz);
		this->lastUpdate = curMils;
		onOrOff = true;
	}
}

