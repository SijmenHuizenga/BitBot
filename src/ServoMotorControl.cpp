/*
 * ServoMotorControl.cpp
 *
 *  Created on: 20 dec. 2014
 *      Author: Sijmen
 */

#include <ServoMotor.h>

ServoMotor::ServoMotor(int pin, bool inv){
	this->servo = new Servo();
	this->servo->attach(pin);
	this->inverted = inv;
	this->curSpeed = 0;
};

void ServoMotor::setSpeed(int speed){
  servo->writeMicroseconds(off + (inverted ? -1 : 1) * (speed*(marge/100)));
}

void ServoMotor::setRawSpeed(int raw){
  servo->writeMicroseconds(raw);
}
