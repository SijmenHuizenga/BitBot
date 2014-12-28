/*
 * MotorController.h
 *
 *  Created on: 20 dec. 2014
 *      Author: Sijmen
 */

#ifndef HEADERS_SERVOMOTOR_H_
#define HEADERS_SERVOMOTOR_H_

#include <Servo.h>
#include "Arduino.h"

class ServoMotor{
  private:
    int curSpeed;
    bool inverted;

    /**
     * At what microseconds is the servo off:
     */
    static const int off = 1505;
    /**
     * How much does the servo go up from the off
     * point until it reaches max speed.
     *
     * According to the documentation at
     * http://learn.parallax.com/node/207 is the
     * max speed at 1700us. But the upper half
     * is horizontal. This whould kill our calculations
     * so here is choosen to not use this upper part.
     */
    static const int marge = 100;

    Servo* servo;

  public:
    /**
     * int: is the phisical pin on the arduino that is connected to the motor.
     * boolean: wether or not the wheel is inverted.
     */
    ServoMotor(int, bool);

    /**
     * deconstructor. Closes teh servo.
     */
    ~ServoMotor();

    /**
     * Sets the speed of the motor.
     * This speed can have the following values:
     * set speed in persentage. From -100 to 100.
     *  +100 is full speed forward
     *  0 off
     *  -100 is full speed backwards
     *
     */
    void setSpeed(int);
    /**
     * sets the raw speed of the servo. Shoud be between 0 and 180.
     */
    void setRawSpeed(int);
};

#endif /* HEADERS_SERVOMOTOR_H_ */
