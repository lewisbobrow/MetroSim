// 
// MetroSim.h
// Lewis Bobrow
// 2/20/19
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>
using namespace std;

#ifndef _METROSIM_H_
#define _METROSIM_H_

//optional
struct Passenger
{
	int id;
	int source;
	int destination;
	bool onTrain;
	bool erased;
};

//optional
struct Station
{
	string name;
	int stationNum;
};


class MetroSim{
public:
	MetroSim();
	~MetroSim();
	void assignStationNumbers();
	void addToStation(string command);
	bool isOver();
	void advanceTrain();
	string passAtStation(Station sta);
	string printPassengers();
	string printStationsHelper(int i);
	string printStations();
	void printMap();
	void getCommand(string command);
	void readCommand();
	string passFile;
	string commandsFile;
	string stationsFile;
private:
	int trainNum;
	int passCounter;
	bool isReverse;
	bool endSim;
	vector<Station> s;
	vector<Passenger> p;
};

#endif