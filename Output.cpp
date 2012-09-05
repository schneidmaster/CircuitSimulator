#include "Output.h"

// Constructor
Output::Output(string inTag, Wire* input)
{
    // Note: Aliasing done on purpose.  That way, the output will automatically update with whatever is in
    // its connecting wire, saving me some code since the output does not need to be stored separately
    connect = input;
    tag = inTag;
    line = "";
}

// Prints the contents of the output's string
void Output::print()
{
    cout<<line<<endl;
}

// Appends the current value of the connected wire to the output string
void Output::poke()
{
    line+=(*connect).getValue();
}

// Tag accessor
string Output::getTag()
{
    return tag;
}


