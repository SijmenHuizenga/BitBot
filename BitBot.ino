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
#include "TimedAction.h"
#include "DataLogger.h"

DrivingController* drivingController;
LightDependentResistor* ldr;
Thermometer* therm;
LedController* leds;
LSM303DMag* magMeter;
LedMatrix* matrix;
AntiBounceButton* spriet;
Buzzer* buzz;

//een timer van vijf seconden
TimedAction* fiveSecondTimer;

//de data logging systeem van de bitbot
DataLogger* logger;

//wat is de huidigge bitbot status?
BitBotState status;

//hoeveel moet bij NABOTSING_DRAAIEN_TERUG gedraad worden?
int returnDegree;

//gebruikt tijdens het zoeken naar licht
int lastLightValue;
//op welke as ben ik aan het zoeken?
Axis as;

//gebruikt voor check of licht/temp ineens zijn verandert.
int lastDegree = 0;
int lastLight = 0;

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
	matrix->drawEmptyness();

	spriet = new AntiBounceButton(10);
	spriet->setCallback(sprietCallback);

	therm = new Thermometer(1);
	therm->setValueChangeCallback(thermCallback);

	drivingController = new DrivingController(magMeter->hoek);
	drivingController->setFinishCallback(movementFinish);

	leds = new LedController();

	buzz = new Buzzer(11);
	buzz->setTone(494);
	buzz->setOnTime(50);

	fiveSecondTimer = new TimedAction();
	fiveSecondTimer->setCallback(fiveSecondCallback);
	fiveSecondTimer->setDelay(5000);

	logger = new DataLogger();

	delay(3000);

	status = LICHTZOEKEN_STARTING;
	as = X_AXES;
	lastLightValue = ldr->getLuxValue();
	Serial.println("initial lux value: "  + String(lastLightValue));
	drivingController->setMovement(80, 80, 2000);
}

/**
 * (meolodie "hoor wie klopt daar kinderen")
 * hoor wie crasht daar kinderen, hoor wie crasht daar kinderen, hoor wie
 * stop daar zatchjes uit het niets? Arduinoooo, Arduinoooooo
 */
void loop() {
	//eerst input
	therm->update();
	spriet->update();
	magMeter->update();
	ldr->update();

	//dan output
	drivingController->update();
	buzz->update();
	fiveSecondTimer->update();
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
			drivingController->setMovement(50, 50, 2000);
			break;
		case NABOTSING_VOORUIT:
			status = NABOTSING_DRAAIEN_B;
			drivingController->setTurn(returnDegree);
			returnDegree = 0;
			break;
		case NABOTSING_DRAAIEN_B:
			//botsing kan alleen geregeistreerd worden tijdens status LICHTZOEKEN_GRADIENT
			status = LICHTZOEKEN_GRADIENT;
			lastLightValue = 0;
			movementFinish();
			break;
		case LICHTZOEKEN_STARTING:
			if(lastLightValue == -1){//overniuw beginnen
				Serial.println("We just turned, now we are the right way");
				lastLightValue = ldr->getLuxValue();
				drivingController->setMovement(80, 80, 2000);
			}else if(curLightVal > lastLightValue){
				Serial.println("first light value: " + String(curLightVal) + " so we are the right way");
				status = LICHTZOEKEN_GRADIENT;
				lastLightValue = 0;
				movementFinish();
				//start lichtzoeken
			}else if(curLightVal < lastLightValue){
				Serial.println("first light value: " + String(curLightVal) + " so we are turning");
				drivingController->setTurn(180);
				lastLightValue = -1;//begin overniuw
			}else{
				Serial.println("Could not find any light. I am sorry.");
				drivingController->stopRouteExecution();
				//status = DANCE;
			}
			break;
		case DANCE:
			matrix->drawSmiley(random(0,1));
			drivingController->setTurn(random(-180, 180));
			break;
		case LICHTZOEKEN_TURNING:
			status = LICHTZOEKEN_STARTING;
			lastLightValue = ldr->getLuxValue();
			Serial.println("initial new lux value: "  + String(lastLightValue));
			drivingController->setMovement(80, 80, 2000);
			break;
		case LICHTZOEKEN_GRADIENT:
			drivingController->setMovement(60, 60, 32767);
			break;
		default:
			break;
	}
}

//callback twee voelsprieten
void sprietCallback(){
	bool isAganstWall = !spriet->getState();
	if(isAganstWall && status == LICHTZOEKEN_GRADIENT){
		drivingController->setMovement(-50, -50, 2000);
		status = NABOTSING_ACHTERUIT;
	}
}

//callback bij verandering van temepratuur
void thermCallback(){
	//zie formule: https://github.com/SijmenHuizenga/BitBot/issues/8
	buzz->setOffTime((30-therm->getCurDegrees())*100);
}

//callback bij verandering vna licht
void ldrCallback(){
	if(status == LICHTZOEKEN_GRADIENT){
		if(ldr->getLuxValue() <= lastLightValue){
			if(as == X_AXES){
				as = Y_AXES;
				status = LICHTZOEKEN_TURNING;
				drivingController->setTurn(90);
			}else if(as == Y_AXES){
				as = DONE_AXES;
				drivingController->stopRouteExecution();
				status = LICHTZOEKEN_DONE;
			}

		}else{
			lastLightValue = ldr->getLuxValue();
		}
	}
}

//Contoroleren of de temeratuur of licht ineens is gedaald én loggen!
void fiveSecondCallback(){
	if(lastDegree != 0 && ((lastDegree - therm->getCurDegrees()) > 5 || (lastLight - ldr->getLuxValue()) > 5)){
		Serial.println("Drop in temeratuur of licht: sad panda");
		matrix->drawSmiley(false);
	}else if(therm->getCurDegrees()>23){
		Serial.println("temperatuur boven 23 graden: happy!");
		matrix->drawSmiley(true);
	}else{
		matrix->drawEmptyness();
	}
	lastDegree = therm->getCurDegrees();
	lastLight = ldr->getLuxValue();

	logger->logData(ldr->getLuxValue(), therm->getCurDegrees(), magMeter->getHoek(),
			drivingController->motorL->getCurSpeed(), drivingController->motorR->getCurSpeed());
}

//callback voor het veranderen van draaing
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
