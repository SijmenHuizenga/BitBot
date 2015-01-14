/*
 * Driving.h
 *
 *  Created on: 24 dec. 2014 / 6 jan. 2015
 *      Author: Sijmen
 */

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#ifndef HEADERS_DRIVING_H_
#define HEADERS_DRIVING_H_

#include "Arduino.h"
#include "ServoMotor.h"

/**
 * De pin op de arduino waar de motoren op zijn aagesloten.
 */
const byte MOTOR_L_PIN = 13;
const byte MOTOR_R_PIN = 12;


class DrivingController {
	private:
		int &huidiggeDraaing;

		void (*callback)();

		int targetDegree; // -1 = using time
		int toGoTime;

		unsigned long startMillis;
	public:
		//zodat de logger de data kan uitlezen
		ServoMotor* motorL;
		ServoMotor* motorR;
	public:
		/**
		 * initializer. Als argument een verwijzing naar een int
		 * die de draaing van de arduino bij houd. Dit getal moet tussen
		 * 0 en 360 liggen.
		 */
		DrivingController(int&);

		/**
		 * Deze functie zou minstens elke miliseconden moeten worden
		 * aangeroepen. Vaker maakt niks uit. Deze functie houdt de
		 * thread niet vast.
		 */
		void update();

		/**
		 * De huidigge Route wordt afgebroken. De motoren worden gestopt.
		 */
		void stopRouteExecution();

		/**
		 * Draai de bitbot een aantal graden. Het aantal graden kan tussen de -360 en +360 liggen.
		 */
		void setTurn(int degree);

		/**
		 * Laat de bitbot een bepaalde tijd op een bepaalde snelheid vooruit of achteruit rijden.
		 */
		void setMovement(int leftSpeed, int rightSpeed, int time);

		/**
		 * Zet de callback functie die wordt aangeroepen als de movement klaar is.
		 */
		void setFinishCallback(void (*callback)());
};

#endif /* HEADERS_DRIVING_H_ */
