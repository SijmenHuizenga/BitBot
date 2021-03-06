/*
 * DataLogger.h
 *
 *  Created on: 13 jan. 2015
 *      Author: Sijmen
 */

#ifndef HEADERS_DATALOGGER_H_
#define HEADERS_DATALOGGER_H_

#include "Arduino.h"

class DataLogger{
	private:
		//0: lux value between 0 and 100
		//1: temp between -100 to +100. The saved value is between 0 and 200
		//2: rotation of arduino between 0 and 360. This value is mapped between 0 and 255
		//3: leftSpeed between -100 and 100. This value is scaled to 0 and 200
		//4: rightspeed between -100 and 100. This value is scaled to 0 and 200
		byte** data;

		/**
		 * de hoeveelheid rows of data die kunnen worden bijgehouden
		 */
		static const int amount = 10;
	public:
		/**
		 * conostructor. Initializeert de data arrays
		 */
		DataLogger();
		/**
		 * dump alle tot nu toe verzamelde data in de serial
		 */
		void serialDump();

		/**
		 * dump een row in de serial
		 */
		void serialDumpRow(int);

		/**
		 * leeg alle data
		 */
		void clearData();

		/**
		 * log een nieuwe row met data
		 */
		void logData(int luxVal, int tempVal, int magValue, int leftSpeed, int rightSpeed);
};



#endif /* HEADERS_DATALOGGER_H_ */
