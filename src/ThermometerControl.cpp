/*
 * ThermometerControl.cpp
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#include "arduino.h"
#include "../controllers/Thermometer.h"

Thermometer::Thermometer(byte analogPin) {
	this->pin = analogPin;
	this->callback = 0;
	this->lastVal = -1;
}

void Thermometer::update(){
	if(this->lastVal != getCurDegrees()){
		this->lastVal = getCurDegrees();
		this->callback();
	}
}

void Thermometer::setValueChangeCallback(void(*call)(void)){
	this->callback = call;
}

int Thermometer::getCurDegrees() {
	return map(analogRead(this->pin), this->deg0, this->deg22, 0, 22);
}

int Thermometer::getRawValue() {
	return analogRead(this->pin);
}


