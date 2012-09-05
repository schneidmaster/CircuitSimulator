#ifndef EVENT_H
#define EVENT_H

#include "Wire.h"

class Event
{
    public:
    // Constructor
    Event(int t, Wire* wireInput, char val, int p);

    // Overloaded < operator for priority queue
    // Defined here since it is a friend
    friend bool operator < (const Event& one, const Event& two)
    {
        if(one.time<two.time)
        {
            return false;
        }
        if(one.time>two.time)
        {
            return true;
        }
        if (one.time == two.time)
        {
            if(one.prior>two.prior) return true;
            else return false;
        }
    }

    // Member functions
    int getTime();
    Wire* getWire();
    char getValue();

    private:
    // Attributes
    int time;
    Wire* whichWire;
    char value;
    int prior;
};

#endif
