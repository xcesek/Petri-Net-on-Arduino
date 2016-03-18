#include <Servo.h>

#include "Helper.h"
#include "Enums.h"
#include "Place.h"
#include "Transition.h"
#include "Arc.h"


// ====== places ======
Place *place0;
Place *place1;
Place **allPlaces;
int allPlacesCount;

// ====== transitions ======
Transition *transition0;
Transition *transition1;
Transition **allTransitions;
int allTransitionsCount;

// ====== arcs ======
Arc *arc0;
Arc *arc1;
Arc *arc2;
Arc *arc3;
Arc **allArcs;
int allArcsCount;

void setup()
{
  Serial.begin(9600);
  
  // ====== general ======
  allPlacesCount = 2;
  allPlaces = (Place**) malloc(allPlacesCount*sizeof(Place*));
  
  allTransitionsCount = 2;
  allTransitions = (Transition**) malloc(allTransitionsCount*sizeof(Transition*));
  
  allArcsCount = 4;
  allArcs = (Arc**) malloc(allArcsCount*sizeof(Arc*));


  // ====== places ======
  //0.
  place0 = new Place("place0", 13, digitalOut);
  place0->setCapacity(10);
  place0->setTokens(1);
  allPlaces[0] = place0;
  
  //1.
  place1 = new Place("place1", 7, digitalOut);
  place1->setCapacity(10);
  place1->setTokens(0);
  allPlaces[1] = place1;
  
  
  // ====== transitions ======  
  transition0 = new Transition("t0", 0, analogIn);
  transition0->setAnalogTreshold(80);
  //transition0->setAnalogTresholdRange(80, 150);
  allTransitions[0] = transition0;
  
  transition1 = new Transition("t1", 4, digitalIn);
  allTransitions[1] = transition1;
  
  
  // ====== arcs ======
  arc0 = new Arc(place0, transition0);
  allArcs[0] = arc0;
  
  arc1 = new Arc(transition0, place1);
  allArcs[1] = arc1;
  
  arc2 = new Arc(place1, transition1);
  allArcs[2] = arc2;
  
  arc3 = new Arc(transition1, place0);
  allArcs[3] = arc3;
  
  
  // ====== wiring parts together ======
  Arc** t1arcs = (Arc**) malloc(2*sizeof(Arc*));
  t1arcs[0] = arc0;
  t1arcs[1] = arc1;
  transition0->setConnectedArcs(t1arcs);
  transition0->setConnectedArcsCount(2);
  
  
  Arc** t2arcs = (Arc**) malloc(2*sizeof(Arc*));
  t2arcs[0] = arc2;
  t2arcs[1] = arc3;
  transition1->setConnectedArcs(t2arcs);
  transition1->setConnectedArcsCount(2);
  
}

void loop()
{  
  for (int i = 0; i < allTransitionsCount; i++) {
    if (allTransitions[i]->isEnabled()) {     // todo: more facny logic
      allTransitions[i]->fire();
    }
  }
  
  for (int i = 0; i < allPlacesCount; i++) {
    allPlaces[i]->apply();
  }
    
  Serial.println("=================================================");
  delay(7000);
}

