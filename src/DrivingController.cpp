/*
 * DrivingController.cpp
 *
 *  Created on: 24 dec. 2014
 *      Author: Sijmen
 */

#include "Driving.h"
#include "LSM303D_MAG.h"
#include "Util.h"

DrivingController::DrivingController(int &hoekRef) : huidiggeDraaing(hoekRef){
	this->motorL = new ServoMotor(MOTOR_L_PIN, false);
	this->motorR = new ServoMotor(MOTOR_R_PIN, true);

	this->callback = 0;

	//reset all variables:
	stopRouteExecution();
}

void DrivingController::update(){
	if(targetDegree != -1){//we using turned movement
		int rightBorder = add360(targetDegree, 5);
		int leftBorder = add360(targetDegree, -5);
		if( between360(this->huidiggeDraaing, leftBorder, rightBorder)){
			stopRouteExecution();
			if(this->callback != 0)
				this->callback();
		}
	}
	if(this->toGoTime != -1){//we using time movements
		unsigned long curMils = millis();
		if(curMils >= this->startMillis + this->toGoTime){
			stopRouteExecution();
			if(this->callback != 0)
				this->callback();
		}
	}

}

void DrivingController::stopRouteExecution(){
	this->toGoTime = -1;
	this->startMillis = 0;
	this->targetDegree = -1;
	this->motorL->setSpeed(0);
	this->motorR->setSpeed(0);
}

void DrivingController::setMovement(int leftSpeed, int rightSpeed, int time){
	this->motorL->setSpeed(leftSpeed);
	this->motorR->setSpeed(rightSpeed);
	unsigned long curMils = millis();
	this->startMillis = curMils;
	this->toGoTime = time;
	targetDegree = -1;
}

void DrivingController::setTurn(int degree){
	this->targetDegree = degree;

	if(degree < 0){ //go left
		this->motorL->setSpeed(0);
		this->motorR->setSpeed(60);
		this->targetDegree = add360(this->huidiggeDraaing, -1*degree);
	}else if(degree > 0){ //go right
		this->motorL->setSpeed(60);
		this->motorR->setSpeed(0);
		this->targetDegree = add360(this->huidiggeDraaing, -1*degree);
	}else{
		//it would be verry stupid if you did this.
		Serial.println("You are stupid. #01");
		return;
	}
}

void DrivingController::setFinishCallback(void (*callback)()){
	this->callback = callback;
}
