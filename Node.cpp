#include "Arduino.h"
#include "Node.h"
#include "Helper.h"

Node::Node(char* _id)
{
  id = _id;
  extended = 0;
}

Node::Node(char* _id, int _pin, FunctionType _functionType)
{
  id = _id;
  pin = _pin;
  functionType = _functionType;
  extended = 1;
  Helper::log(1,"(place) initializing -> ", id);
};
