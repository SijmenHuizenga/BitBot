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

/**
 * brightness between 0 and 15 where 0 is
 * 1/16 brightness
 * and 15 is 16/16 brightness
 */
void LedMatrix::setBrightness(int brightness) {
	Wire.beginTransmission(this->adres);
	Wire.write(B11100000 + brightness);
	Wire.endTransmission();
}

/**
 * amount between 1 and 7 where:
 * 1 = blink off
 * 3 = 2 hz
 * 5 = 0.5 hz
 */
void LedMatrix::setBlink(int amount) {
	Wire.beginTransmission(this->adres);
	Wire.write(B10000000 + amount);
	Wire.endTransmission();
}

/**
 * Every one loves a smiley. So this function shows this smyle
 * to the display. Wether the smily is happy or not can be
 * said by the bool argument.
 */
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

/**
 * draw void onto the led matrix
 */
void LedMatrix::drawEmptyness(){
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for(int i = 0; i < 16; i++){
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

/**
 * Draw a letter to the matrix.
 */
void LedMatrix::drawLetter(char asciiCode) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for (int i = 0; i < 8; i++) {
		Wire.write(font8x8_basic[(int) asciiCode][i]);
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

/**
 * Draw the matrix with stuff.
 */
void LedMatrix::drawMatrix(byte bits[]) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for (int i = 0; i < 8; i++) {
		Wire.write(rightCycleShift(bits[i]));
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

/**
 * get a unsigned char representing a row of a letter.
 */
unsigned char LedMatrix::getCharBock(int ascii, int row){
	return font8x8_basic[ascii][row];
}

/**
 * do a right cycle shift
 */
byte LedMatrix::rightCycleShift(byte in) {
	return (in >> 1 | in << 7);
}

/**
 * do a left cycle shift
 */
byte LedMatrix::leftCycleShift(byte in) {
	return (in << 1 | in >> 7);
}
