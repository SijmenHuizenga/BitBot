/*
 * DrivingController.cpp
 *
 *  Created on: 24 dec. 2014
 *      Author: Sijmen
 */

#include "BitBot.h"
#include "DrivingController.h"
#include "LSM303D_MAG.h"

DrivingController::DrivingController(){
	motorL = new ServoMotor(MOTOR_L_PIN, false);
	motorL->setSpeed(0);
	motorR = new ServoMotor(MOTOR_R_PIN, true);

	movementNr = 0;
	route = NULL;
}

void DrivingController::update(){
	if(route == NULL){
		return;
	}
	if(route->movements[movementNr]->isDone()){
		Serial.println("Next Movement Starting Now...");
		movementNr++;
		if(movementNr >= route->movementsAmount){
			if(route->repeat){
				//end of route, should repeat
				movementNr = 0;
			}else{
				//end of route, no repeat
				stopRouteExecution();
				return;
			}
		}
		motorL->setSpeed(route->movements[movementNr]->getLeftSpeed());
		motorR->setSpeed(route->movements[movementNr]->getRightSpeed());
		route->movements[movementNr]->start();
	}

}

void DrivingController::setRoute(Route* route_){
	route = route_;
	movementNr = 0;

	motorL->setSpeed(route->movements[movementNr]->getLeftSpeed());
	motorR->setSpeed(route->movements[movementNr]->getRightSpeed());
	route->movements[movementNr]->start();
}

void DrivingController::stopRouteExecution(){
	route = NULL;
	movementNr = 0;
	motorL->setSpeed(0);
	motorR->setSpeed(0);
}

TimedMovement::TimedMovement(unsigned int time_, int leftSpeed_, int rightSpeed_){
	this->time = time_;
	this->leftSpeed = leftSpeed_;
	this->rightSpeed = rightSpeed_;
	this->movementStartMillis = 0;
}

void TimedMovement::start(){
	this->movementStartMillis = millis();
}

bool TimedMovement::isDone(){
	return this->movementStartMillis + this->time >= millis();
}

DegreeMovement::DegreeMovement(int turnDegree){
	this->turnAmount = turnDegree;
	this->targetD = 0;

	if(turnDegree < 0){
		this->leftOrRight = true;
	}else if(turnDegree > 0){
		this->leftOrRight = false;
	}else{
		//it would be verry stupid if you did this.
		Serial.println("You are stupid. #01");
		return;
	}
}
int DegreeMovement::getLeftSpeed(){
	return this->leftOrRight ? 0 : 60;
}
int DegreeMovement::getRightSpeed(){
	return this->leftOrRight ? 60 : 0;
}

void DegreeMovement::start(){
	if(this->leftOrRight){//left
		targetD = BitBot::rotate360(BitBot::getBot()->getMagMeter()->getHoek(), 360+turnAmount);
	}else{//right
		targetD = BitBot::rotate360(BitBot::getBot()->getMagMeter()->getHoek(), turnAmount);
	}
}

bool DegreeMovement::isDone(){
	int rightBorder = BitBot::rotate360(targetD, 10);
	int leftBorder = BitBot::rotate360(targetD, -10);
	int hoek = BitBot::getBot()->getMagMeter()->getHoek();
	Serial.println(String(rightBorder) + " : " + String(hoek) + " : " + String(leftBorder));
	return hoek < rightBorder && hoek > leftBorder;
	return false;
}
