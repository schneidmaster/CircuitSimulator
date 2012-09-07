CircuitSimulator
==============

 * CircuitSimulator
 * version: 1.0
 * @requires C++
 * @homepage https://github.com/schneidmaster/circuitsimulator
 * 
 * written by Zach Schneider (@schneidmaster)
 * (c) 2011
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

An event-driven circuit simulator, written in C++ and designed to print to terminal output.

Set up as a code::blocks (http://www.codeblocks.org/) project; done for Object-Oriented Design in C++ in April 2011.

* Usage

Set up circuit using a circuit file (see circuits/crct.txt for example).  First line is the name of the circuit.  Lines beginning with INPUT or OUTPUT mark an input or output; give them a name and a wire number.  Lines beginning with NOT, AND, OR, NOR, XOR are gates, second argument is gate delay, third and fourth arguments are the two input wires, fifth argument is the output wire.  (For a NOT gate, third argument is the input wire and fourth argument is the output wire).

Then, set up a circuit vector file (see circuits/crct_vector.txt for example; the vector must have the same name as the circuit with _vector appended to the end).  The first line is, again, the name.  The following lines are arbitrary: what input you want to control, then what time (how many clock cycles into simulation) you want the change to take place, then what change you want (1 for high, 0 for low).

Finally, compile with the C++ compiler of your choice (with g++, "g++ main.cpp Event.cpp Input.cpp Wire.cpp Gate.cpp Output.cpp"), run ("./a.out"), and enter your circuit base name and number of cycles to simulate when prompted (for the example above, "circuits/crct" would work).