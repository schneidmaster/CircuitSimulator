#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>

#include "Wire.h"

using namespace std;

class Output
{
    public:
        // Constructor
        Output(string inTag, Wire* input);

        // Member function definitions
        string getTag();
        void print();
        void poke();

    private:
        // Attributes
        Wire* connect;
        string tag;
        string line;
};

#endif
