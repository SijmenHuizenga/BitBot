/*
 * LedMatrix.h
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#ifndef SRC_MATRIXCONTROL_H_
#define SRC_MATRIXCONTROL_H_

#include "Arduino.h"

class LedMatrix {
  private:

	/**
	 * de fiezieke pin op de arduino
	 */
    int adres;
  public:

    /**
     * constructor: argument is de fizieke pin
     */
    LedMatrix(int);

    /**
     * brightness between 0 and 15 where 0 is
     * 1/16 brightness
     * and 15 is 16/16 brightness
     */
    void setBrightness(int);

    /**
     * amount between 1 and 7 where:
     * 1 = blink off
     * 3 = 2 hz
     * 5 = 0.5 hz
     */
    void setBlink(int);

    /**
     * draw void onto the led matrix
     */
    void drawEmptyness();

    /**
     * Every one loves a smiley. So this function shows this smyle
     * to the display. Wether the smily is happy or not can be
     * said by the bool argument.
     */
    void drawSmiley(bool);

    /**
     * Draw a letter to the matrix.
     */
    void drawLetter(char);

    /**
     * Draw the matrix with stuff.
     */
    void drawMatrix(byte bits[]);

    /**
     * do a right cycle shift
     */
    byte rightCycleShift(byte);

    /**
     * do a left cycle shift
     */
    byte leftCycleShift(byte);

    /**
     * get a unsigned char representing a row of a letter.
     */
    unsigned char getCharBock(int ascii, int row);
};

#endif
