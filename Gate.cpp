#include "Gate.h"

// Function prototype definitions to update each gate type
char andUpdate(char one, char two);
char orUpdate(char one, char two);
char nandUpdate(char one, char two);
char norUpdate(char one, char two);
char xorUpdate(char one, char two);
char xnorUpdate(char one, char two);
char notUpdate(char one, char two);

// Gate constructor
Gate::Gate(Wire* in1, Wire* in2, Wire* out, int typ, int dly)
{
        input1 = in1;
        input2 = in2;
        output = out;
        type = typ;
        delay = dly;
}

// Gate destructor
Gate::~Gate()
{
    delete input1;
    delete input2;
    delete output;
}


// Gate update function
void Gate::update(int time, priority_queue<Event>* eq, int priority)
{
    // Bringing in the current wire values
    char one = (*input1).getValue();
    char two = (*input2).getValue();
    char ret;
    // Checking the gate type and calling the appropriate update function
    switch(type)
    {
        case 1:
        ret = andUpdate(one, two);
        break;
        case 2:
        ret = orUpdate(one, two);
        break;
        case 3:
        ret = nandUpdate(one, two);
        break;
        case 4:
        ret = norUpdate(one, two);
        break;
        case 5:
        ret = xorUpdate(one, two);
        break;
        case 6:
        ret = xnorUpdate(one, two);
        break;
        case 7:
        ret = notUpdate(one, two);
        default:
        break;
    }

    // Creating a new event to change the output wire
    // after the appropriate gate delay
    Event newEvent(time+delay, output, ret, priority);
    (*eq).push(newEvent);
}

// Update functions for each type of gate
char andUpdate(char one, char two)
{
    if((one == 'x' || two == 'x')&&(one == '-' || two == '-'))
    {
        return 'x';
    }
    if(one == '-' && two == '-')
    {
        return '-';
    }
    return '_';
}

char orUpdate(char one, char two)
{
    if((one == 'x' || two == 'x')&&(one == '_' || two == '_'))
    {
        return 'x';
    }
    if(one == '-' || two == '-')
    {
        return '-';
    }
    return '_';
}

char nandUpdate(char one, char two)
{
    if((one == 'x' || two == 'x')&&(one == '-' || two == '-'))
    {
        return 'x';
    }
    if(one == '-' && two == '-')
    {
        return '_';
    }
    return '-';
}

char norUpdate(char one, char two)
{
    if((one == 'x' || two == 'x')&&(one == '_' || two == '_'))
    {
        return 'x';
    }
    if(one == '_' && two == '_')
    {
        return '-';
    }
    return '_';
}

char xorUpdate(char one, char two)
{
    if(one == 'x' || two == 'x')
    {
        return 'x';
    }
    if(one == '-' && two == '_')
    {
        return '-';
    }
    if(one == '_' && two == '-')
    {
        return '-';
    }
    return '_';
}

char xnorUpdate(char one, char two)
{
    if(one == 'x' || two == 'x')
    {
        return 'x';
    }
    if(one == '-' && two == '_')
    {
        return '_';
    }
    if(one == '_' && two == '-')
    {
        return '_';
    }
    return '-';
}

char notUpdate(char one, char two)
{
    if(one == 'x')
    {
        return 'x';
    }
    if(one == '-')
    {
        return '_';
    }
    if(one == '_')
    {
        return '-';
    }
}
