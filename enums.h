#ifndef Enums_h
#define Enums_h

#include "Arduino.h"


enum FunctionType {
  digitalIn, digitalOut, analogIn, analogOut, servo 
};

enum ArcType {
  standard, inhibitor, test
};

#endif
