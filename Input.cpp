#include "Input.h"

// Constructor
Input::Input(string inTag, Wire* input)
{
    connect = input;
    tag = inTag;
}

// Tag accessor
string Input::getTag()
{
    return tag;
}

// Wire accessor
Wire* Input::getWire()
{
    return connect;
}
