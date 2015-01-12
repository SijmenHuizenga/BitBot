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
    int adres;
  public:
    LedMatrix(int);
    void setBrightness(int);
    void setBlink(int);
    void drawEmptyness();
    void drawSmiley(bool);
    void drawLetter(char);
    void drawMatrix(byte bits[]);
    byte rightCycleShift(byte);
    byte leftCycleShift(byte);
    unsigned char getCharBock(int ascii, int row);
};

#endif
