#include "Wire.h"
#include "Gate.h"

// Constructor
Wire::Wire(int inTag)
{
    value = 'x';
    tag = inTag;
}

// Destructor
Wire::~Wire()
{
    for(int i=0; i<driving.size(); i++)
    {
        delete driving[i];
    }
}

// Accessor
char Wire::getValue()
{
    return value;
}

// Mutator
void Wire::setValue(char val)
{
    value = val;
    return;
}

// Adds a Gate to the vector of gates the wire drives
void Wire::addToDriving(Gate* val)
{
    driving.push_back(val);
    return;
}

// Calls the update function of each gate in the driving vector
int Wire::updateDriving(int time, priority_queue<Event>* eq, int priority)
{
    for(int i=0; i<driving.size(); i++)
    {
        Gate* test = driving[i];
        (*test).update(time, eq, priority);
        priority++;
    }
    return priority;
}
