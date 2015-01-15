/*
 * LedMatrixControl.cpp
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#include "Arduino.h"

#include "../Lib/Wire/font_8x8.h"
#include "../Lib/Wire/Wire.h"
#include "../controllers/LedMatrix.h"

LedMatrix::LedMatrix(int adress) {
	this->adres = adress;

	Wire.beginTransmission(this->adres);
	Wire.write(0x21);
	Wire.endTransmission();
}

void LedMatrix::setBrightness(int brightness) {
	Wire.beginTransmission(this->adres);
	Wire.write(B11100000 + brightness);
	Wire.endTransmission();
}

void LedMatrix::setBlink(int amount) {
	Wire.beginTransmission(this->adres);
	Wire.write(B10000000 + amount);
	Wire.endTransmission();
}

void LedMatrix::drawSmiley(bool happy) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);

	Wire.write(rightCycleShift(B00111100));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B01111110));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B11011011));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B11111111));
	Wire.write(0x00);
	if(happy)
		Wire.write(rightCycleShift(B10111101));
	else
		Wire.write(rightCycleShift(B11000011));
	Wire.write(0x00);
	if(happy)
		Wire.write(rightCycleShift(B11000011));
	else
		Wire.write(rightCycleShift(B10111101));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B01111110));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B00111100));
	Wire.write(0x00);
	Wire.endTransmission();
}


void LedMatrix::drawEmptyness(){
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for(int i = 0; i < 16; i++){
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

void LedMatrix::drawLetter(char asciiCode) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for (int i = 0; i < 8; i++) {
		Wire.write(font8x8_basic[(int) asciiCode][i]);
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

void LedMatrix::drawMatrix(byte bits[]) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for (int i = 0; i < 8; i++) {
		Wire.write(rightCycleShift(bits[i]));
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

unsigned char LedMatrix::getCharBock(int ascii, int row){
	return font8x8_basic[ascii][row];
}

byte LedMatrix::rightCycleShift(byte in) {
	return (in >> 1 | in << 7);
}

byte LedMatrix::leftCycleShift(byte in) {
	return (in << 1 | in >> 7);
}
