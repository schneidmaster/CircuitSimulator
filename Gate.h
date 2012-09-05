#ifndef GATE_H
#define GATE_H

#include <queue>
#include "Wire.h"
#include "Event.h"

class Wire;

class Gate
{
    public:
    // Constructor
    Gate(Wire* input1, Wire* input2, Wire* output, int type,int dly);

    // Destructor
    ~Gate();

    // Member function definitions
    void update(int time, priority_queue<Event>* eq, int priority);
    // Note: Since the gate only aliases the wires and does not new anything,
    // it requires no destructor.

    private:
    // Attributes
    Wire* input1;
    Wire* input2;
    Wire* output;
    int delay;
    int type;
        //Notes on type:
        //1 = AND
        //2 = OR
        //3 = NAND
        //4 = NOR
        //5 = XOR
        //6 = XNOR
        //7 = NOT
};

#endif // GATE_H
