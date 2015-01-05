
#include <LSM303D_MAG.h>
#include "headers/DrivingController.h"
#include <Wire.h>

DrivingController* c;
LSM303DMag* mag;

void setup() {
	Serial.begin(9600);
	Wire.begin();


	c = new DrivingController();

	mag = new LSM303DMag();
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
	c->update();
	mag->update();

}
