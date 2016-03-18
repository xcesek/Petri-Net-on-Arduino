#ifndef Transition_h
#define Transition_h

#include "Arduino.h"
#include "Helper.h"
#include "Enums.h"
#include "Arc.h"
#include "Place.h"

class Transition : public Node
{
  private:
    Arc **connectedArcs;
    int connectedArcsCount;
    
    Place **inPlaces;
    int inPlacesCount;
    Place **outPlaces;
    int outPlacesCount;
    int analogTreshold;
    int analogTresholdRangeLow;
    int analogTresholdRangeHigh;
    
  public:
    Transition(char* id, Place **_inPlaces, int _inPlacesCount, Place **_outPlaces, int _outPlacesCount);
    Transition(char* id, int _pin, FunctionType _functionType, Place **_inPlaces, int _inPlacesCount, Place **_outPlaces, int _outPlacesCount);
    void fire();
    int isEnabled();
    Arc **getConnectedArcs();
    int getConnectedArcsCount();
    
    void setAnalogTreshold(int _analogTreshold);
    void setAnalogTresholdRange(int _analogTresholdRangeLow, int _analogTresholdRangeHigh);
};

#endif

