#include <Wire.h>
#include "Driving.h"
#include "LSM303D_MAG.h"

DrivingController* drivingController;
LSM303DMag* magMeter;

void setup() {
	Serial.begin(9600);
	Wire.begin();

	magMeter = new LSM303DMag();
	drivingController = new DrivingController(magMeter->hoek);
	drivingController->setFinishCallback(movementFinish);
	drivingController->setTurn(-180);
}

void loop() {
	magMeter->update();
	drivingController->update();
}

void movementFinish(){
	Serial.println("Movement Finished!");
}
