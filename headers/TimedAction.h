/*
 * TimedAction.h
 *
 *  Created on: 12 jan. 2015
 *      Author: Sijmen
 */

#ifndef HEADERS_TIMEDACTION_H_
#define HEADERS_TIMEDACTION_H_

class TimedAction{
	private:
		/**
		 * de laatste update moment
		 */
		unsigned long lastMils;

		/**
		 * de lengte van de delay tussen de callbacks
		 */
		unsigned int delay;

		/*
		 * de aan te roepen functie
		 */
		void ( *callback )( void );
	public:
		/**
		 * de constructor. Niks bijzonders
		 */
		TimedAction();

		/**
		 * zet de lengte van de delay tussen de actions
		 */
		void setDelay(unsigned int);

		/**
		 * zet de functie die moet worden aangeroepen als de delay op is
		 */
		void setCallback(void ( * callback )( void ));

		/**
		 * update de timed action
		 */
		void update();
};

#endif /* HEADERS_TIMEDACTION_H_ */
