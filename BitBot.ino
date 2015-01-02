
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
	dev->min.x =  min(dev->readings.x, dev->min.x);
	dev->min.y =  min(dev->readings.y, dev->min.y);
	dev->min.z =  min(dev->readings.z, dev->min.z);

	dev->max.x =  max(dev->readings.x, dev->max.x);
	dev->max.y =  max(dev->readings.y, dev->max.y);
	dev->max.z =  max(dev->readings.z, dev->max.z);


}
