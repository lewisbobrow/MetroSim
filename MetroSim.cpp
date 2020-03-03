
// 
// MetroSim.cpp
// Lewis Bobrow
// 2/20/19
//

#include "MetroSim.h"

//deafult constructor
MetroSim::MetroSim(){
	trainNum = 0;
	passCounter = 0;
	stationsFile = "";
	commandsFile = "";
	passFile = "";
	isReverse = false;
	endSim = false;
	vector<Station> s;
	vector<Passenger> p;
}

//destructor
MetroSim::~MetroSim(){
	s.clear();
	p.clear();
}

// Input: nothing
// Returns: boolean value
// Does: returns whether the simulation is over or not
bool MetroSim::isOver(){
	if(endSim){
		return true;
	} else{
		return false;
	}
}

// Input: nothing
// Returns: nothing
// Does: goes through the stations file and creates a struct of each one.
//       Assigns station numbers and stations names to the struct.
//       Pushes these structs into a vector.
void MetroSim::assignStationNumbers(){
	ifstream inFile;
	string staName;
	int counter = 1;
	inFile.open(stationsFile);
	if(!inFile.is_open()){
		return;
	}
	while(!inFile.eof()){
		Station sta;
		getline(inFile, staName);
		sta.name = staName;
		sta.stationNum = counter;
		s.push_back(sta);
		counter++;
	}
	inFile.close();
}

// Input: string
// Returns: nothing
// Does: creates a passenger struct and assigns passenger id, source,
//       destination, whether it is on the train or not, and whether
//       it has completed its ride. Pushes this struct onto the
//       vector and writes the info about the passenger to the
//       stations file.
void MetroSim::addToStation(string command){
	stringstream ss(command);
	string a, b, c;
	ss >> a;
	ss >> b;
	ss >> c;
	Passenger pass;
	passCounter++;
	pass.id = passCounter;
	pass.source = stoi(b);
	pass.destination = stoi(c);
	pass.erased = false;
	if(trainNum == stoi(b)){
		pass.onTrain = true;
	} else{
		pass.onTrain = false;
	}
	p.push_back(pass);
	ofstream outFile;
	outFile.open(passFile);
	outFile << pass.id << " " << pass.source << " " 
	        << pass.destination << endl;
	outFile.close();
}

// Input: nothing
// Returns: nothing
// Does: advances the train and updates all of the passengers in the struct
void MetroSim::advanceTrain(){
	int stationSize = static_cast<int>(s.size());
	int passSize = static_cast<int>(p.size());
	if(!isReverse){
		trainNum++;
	} else {
		trainNum--;
	}
	if((trainNum == stationSize) && (!isReverse)){
		isReverse = !isReverse;
		reverse(s.begin(), s.end());
	} else if((trainNum == 1) && (isReverse)){
		isReverse = !isReverse;
		reverse(s.begin(), s.end());
	}
	for(int i = 0; i < passSize; i++){
		if(p.at(i).destination == trainNum){
			p.at(i).onTrain = false;
			p.at(i).erased = true;
		}
		if(p.at(i).source == trainNum){
			p.at(i).onTrain = true;
			if(p.at(i).source == p.at(i).destination){
				p.at(i).onTrain = false;
				p.at(i).erased = true;
			}
		}
	}
}

// Input: Station object
// Returns: string
// Does: returns a string of all of the passengers that are 
//       currently waiting at a station
string MetroSim::passAtStation(Station sta){
	int passSize = static_cast<int>(p.size());
	string passStat = "";
	for(int i = 0; i < passSize; i++){
		if(sta.stationNum == p.at(i).source && p.at(i).onTrain == false
		   && p.at(i).erased == false){
			string s1 = to_string(p.at(i).id);
			string s2 = to_string(p.at(i).source);
			string s3 = to_string(p.at(i).destination);
			passStat = passStat + "[" + s1 + ", " + s2 + "->" + s3 + "]";
		}
	}
	return passStat;
}

// Input: nothing
// Returns: string
// Does: returns a string of all the passengers that are on the train
string MetroSim::printPassengers(){
	int passSize = static_cast<int>(p.size());
	string passTrain;
	for(int i = 0; i < passSize; i++){
		if(p.at(i).onTrain == true){
			string s1 = to_string(p.at(i).id);
			string s2 = to_string(p.at(i).source);
			string s3 = to_string(p.at(i).destination);
			passTrain = passTrain + "[" + s1 + ", " + s2 + "->" + s3 + "]";
		}
	}
	return passTrain;
}

// Input: int i
// Returns: string
// Does: returns a string of all the stations and the passengers at those
//       stations. indicates whether the train is at a given station
string MetroSim::printStationsHelper(int i){
	string stationList = "";
	if(i == trainNum){
		stationList = stationList + "TRAIN: " + "[" + to_string(i) + 
		"] " + s.at(i - 1).name + " {" + passAtStation(s.at(i - 1)) + "}" 
		+ "\n";
	} else{
		stationList = stationList + "       " + "[" + to_string(i ) +
		"] " + s.at(i - 1).name + " {" + passAtStation(s.at(i - 1)) + "}" 
		+ "\n";
	}
	return stationList;
}

// Input: nothing
// Returns: string
// Does: returns a string of all the stations using the station helper
//       function above
string MetroSim::printStations(){
	int stationSize = static_cast<int>(s.size());
	string stationList = "";
	for(int i = 1; i <= stationSize; i++){
		cout << printStationsHelper(i);
	}
	return stationList;
}

// Input: nothing
// Returns: nothing
// Does: prints the station map with all the passengers at the station
//       and all the passengers on the train using the functions above
void MetroSim::printMap(){
	cout << "Passengers on the train: {" << printPassengers() << "}" << endl;
	cout << printStations() << endl;
}

// Input: string
// Returns: nothing
// Does: takes a command, and executes the command. If the command is
//       invalid, a message is printed.
void MetroSim::getCommand(string command){
	int stationSize = static_cast<int>(s.size());
	if(commandsFile == ""){
		cout << "Command: ";
		getline(cin, command);
	}
	if (command == "m m"){
		advanceTrain();
		printMap();
	} else if(command == "m f"){
		endSim = true;
	} else if(command[0] == 'p'){
		stringstream ss(command);
		string a, b, c;
		ss >> a;
		ss >> b;
		ss >> c;
		if((stoi(b) <= stationSize) && (stoi(c) <= stationSize)){
			addToStation(command);
			printMap();
		} else{
			cout << "Invalid command, please try again." << endl;
		}
	} else if(command[0] == 'f'){
		stringstream ss(command);
		string a, b;
		ss >> a;
		ss >> b;
		commandsFile = b;
		readCommand();
	} else {
		cout << "Invalid command, please try again." << endl;
	}
}

// Input: nothing
// Returns: nothing
// Does: takes in commands from a file, and executes the command
//       using the function above
void MetroSim::readCommand(){
	ifstream inFile;
	string command;
	inFile.open(commandsFile);
	while(!inFile.eof()){
		getline(inFile, command);
		getCommand(command);
	}
	endSim = true;
	inFile.close();
}
