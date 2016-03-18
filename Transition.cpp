#include "Arduino.h"
#include "Transition.h"
#include "Arc.h"
#include "Helper.h"
#include "Enums.h"

Transition::Transition(char* _id, Place **_inPlaces, int _inPlacesCount, Place **_outPlaces, int _outPlacesCount)
: Node(_id, transitionType)
{  
  inPlaces = _inPlaces;
  inPlacesCount = _inPlacesCount;
  outPlaces = _outPlaces;
  outPlacesCount = _outPlacesCount;
  
  analogTreshold = -1;
  analogTresholdRangeLow = -1;
  analogTresholdRangeHigh = -1;
}


Transition::Transition(char* _id, int _pin, FunctionType _functionType, Place **_inPlaces, int _inPlacesCount, Place **_outPlaces, int _outPlacesCount)
: Node(_id, transitionType, _pin, _functionType)
{ 
  inPlaces = _inPlaces;
  inPlacesCount = _inPlacesCount;
  outPlaces = _outPlaces;
  outPlacesCount = _outPlacesCount;
  
  analogTreshold = -1;
  analogTresholdRangeLow = -1;
  analogTresholdRangeHigh = -1;
  
  Serial.print("(transition) initializing -> "); Serial.print(id);  Serial.print(" -> ");
  
  switch (functionType) {
    case digitalIn:
      pinMode(pin, INPUT);
      Serial.println("digitalIn");
      break;
    case digitalOut: 
      // what?
      pinMode(pin, OUTPUT);
      Serial.println("digitalOut");
      break;
    case analogIn:
      // nothing to do - works out of the box
      Serial.println("analogIn");
      break;
    case analogOut: 
      // what?
      pinMode(pin, OUTPUT);  //yes, analog out is done through PWM
      Serial.println("analogOut");
      break;
  }
}

void Transition::fire()
{
  Serial.print("(transition) firing "); Serial.println(id);
  Serial.print("   (transition) funtions: "); Serial.println(functionType);
  Serial.print("   (transition) inPlacesCount: "); Serial.println(inPlacesCount);
  Serial.print("   (transition) outPlacesCount: "); Serial.println(outPlacesCount);
  
  for (int i = 0; i < inPlacesCount; i++) {
    inPlaces[i]->removeTokens(1);
  }
  // delay ?
  
  for (int i = 0; i < outPlacesCount; i++) {
    outPlaces[i]->addTokens(1);
  }
}

int Transition::isEnabled()
{
  Serial.print("(transition) isActive? "); Serial.println(id);
  int internalTriggerActive = 0;

  // internal guard
  internalTriggerActive = 1;
  for (int i = 0; i < inPlacesCount; i++) {
    if (inPlaces[i]->getTokens() < 1) internalTriggerActive = 0;
  }
  Serial.print("(transition) internal > "); Serial.println(internalTriggerActive);
  if (!extended) {
    return internalTriggerActive; 
  }
  
  // external guard
  int readValue;
  int externalTriggerActive = 0;
  switch (functionType) {
    case digitalIn:
      readValue = digitalRead(pin);
      Serial.print("   (transition) digital read value: "); Serial.println(readValue);
      if(readValue == 1) externalTriggerActive = 1;
      break;
      
    case digitalOut: 
      // what?
      break;
      
    case analogIn:
      readValue = analogRead(pin);
      Serial.print("   (transition) analog read value: "); Serial.println(readValue);
      if((analogTreshold != -1) && (readValue > analogTreshold)) externalTriggerActive = 1;
      if((analogTresholdRangeLow != -1) && (analogTresholdRangeLow < readValue) && (readValue < analogTresholdRangeHigh)) externalTriggerActive = 1;
      break;
      
    case analogOut: 
      // what?
      break;
  }
  Serial.print("   (transition) isActive: "); Serial.println(internalTriggerActive && externalTriggerActive);
  return internalTriggerActive && externalTriggerActive;
}

Arc **Transition::getConnectedArcs() {
  return connectedArcs;
}

int Transition::getConnectedArcsCount() {
  return connectedArcsCount;
}

void Transition::setAnalogTreshold(int _analogTreshold) {
  analogTreshold = _analogTreshold;
  Serial.print("(transition) setting analogTreshold: "); Serial.println(analogTreshold);
}

void Transition::setAnalogTresholdRange(int _analogTresholdRangeLow, int _analogTresholdRangeHigh) {
  analogTresholdRangeLow = _analogTresholdRangeLow;
  analogTresholdRangeHigh = _analogTresholdRangeHigh;
  Serial.print("(transition) setting analogTresholdRange: "); Serial.print(analogTresholdRangeLow);Serial.print(" - ");Serial.println(analogTresholdRangeHigh);
}


