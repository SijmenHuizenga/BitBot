/*
 * BitBot.h
 *
 *  Created on: 6 jan. 2015
 *      Author: Sijmen
 */

#ifndef HEADERS_BITBOT_H_
#define HEADERS_BITBOT_H_

#include "DrivingController.h"
#include "LSM303D_MAG.h"

class BitBot {
	private:
		DrivingController* drivingController;
		LSM303DMag* magMeter;
		bool set = false;
	public:
		void setup();
		void loop();
		static BitBot* getBot();
		LSM303DMag* getMagMeter(){
			return magMeter;
		}

	public:
		static int rotate360(int x, int toRotate){
			x += toRotate;
			if(x > 360)
				x-= 360;
			if(x < 0)
				x = 360 + x;
			return x;
		}
};
//http://en.wikipedia.org/wiki/Singleton_pattern
static BitBot* bitbotInstance = NULL;
static bool inited = false;


#endif /* HEADERS_BITBOT_H_ */
