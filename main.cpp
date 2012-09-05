#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>

#include "Output.h"
#include "Gate.h"
#include "Wire.h"
#include "Event.h"
#include "Input.h"

using namespace std;

int main()
{
    ifstream in;

    string input;
    string crctName;
    string crctFile;
    string vectFile;
    string inLine;
    string part;
    string tag;
    string temp;

    int numcycl;
    int numtag;
    int loc;
    int loc1;
    int delay;
    int wire1;
    int wire2;
    int outwire;
    int type;
    int time;
    int priority;

    char tempc;

    vector<Wire*> wires;
    vector<Gate*> gates;
    vector<Input> inputs;
    vector<Output> outputs;

    priority_queue<Event> *eq = new priority_queue<Event>;

    // Getting circuit name
    cout<<"Welcome to SchneiderLOGIC Circuit Simulator!\n";
    cout<<"Please enter the base name of your circuit:\n";
    cout<<"~$ ";
    getline(cin, input, '\n');
    crctFile = input + ".txt";
    vectFile = input + "_vector.txt";

    // Opening circuit file
    in.open(crctFile.c_str(), ifstream::in);

    // Checking for existence
    while(!in)
    {
        cout<<"\nError: file "<<crctFile<<" does not exist.  Please try again.\n";
        cout<<"~$ ";
        getline(cin, input, '\n');
        crctFile = input + ".txt";
        vectFile = input + "_vector.txt";
        in.open(crctFile.c_str(), ifstream::in);
    }

    // Getting the first line (title line) and then taking in the first meaningful line
    getline(in, inLine, '\n');
    crctName = inLine;
    getline(in, inLine, '\n');

    // Processing all inputs and outputs
    while(inLine.substr(0,1)=="I"||(inLine.substr(0,2)=="OU"))
    {
        // Parsing the string to find the input/output tag
        loc = inLine.find(" ");
        while(inLine[loc]==' ')
        {
            loc++;
        }
        part = inLine.substr(loc, inLine.size()-loc);
        loc1 = part.find(" ");
        tag = inLine.substr(loc, loc1);

        // Parsing the string to find the wire index number and converting to int
        loc += loc1;
        while(inLine[loc]==' ')
        {
            loc++;
        }
        part = inLine.substr(loc, inLine.size()-loc1);
        numtag = atoi(part.c_str());

        // Checking to ensure that the tag is legal
        if(numtag<=0)
        {
            cout<<"Error: Wire tag less than or equal to zero."<<endl;
            return 0;
        }
        numtag++;

        // Resizing the wire vector to accommodate the tag of the new wire if necessary
        if(numtag>wires.size())
        {
            for(int i = numtag; i>(wires.size()); i--)
            {
                wires.push_back(NULL);
            }
        }
        if(numtag>wires.size())
        {
            wires.push_back(NULL);
        }
        numtag--;

        // Setting the wire in the correct vector index and increasing the vector size
        // Also creating a new input or output with the correct tag and linked to the correct wire
        if(inLine.substr(0,1)=="I")
        {
            if(wires[numtag]!=NULL)
            {
                cout<<"Error: Two inputs controlling the same wire."<<endl;
                return 0;
            }
            Wire* newWire = new Wire(numtag);
            wires[numtag] = newWire;
            Input newInput(tag, newWire);
            inputs.push_back(newInput);
        }
        if(inLine.substr(0,1)=="O")
        {
            if(wires[numtag]==NULL)
            {
                Wire* newWire = new Wire(numtag);
                wires[numtag] = newWire;
            }

            Output newOutput(tag, wires[numtag]);
            outputs.push_back(newOutput);
        }

        // Getting the next line
        getline(in, inLine, '\n');
    }

    // Parsing the file to find and load each gate
    while(!in.eof())
    {
        wire2 = 0;

        // Parsing the string to find the gate type
        loc = inLine.find(" ");
        tag = inLine.substr(0,loc);
        loc++;

        // Parsing the string to find the gate delay
        while(inLine[loc]==' ')
        {
            loc++;
        }
        part = inLine.substr(loc, inLine.size()-loc);
        loc1 = part.find("ns");
        temp = part.substr(0, loc1);
        delay = atoi(temp.c_str());
        loc = part.find(" ");
        while(part[loc]==' ')
        {
            loc++;
        }

        // Parsing the string to find first input wire
        part = part.substr(loc, part.size()-loc);
        loc = part.find(" ");
        temp = part.substr(0, loc);
        wire1 = atoi(temp.c_str());
        while(part[loc]==' ')
        {
            loc++;
        }

        if(tag!="NOT")
        {
            // Parsing the string to find second input wire
            part = part.substr(loc, part.size()-loc);
            loc = part.find(" ");
            temp = part.substr(0, loc);
            wire2 = atoi(temp.c_str());
        }

        // Parsing the string to find outwire
        loc = part.find(" ");
        while(part[loc]==' ')
        {
            loc++;
        }
        part = part.substr(loc, part.size()-loc);
        outwire = atoi(part.c_str());

        // Putting the gate on the vector
        type = 0;
        if(tag == "AND")
        {
            type = 1;
        }
        if(tag == "OR")
        {
            type = 2;
        }
        if(tag == "NAND")
        {
            type = 3;
        }
        if(tag == "NOR")
        {
            type = 4;
        }
        if(tag == "XOR")
        {
            type = 5;
        }
        if(tag == "XNOR")
        {
            type = 6;
        }
        if(tag == "NOT")
        {
            type = 7;
        }
        if(type == 0)
        {
            cout<<"Error: Gate type "<<tag<<"not recognized."<<endl;
            return 0;
        }

        // Making a new gate and putting it on the vector
        // Finding the largest wiretag and increasing the vector size if needed
        if(wire1>=wire2)
        {
            if(wire1>=outwire)
            {
                numtag = wire1;
            }
            else
            {
                numtag = outwire;
            }
        }
        else
        {
            if(wire2>=outwire)
            {
                numtag = wire2;
            }
            else
            {
                numtag = outwire;
            }
        }

        if(numtag>wires.size())
        {
            for(int i = numtag; i>(wires.size()); i--)
            {
                wires.push_back(NULL);
            }
        }
        // Creating a new wire with the right tag if needed
        if(wires[wire1]==NULL)
        {
            Wire* newWire = new Wire(wire1);
            wires[wire1] = newWire;
        }
        if(type!=7 && wires[wire2]==NULL)
        {
            Wire* newWire = new Wire(wire2);
            wires[wire2] = newWire;
        }
        if(wires[outwire]==NULL)
        {
            Wire* newWire = new Wire(outwire);
            wires[outwire] = newWire;
        }
        if(type == 7)
        {
            wire2=wire1;
        }
        Gate* newGate = new Gate(wires[wire1],wires[wire2],wires[outwire],type, delay);

        gates.push_back(newGate);

        // Adding the gate to each wire's driving vector
        (*wires[wire1]).addToDriving(newGate);
        // If statement so if the same wire drives both inputs of a gate,
        // the gate isn't added twice
        if(wires[wire1]!=wires[wire2])
        {
            (*wires[wire2]).addToDriving(newGate);
        }

        // Getting the next line
        getline(in, inLine, '\n');
        // So the program doesn't break for blank lines at the end of a file
        if(inLine == "")
        {
            break;
        }
    }

    // Closing the circuit file and opening the vector file
    in.close();
    in.open(vectFile.c_str());
    priority = 0;

    // Checking for existence
    while(!in)
    {
        cout<<"\nError: file "<<crctFile<<"_vector.txt does not exist.  Please try again.\n";
        cout<<"~$ ";
        getline(cin, input, '\n');
        vectFile = input + "_vector.txt";
        in.open(vectFile.c_str(), ifstream::in);
    }
    // Getting the number of cycles to simulate
    cout<<"\nHow many cycles would you like to simulate?\n";
    cout<<"~$ ";
    cin>>numcycl;

    // Checking for a good number
    while(numcycl<=0)
    {
        cout<<"\nError: You must simulate at least one cycle.";
        cout<<"\nHow many cycles would you like to simulate?\n";
        cout<<"~$ ";
        cin>>numcycl;
    }

    // Discarding the title line and taking the first meaningful line
    getline(in, inLine, '\n');
    getline(in, inLine, '\n');

    while(!in.eof() && inLine!="")
    {
        // Discarding the "Input" and every space after it
        loc = inLine.find(" ");
        while(inLine[loc]==' ')
        {
            loc++;
        }
        // Finding the tag
        part = inLine.substr(loc,inLine.size()-loc);
        loc = part.find(" ");
        tag = part.substr(0,loc);

        // Finding the time
        while(part[loc] == ' ')
        {
            loc++;
        }
        part = part.substr(loc, part.size()-loc);
        loc = part.find(" ");
        temp = part.substr(0,loc);
        wire1 = atoi(temp.c_str());

        // Finding the new value
        while(part[loc]==' ')
        {
            loc++;
        }
        part = part.substr(loc, part.size()-loc);
        tempc = part[0];

        switch(tempc)
        {
            case '1':
            tempc = '-';
            break;
            case '0':
            tempc = '_';
            break;
            default:
            cout<<"Error: All wire values must be 1 or 0.  Value "<<tempc<<" is not allowed."<<endl;
            return 0;
        }

        // Finding the input that corresponds
        bool test = false;
        for(int i=0; i<inputs.size(); i++)
        {
            if(inputs[i].getTag()==tag)
            {
                // Pushing a new event using that input's Wire
                Event newEv(wire1, inputs[i].getWire(), tempc, priority);
                (*eq).push(newEv);
                test = true;
            }
        }

        // Error if a nonexistent input was modified in the vector file
        if(!test)
        {
            cout<<"Error: Attempting to change nonexisting input "<<tag<<"."<<endl;
            return 0;
        }
        priority++;
        getline(in, inLine, '\n');
    }

    // Running the simulation
    for(time=0; time<numcycl; time++)
    {
        // Check for events
        if(!(*eq).empty())
        {
            Event toHandle = (*eq).top();
            // If the top event has the same time as the current time
            while(toHandle.getTime()==time&&!(*eq).empty())
            {
                // Popping the top event off
                (*eq).pop();
                // Getting the wire
                Wire* toUpdate = toHandle.getWire();
                // Setting its new value
                (*toUpdate).setValue(toHandle.getValue());
                // Updating its vector of gates
                priority = (*toUpdate).updateDriving(time, eq, priority);
                // Reloading the top event if the event queue is not empty
                if(!(*eq).empty())
                {
                    toHandle = (*eq).top();
                }
            }
        }

        // Poke each output
        for(int i=0; i<outputs.size(); i++)
        {
            // Poke function causes the output to print its current value to the output string
            (outputs[i]).poke();
        }
        // Runs three more cycles then quits if no more events to process
        if((*eq).empty())
        {
            for(int i=0; i<2; i++)
            {
                for(int j=0; j<outputs.size(); j++)
                {
                    (outputs[j]).poke();
                }
            }
            break;
        }

    }

    // Finding longest output for clean printing purposes
    int longest=0;
    for(int i=0; i<outputs.size(); i++)
    {
        int comp = (outputs[i].getTag()).size();
        if(comp>longest)
        {
            longest = comp;
        }
    }

    // Printing circuit name
    cout<<endl<<crctName<<endl;
    // Printing outputs
    for(int i=0; i<outputs.size(); i++)
    {
        string toPrint = outputs[i].getTag();
        for(int i = toPrint.size();i<=longest;i++)
        {
            toPrint += " ";
        }
        cout<<toPrint;
        outputs[i].print();
    }
    if(time!=numcycl)
    {
        cout<<endl<<endl<<"Note: Simulation stopped after "<<time<<" cycles due to no further activity.\n";
    }
    return 0;
}
