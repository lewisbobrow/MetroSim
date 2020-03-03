// 
// Main.cpp
// Lewis Bobrow
// 2/20/19
//

#include <iostream>
#include <fstream>
#include <string>
#include "MetroSim.h"
using namespace std;

int main(int argc, char* argv[]){
	argc = 4;
//passes the command line arguments into strings.
	string file1 = argv[1];
	string file2 = argv[2];
//checks if there is a command file
	if(argv[3] == NULL){
		string file3 = "";
	} else {
		string file3 = argv[3];
	}
//checks if the command is valid
	if((argv[1] == NULL) || (argv[2] == NULL)){
		cerr << "Usage: MetroSim stationsFile passFile [comands]" << endl;
		return 0;
	}
//creates a MetroSim class
	MetroSim sim;
	sim.stationsFile = argv[1];
	sim.passFile = argv[2];
//reads in the command file (empty string if command-line is empty)
	if(argv[3] == NULL){
		sim.commandsFile = "";
	} else{
		sim.commandsFile = argv[3];
	}
//assigns station numbers to the class using the stations file 
//in the command line
	sim.assignStationNumbers();
//checks if the simulation is over, if it is, executes the commands until
//the simulation is over.
	while(sim.isOver() == false){
//checks if there is a command file. if there is, the program reads from that,
//if not, reads from user inputs.
		if(argv[3] == NULL){
			sim.getCommand("");
		} else{
			sim.readCommand();
		}
	}
//prints the exit message at the end of the while loop
	cerr << "Thanks for playing MetroSim. Have a nice day!" << endl;

	return 0;
}
