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
    
    int analogTreshold;
    int analogTresholdRangeLow;
    int analogTresholdRangeHigh;
    
  public:
    Transition(char* id);
    Transition(char* id, int _pin, FunctionType _functionType);
    void fire();
    int isEnabled();
    void setConnectedArcs(Arc **arcs);
    void setConnectedArcsCount(int count);
    Arc **getConnectedArcs();
    int getConnectedArcsCount();
    
    void setAnalogTreshold(int _analogTreshold);
    void setAnalogTresholdRange(int _analogTresholdRangeLow, int _analogTresholdRangeHigh);
};

#endif

