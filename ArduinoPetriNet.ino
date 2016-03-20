// imports
#include <Servo.h>
#include "Helper.h"
#include "Enums.h"
#include "Place.h"
#include "Transition.h"
#include "Arc.h"



// global variables
// ====== places ======
Place *p_1;
Place *p_3;
Place **allPlaces;
int allPlacesCount;

// ====== transitions ======
Transition *t_4;
Transition *t_2;
Transition **allTransitions;
int allTransitionsCount;

// ====== arcs ======
Arc *a_150199539;
Arc *a_1218347417;
Arc *a_2040180576;
Arc *a_2109493155;
Arc **allArcs;
int allArcsCount;



// initial setup
void setup() {
Serial.begin(9600);

// ====== general ======
allPlacesCount = 2;
allPlaces = (Place**) malloc(allPlacesCount*sizeof(Place*));
allTransitionsCount = 2;
allTransitions = (Transition**) malloc(allTransitionsCount*sizeof(Transition*));
allArcsCount = 4;
allArcs = (Arc**) malloc(allArcsCount*sizeof(Arc*));

// ====== places ======
p_1 = new Place("p_1", 8, DIGITAL_OUT);
p_1->setCapacity(10);
p_1->setTokens(1);
allPlaces[0] = p_1;
p_3 = new Place("p_3", 13, DIGITAL_OUT);
p_3->setCapacity(10);
p_3->setTokens(0);
allPlaces[1] = p_3;

// ====== transitions ======
t_4 = new Transition("t_4", 4, DIGITAL_IN);
t_4->setAnalogThreshold(80);
allTransitions[0] = t_4;
t_2 = new Transition("t_2", 0, ANALOG_IN);
t_2->setAnalogThreshold(80);
allTransitions[1] = t_2;

// ====== arcs ======
a_150199539 = new Arc(p_1, t_4);
allArcs[0] = a_150199539;
a_1218347417 = new Arc(t_4, p_3);
allArcs[1] = a_1218347417;
a_2040180576 = new Arc(t_2, p_1);
allArcs[2] = a_2040180576;
a_2109493155 = new Arc(p_3, t_2);
allArcs[3] = a_2109493155;

// ====== wiring parts together ======
Arc** ta_4 = (Arc**) malloc( 2*sizeof(Arc*));
ta_4[0] = a_150199539;
ta_4[1] = a_1218347417;
t_4->setConnectedArcs(ta_4);
t_4->setConnectedArcsCount(2);
Arc** ta_2 = (Arc**) malloc( 2*sizeof(Arc*));
ta_2[0] = a_2040180576;
ta_2[1] = a_2109493155;
t_2->setConnectedArcs(ta_2);
t_2->setConnectedArcsCount(2);

}

// main infinite loop
void loop() {
for (int i = 0; i < allTransitionsCount; i++) {
    if (allTransitions[i]->isEnabled()) {     // todo: more facny logic
      allTransitions[i]->fire();
    }
  }
  
  for (int i = 0; i < allPlacesCount; i++) {
    allPlaces[i]->apply();
  }
    
  Serial.println("=================================================");
  delay(70);
}
