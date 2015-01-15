/*
 * LDRControl.cpp
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#include "Arduino.h"
#include "../controllers/LDR.h"

LightDependentResistor::LightDependentResistor(byte analogPin) {
	this->pin = analogPin;
	this->callback = 0;
	this->lastVal = -1;
}
void LightDependentResistor::setValueChangeCallback(void(*call)(void)){
	this->callback = call;
}

int LightDependentResistor::getLuxValue() {
	return map(constrain(analogRead(this->pin),this->min, this->max), this->min, this->max, 100, 0);
}

int LightDependentResistor::getRawValue() {
	return analogRead(this->pin);
}

void LightDependentResistor::update(){
	int curLuxVal = getLuxValue();
	if(abs(this->lastVal - curLuxVal) > 5){
		this->lastVal = curLuxVal;
		this->callback();
	}
}
