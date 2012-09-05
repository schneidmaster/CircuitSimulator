#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "Wire.h"

using namespace std;

class Input
{
    public:
    // Constructor
    Input(string inTag, Wire* input);

    // Member functions
    string getTag();
    Wire* getWire();
    void update(char newVal);

    private:
    // Attributes
    Wire* connect;
    string tag;
};

#endif
