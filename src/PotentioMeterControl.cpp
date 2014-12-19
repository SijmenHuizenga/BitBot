/*
 * PotentioMeterControl.cpp
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#include "arduino.h"
#include "../controllers/PotentioMeter.h"

PotentioMeter::PotentioMeter(byte analogPin) {
	this->pin = analogPin;
	this->callback = 0;
	this->lastVal = -1;
}

/**
 * value is tussen 0 en 99
 */
int PotentioMeter::getValuePersentage() {
	return map(analogRead(pin), 0, 1023, 0, 99);
}

int PotentioMeter::getRawValue() {
	return analogRead(pin);
}
void PotentioMeter::setValueChangeCallback(void(*call)(void)){
	this->callback = call;
}
void PotentioMeter::update(){
	if(this->lastVal != this->getValuePersentage()){
		this->lastVal = this->getValuePersentage();
		this->callback();
	}
}


