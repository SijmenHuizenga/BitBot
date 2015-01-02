
#include <LSM303D.h>
#include "headers/DrivingController.h"
#include <Wire.h>

DrivingController* c;

LSM303D* dev;

void setup() {
	Serial.begin(9600);
	Wire.begin();
	dev = new LSM303D();

//	c = new DrivingController();
//
//	Movement* arr = new Movement[2]();
//	arr[0] = Movement::getTurnLeftMovement();
//	arr[1] = Movement::getTurnRightMovement();
//
//	Route* route = new Route(true, 2, arr);
//
//	c->setRoute(route);
}

void loop() {
//	c->update();
	dev->update();

	delay(100);
}
