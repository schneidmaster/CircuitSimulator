#include "Event.h"

// Constructor
Event::Event(int t, Wire* wireInput, char val, int p)
{
    time = t;
    whichWire = wireInput;
    value = val;
    prior = p;
}

// Time accessor
int Event::getTime()
{
    return time;
}

// Wire accessor
Wire* Event::getWire()
{
    return whichWire;
}

// Value accessor
char Event::getValue()
{
    return value;
}
