#include <Wire.h>
#include "Driving.h"
#include "LSM303D_MAG.h"
#include "LDR.h"
#include "LedMatrix.h"
#include "Button.h"
#include "Buzzer.h"
#include "BitBotSates.h"

DrivingController* drivingController;
LightDependentResistor* ldr;
LSM303DMag* magMeter;
LedMatrix* matrix;
AntiBounceButton* rightWinkle;
AntiBounceButton* leftWinkle;
Buzzer* buzz;

//wat is de huidigge bitbot status?
BitBotState status;

//welke status was er voor de botsing?
BitBotState voorBotsingStatus;
//hoeveel moet bij NABOTSING_DRAAIEN_TERUG gedraad worden?
int returnDegree;



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

	buzz = new Buzzer(11);
	buzz->setOnTime(1000);
	buzz->setOffTime(500);
	buzz->setTone(494);

	status = LICHTZOEKEN_X;
}

void loop() {
	magMeter->update();
	drivingController->update();

	rightWinkle->update();
	leftWinkle->update();

	buzz->update();
}

//callback:
void movementFinish(){
	switch (status) {
		case NABOTSING_ACHTERUIT:
			status = NABOTSING_DRAAIEN_A;
			drivingController->setTurn(90);
			returnDegree -= 90;
			break;
		case NABOTSING_DRAAIEN_A:
			status = NABOTSING_VOORUIT;
			drivingController->setMovement(50, 50, 2000);
			break;
		case NABOTSING_VOORUIT:
			status = NABOTSING_DRAAIEN_B;
			drivingController->setTurn(returnDegree);
			returnDegree = 0;
			break;
		case NABOTSING_DRAAIEN_B:
			status = voorBotsingStatus;
			voorBotsingStatus = 0;
			break;
		default:
			break;
	}
}

//callback twee voelsprieten
void winkleCallback(){
	bool isAganstWall = !rightWinkle->getState() || !leftWinkle->getState();
	if(isAganstWall){
		if(status == NABOTSING_VOORUIT){
			drivingController->setMovement(-50, -50, 2000);
			status = NABOTSING_ACHTERUIT;
		}
	}
}

void startNaBotsing(){


}



