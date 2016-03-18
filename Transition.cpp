#include "Arduino.h"
#include "Transition.h"
#include "Arc.h"
#include "Helper.h"
#include "Enums.h"

Transition::Transition(char* _id)
: Node(_id, transitionType)
{  
  analogTreshold = -1;
  analogTresholdRangeLow = -1;
  analogTresholdRangeHigh = -1;
}


Transition::Transition(char* _id, int _pin, FunctionType _functionType)
: Node(_id, transitionType, _pin, _functionType)
{ 
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
  Serial.print("   (transition) connectedArcsCount: "); Serial.println(connectedArcsCount);
  
  for (int i = 0; i < connectedArcsCount; i++) {
    Node *source = connectedArcs[i]->getSource();
    if (source->getNodeType() == placeType) {
      Place *place = (Place*) source;
      place->removeTokens(connectedArcs[i]->getMultiplicity());
    }
  }
  // delay ?
  
  for (int i = 0; i < connectedArcsCount; i++) {
    Node *destination = connectedArcs[i]->getDestination();
    if (destination->getNodeType() == placeType) {
      Place *place = (Place*) destination;
      place->addTokens(connectedArcs[i]->getMultiplicity());
    }
  }
}

int Transition::isEnabled()
{
  Serial.print("(transition) isEnabled? "); Serial.println(id);

  // internal condition
  int internalTriggerActive = 1;
  for (int i = 0; i < connectedArcsCount; i++) {
    Node *source = connectedArcs[i]->getSource();
    if (source->getNodeType() == placeType) {
      Place *place = static_cast<Place*>(source);
      if (place->getTokens() < connectedArcs[i]->getMultiplicity()) internalTriggerActive = 0;
    }
  }
  Serial.print("(transition) internal : "); Serial.println(internalTriggerActive);
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

void Transition::setConnectedArcs(Arc **arcs) {
  connectedArcs = arcs;
}

void Transition::setConnectedArcsCount(int count) {
  connectedArcsCount = count;
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


