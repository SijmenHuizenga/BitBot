/*
 * BitBot.cpp
 *
 *  Created on: 6 jan. 2015
 *      Author: Sijmen
 */

//static functions
#include "BitBot.h"

void BitBot::setup(){
	Serial.println("Reached beginning of setup.");
	magMeter = new LSM303DMag();
	drivingController = new DrivingController();
	Serial.println("Reached end of setup.");
}

void BitBot::loop(){
	magMeter->update();
	drivingController->update();
	if(!set){
		set = true;
		Movement* arr[2];
		arr[0] = new DegreeMovement(90);
		arr[1] = new DegreeMovement(-90);
		Route* route = new Route(false, 2, arr);
		drivingController->setRoute(route);
	}
}

BitBot* BitBot::getBot(){
	if(!inited){
		Serial.println("Craeting new instance");
		inited = true;
		bitbotInstance = new BitBot();
	}
	return bitbotInstance;
}

