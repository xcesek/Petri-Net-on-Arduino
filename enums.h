#ifndef Enums_h
#define Enums_h

#include "Arduino.h"


enum FunctionType {
  digitalIn, digitalOut, analogIn, analogOut, 
  servo, PWMmotor, buzzer,
  diode, 
  potentiometer, thermometer, microphone, ultrasonicSensor,
  button
};

enum ArcType {
  standard, inhibitor, test
};

enum NodeType {
  placeType, transitionType
};

enum logLevel {
  info, debug, warn, error 
};

#endif
