
#include "headers/DrivingController.h"

DrivingController* c;

void setup() {
	Serial.begin(9600);
	c = new DrivingController();

	Movement* arr = new Movement[2]();
	arr[0] = Movement::getTurnLeftMovement();
	arr[1] = Movement::getTurnRightMovement();

	Route* route = new Route(false, 2, arr);

	c->setRoute(route);
}

void loop() {
	c->update();
}
