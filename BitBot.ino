#include "controllers/ServoMotor.h"
#include "controllers/Button.h"
#include "controllers/LDR.h"
#include "controllers/Led.h"
#include "controllers/LedMatrix.h"
#include "controllers/PotentioMeter.h"
#include "controllers/Thermometer.h"

ServoMotor* motorL;

void setup() {
	motorL = new ServoMotor(13, false);
	motorL->setSpeed(10);
}

void loop() {

}

