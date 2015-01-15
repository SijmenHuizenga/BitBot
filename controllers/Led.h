/*
 * Led.h
 *
 *  Created on: 19 dec. 2014
 *      Author: Sijmen
 */

#ifndef LedControl_h
#define LedControl_h

#include "Arduino.h"

class LedController{
    private:
	  /**
	   * de fiezieke pins op de arduino
	   */
      byte pins[8];
    public:
      /**
       * constructor.
       */
      LedController();

      /**
       * zet een bepaalde led aan
       */
      void setLedOn(byte, boolean);

      /**
       * zet alle leds uit
       */
      void resetLights();

      /**
       * hoeveel leds zijn er?
       */
      int getLedAmount();		

      /**
       * geef een string met alle statussen van de leds
       */
      String getCurState();
};

#endif
