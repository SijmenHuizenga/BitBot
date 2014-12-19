#ifndef LedControl_h
#define LedControl_h

#include "Arduino.h"

class LedController{
    private:
      byte pins[8];
    public:
      LedController();
      void initilize();
      void setLedOn(byte, boolean);
      void resetLights();
      int getLedAmount();		
      String getCurState();
};

#endif
