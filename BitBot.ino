#include <Wire.h>
#include "Driving.h"
#include "LSM303D_MAG.h"
#include "LDR.h"
#include "LedMatrix.h"
#include "Button.h"

DrivingController* drivingController;
LightDependentResistor* ldr;
LSM303DMag* magMeter;
LedMatrix* matrix;
AntiBounceButton* rightWinkle;
AntiBounceButton* leftWinkle;


void setup() {
	Serial.begin(9600);
	Wire.begin();

	magMeter = new LSM303DMag();

	ldr = new LightDependentResistor(0);
	matrix = new LedMatrix(0x70);
	matrix->setBlink(1);
	matrix->setBrightness(5);

	rightWinkle = new AntiBounceButton(8);
	leftWinkle = new AntiBounceButton(9);
	rightWinkle->setCallback(winkleCallback);
	leftWinkle->setCallback(winkleCallback);


	drivingController = new DrivingController(magMeter->hoek);
	drivingController->setFinishCallback(movementFinish);
}

void loop() {
	magMeter->update();
	drivingController->update();

	rightWinkle->update();
	leftWinkle->update();

}

void movementFinish(){
	Serial.println("Movement Finished!");
}

//Twee winkels, 1 callback:
void winkleCallback(){
	bool isAganstWall = !rightWinkle->getState() || !leftWinkle->getState();
	matrix->drawSmiley(!isAganstWall);
}
