#ifndef WIRE_H
#define WIRE_H

#include <vector>
#include <queue>

using namespace std;

class Gate;
class Event;

class Wire
{
    public:
    // Constructor
    Wire(int inTag);

    // Destructor
    ~Wire();

    // Member function definitions
    char getValue();
    void setValue(char val);
    void addToDriving(Gate* val);
    int updateDriving(int time, priority_queue<Event>* eq, int priority);

    private:
    // Attributes
    char value;
    vector<Gate*> driving;
    int tag;
};

#endif
