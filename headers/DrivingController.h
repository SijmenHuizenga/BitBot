/*
 * DrivingController.h
 *
 *  Created on: 24 dec. 2014
 *      Author: Sijmen
 */

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#ifndef HEADERS_DRIVINGCONTROLLER_H_
#define HEADERS_DRIVINGCONTROLLER_H_

#include "BitBot.h"
#include "Arduino.h"
#include "ServoMotor.h"

/**
 * De pin op de arduino waar de motoren op zijn aagesloten.
 */
const byte MOTOR_L_PIN = 13;
const byte MOTOR_R_PIN = 12;

/**
 *  Wat zijn deze klasse?
 * Een drivingController stuurt 2 motoren aan.
 * Je geeft aan de drivingController een Route (route).
 * De drivingController gaat deze route uitvoren. Een route
 * bestaat uit een lijst met movements. Elke movement heeft
 * een tijd: hoe lang de movment moet worden uitgevoerd. Ook
 * heeft elke movement twee snelheden: voor het linker én rechter
 * wiel.
 *
 * Zo kan een route bijvoorbeeld zijn:
 * Route[
 * Movement[time=5000, leftSpeed=100, rightSpeed=100],
 * Movement[time=1000, leftSpeed=30, rightSpeed=100],
 * Movement[time=5000, leftSpeed=50, rightSpeed=50]
 * ]
 * Deze route doet het volgende: Ga vijf seconden volle snelheid vooruit,
 * Daarna draai 1 seconde naar links, en ga daarna vijf seconden op halve snelheid
 * vooruit.
 *
 * De drivingController voert de rote uit. Als de route afgelopen is, wordt deze
 * opnieuw gestart, of hij wordt gestopt. Dit wordt aangegeven door een boolean.
 * Ook kan tegen de drivingController gezegt worden dat de huidigge route gestopt
 * moet worden, of dat er een nieuwe route gestart moet worden.
 *
 * De Movement en Route klassen zijn hebben geen functionaliteit. Ze zijn alleen
 * bedoeld om een aantal variabelen te grouperen. Deze klasse hebben dus alleen
 * een constructor.
 */

//http://stackoverflow.com/questions/127426/gnu-compiler-warning-class-has-virtual-functions-but-non-virtual-destructor
class Movement {
	public:
		int leftSpeed;
		int rightSpeed;

		virtual ~Movement(){};

		virtual void start(){};
		virtual bool isDone(){return false;};
};

class TimedMovement: public Movement {
	public:
		int leftSpeed;
		int rightSpeed;
		unsigned long movementStartMillis;
		unsigned int time;


		TimedMovement(unsigned int, int, int);
		~TimedMovement(){};
		void start();
		bool isDone();
};

class DegreeMovement: public Movement {
	public:
		unsigned int turnAmount;
		unsigned int targetD;
		bool leftOrRight; //true = left, false = right;

		DegreeMovement(int turnDegree);
		~DegreeMovement(){};
		void start();
		bool isDone();
};

class Route {
	public:
		bool repeat;
		byte movementsAmount;
		Movement** movements;

		Route(bool repeat_, byte movementsAmount_, Movement** movements_) {
			repeat = repeat_;
			movementsAmount = movementsAmount_;
			movements = movements_;
		}
};

class DrivingController {
	private:
		ServoMotor* motorL;
		ServoMotor* motorR;
		Route* route;

		//route execution:
		byte movementNr;
	public:
		/**
		 * initializer. Geen argumenten.
		 */
		DrivingController();

		/**
		 * Deze functie zou minstens elke miliseconden moeten worden
		 * aangeroepen. Vaker maakt niks uit. Deze functie houdt de
		 * thread niet vast.
		 */
		void update();

		/**
		 * Zet een nieuwe Route. De huidigge Route wordt afgebroeken en
		 * deze Route wordt rechtstreeks uitgevoerd.
		 */
		void setRoute(Route*);

		/**
		 * De huidigge Route wordt afgebroken. De motoren worden gestopt.
		 */
		void stopRouteExecution();
};

#endif /* HEADERS_DRIVINGCONTROLLER_H_ */
