/*
 * DataLoggerImpl.cpp
 *
 *  Created on: 13 jan. 2015
 *      Author: Sijmen
 */

#include "DataLogger.h"
#include "Arduino.h"

DataLogger::DataLogger(){
	data = new byte*[amount];
	for(int i = 0; i < amount; ++i)
	    data[i] = new byte[5];
	clearData();
}

void DataLogger::serialDump(){
	Serial.println("time | lux | celsius | degree | left velocity | right velocity");
	for(byte i = 0; i < amount; i++){
		if(data[i][0] == 0xFF){
			return;
		}
		serialDumpRow(i);
	}
}

void DataLogger::serialDumpRow(int i){
	Serial.print(String(i) + " | ");
	Serial.print(String(data[i][0]) + " | ");
	Serial.print(String(((int)data[i][1])-100) + " | ");
	Serial.print(String(map(data[i][2], 0, 255, 0, 360)) + " | ");
	Serial.print(String(((int)data[i][3])-100) + " | ");
	Serial.println(String(((int)data[i][4])-100) + " | ");
}

void DataLogger::clearData(){
	for(byte i = 0; i < amount; i++){
		for(byte j = 0; j < 5; j++){
			data[i][j] = 0xFF;
		}
	}
}

void DataLogger::logData(int luxVal, int tempVal, int magValue, int leftSpeed, int rightSpeed){
	int i;
	for(i = 0; i < amount; i++){
		if(data[i][0] == 0xFF){
			goto logData;
		}
	}
	Serial.println("Datalogger is full of data.");
	return;

	logData:
	data[i][0] = luxVal;
	data[i][1] = tempVal+100;
	data[i][2] = map(magValue, 0, 360, 0, 255);
	data[i][3] = leftSpeed+100;
	data[i][4] = rightSpeed+100;
	serialDumpRow(i);
}
