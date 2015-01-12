#include <Wire.h>
#include "Driving.h"
#include "LSM303D_MAG.h"
#include "LDR.h"
#include "LedMatrix.h"
#include "Button.h"
#include "Buzzer.h"
#include "BitBotSates.h"
#include "Thermometer.h"
#include "Led.h"

DrivingController* drivingController;
LightDependentResistor* ldr;
Thermometer* therm;
LedController* leds;
LSM303DMag* magMeter;
LedMatrix* matrix;
AntiBounceButton* spriet;
Buzzer* buzz;

//wat is de huidigge bitbot status?
BitBotState status;

//welke status was er voor de botsing?
BitBotState voorBotsingStatus;
//hoeveel moet bij NABOTSING_DRAAIEN_TERUG gedraad worden?
int returnDegree;

int lastLightValue;

void setup() {
	Serial.begin(9600);
	Wire.begin();

	magMeter = new LSM303DMag();
	magMeter->setValueChangeCallback(compassCallback);

	ldr = new LightDependentResistor(2);
	ldr->setValueChangeCallback(ldrCallback);

	matrix = new LedMatrix(0x70);
	matrix->setBlink(1);
	matrix->setBrightness(5);
	matrix->drawSmiley(false);

	spriet = new AntiBounceButton(10);
	spriet->setCallback(sprietCallback);

	therm = new Thermometer(1);
	therm->setValueChangeCallback(thermCallback);

	drivingController = new DrivingController(magMeter->hoek);
	drivingController->setFinishCallback(movementFinish);

	leds = new LedController();
	leds->initilize();

	buzz = new Buzzer(11);
	buzz->setTone(494);
	buzz->setOnTime(50);

	status = LICHTZOEKEN_STARTING;
	lastLightValue = ldr->getLuxValue();
	Serial.println("initial lux value: "  + String(lastLightValue));
	drivingController->setMovement(80, 80, 1000);
}

void loop() {
	//eerst input
	therm->update();
	spriet->update();
	magMeter->update();

	//dan output
	drivingController->update();
	buzz->update();
}

//callback:
void movementFinish(){
	int curLightVal = ldr->getLuxValue();
	switch (status) {
		case NABOTSING_ACHTERUIT:
			status = NABOTSING_DRAAIEN_A;
			drivingController->setTurn(90);
			returnDegree -= 90;
			break;
		case NABOTSING_DRAAIEN_A:
			status = NABOTSING_VOORUIT;
			drivingController->setMovement(50, 50, 1000);
			break;
		case NABOTSING_VOORUIT:
			status = NABOTSING_DRAAIEN_B;
			drivingController->setTurn(returnDegree);
			returnDegree = 0;
			break;
		case NABOTSING_DRAAIEN_B:
			status = voorBotsingStatus;
			if(status == LICHTZOEKEN_STARTING){
				lastLightValue = -1;
				movementFinish();
			}
			break;
		case LICHTZOEKEN_STARTING:
			if(lastLightValue == -1){//overniuw beginnen
				Serial.println("We just turned, now we are the right way");
				lastLightValue = ldr->getLuxValue();
				drivingController->setMovement(80, 80, 1000);
			}
			if(curLightVal > lastLightValue){
				Serial.println("first light value: " + String(curLightVal) + " so we are the right way");
				status = LICHTZOEKEN_GRADIENT;
				matrix->drawSmiley(true);
				//start lichtzoeken
			}else if(curLightVal < lastLightValue){
				Serial.println("first light value: " + String(curLightVal) + " so we are turning");
				drivingController->setTurn(-220);
				lastLightValue = -1;//begin overniuw
			}else{
				Serial.println("Could not find any light. I am sorry.");
				status = DANCE;
			}
			break;
		default:
			break;
	}
}

//callback twee voelsprieten
void sprietCallback(){
	bool isAganstWall = !spriet->getState();
	if(isAganstWall){
		if(status == NABOTSING_ACHTERUIT || status == NABOTSING_VOORUIT || status == LICHTZOEKEN_STARTING || status == LICHTZOEKEN_GRADIENT){
			drivingController->setMovement(-50, -50, 1000);
			voorBotsingStatus = status;
			status = NABOTSING_ACHTERUIT;
		}
	}
}

void thermCallback(){
	//zie formule: https://github.com/SijmenHuizenga/BitBot/issues/8
	Serial.println(therm->getCurDegrees());
	buzz->setOffTime((30-therm->getCurDegrees())*100);
}

void ldrCallback(){

}

void compassCallback(){
	for(int i = 0; i < 8; i++)
		leds->setLedOn(i, false);
	switch (magMeter->heading()) {
		case N:   leds->setLedOn(0, true);  break;
		case NE:  leds->setLedOn(1, true);  break;
		case E:   leds->setLedOn(2, true);  break;
		case ES:  leds->setLedOn(3, true);  break;
		case S:   leds->setLedOn(4, true);  break;
		case SW:  leds->setLedOn(5, true);  break;
		case W:   leds->setLedOn(6, true);  break;
		case WN:  leds->setLedOn(7, true);  break;
		default:
			break;
	}
}



