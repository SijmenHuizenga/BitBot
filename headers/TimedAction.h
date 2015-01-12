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
		unsigned long lastMils;
		unsigned int delay();
		void ( *callback )( void );
	public:
		TimedAction();
		void setDelay(unsigned int);
		void setCallback(void ( * callback )( void ));
		void update();
};

#endif /* HEADERS_TIMEDACTION_H_ */
