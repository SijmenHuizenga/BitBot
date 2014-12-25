/*
 * DrivingController.cpp
 *
 *  Created on: 24 dec. 2014
 *      Author: Sijmen
 */

#include "DrivingController.h"

DrivingController::DrivingController(){
	motorL = new ServoMotor(MOTOR_L_PIN, false);
	motorL->setSpeed(0);
	motorR = new ServoMotor(MOTOR_R_PIN, true);

	movementNr = 0;
	movementStartMillis = millis();
	route = NULL;
}

void DrivingController::update(){
	if(route == NULL){
		return;
	}
	unsigned long curMills = millis();
	if(curMills - movementStartMillis >= route->movements[movementNr]->time){
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
			motorL->setSpeed(route->movements[movementNr]->leftSpeed);
			motorR->setSpeed(route->movements[movementNr]->rightSpeed);
		}
	}
}
void DrivingController::setRoute(Route* route_){
	route = route_;
	movementNr = 0;
	movementStartMillis = millis();

	motorL->setSpeed(route->movements[movementNr]->leftSpeed);
	motorR->setSpeed(route->movements[movementNr]->rightSpeed);
}
void DrivingController::stopRouteExecution(){
	route = NULL;
	movementNr = 0;
	movementStartMillis = 0;
	motorL->setSpeed(0);
	motorR->setSpeed(0);
}


