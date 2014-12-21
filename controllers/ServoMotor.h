/*
 * MotorController.h
 *
 *  Created on: 20 dec. 2014
 *      Author: Sijmen
 */

#ifndef HEADERS_SERVOMOTOR_H_
#define HEADERS_SERVOMOTOR_H_

#include <Servo.h>

class ServoMotor{
  private:
    int curSpeed;
    bool inverted;

    static const int off = 1505;  //what is the zero point?
    static const int marge = 200; //how much up can i go?

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
     * set speed in persentage. From 0 to 100.
     */
    void setSpeed(int);
    /**
     * sets the raw speed of the servo. Shoud be between 0 and 180.
     */
    void setRawSpeed(int);
};

#endif /* HEADERS_SERVOMOTOR_H_ */
