/*
 * BitBot.cpp
 *
 *  Created on: 6 jan. 2015
 *      Author: Sijmen
 */

#include "BitBot.h"

void BitBot::setup(){
	delay(1);
	magMeter = new LSM303DMag();
	delay(1);
	drivingController = new DrivingController();
	delay(1);
}

void BitBot::loop(){
	magMeter->update();
	drivingController->update();
	if(!set){
		set = true;
		Movement** arr;
		arr[0] = new DegreeMovement(90);
		arr[1] = new DegreeMovement(-90);
		Route* route = new Route(false, 2, arr);
		drivingController->setRoute(route);
	}
}

BitBot* BitBot::getBot(){
	if(!inited){
		Serial.println("new");
		delay(1);
		inited = true;
		bitbotInstance = new BitBot();
	}
	return bitbotInstance;
}

