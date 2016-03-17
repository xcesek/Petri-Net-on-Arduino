#ifndef Node_h
#define Node_h

#include "Arduino.h"
#include "Helper.h"
#include "Enums.h"

class Node
{
  protected:
    char *id;
    int pin;
    FunctionType functionType;
    int extended;
    
  public:
    Node(char* id);
    Node(char* id, int _pin, FunctionType _functionType);
};

#endif
