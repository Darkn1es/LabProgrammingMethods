#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int MAXHASH = 32;

enum TransportEnum
{
	PLANE = 0,
	TRAIN = 1,
	SHIP = 2
};

enum ShipType
{
	LINER,
	TOW,
	TANKER,
};

struct Transport
{
	int type;

	int speed;
	int length;
	double cargoWeight;

	//Plane
	int range;
	int capacity;

	//Train
	int count;

	//Ship
	int displacement;
	ShipType shipType;

};

int getHash(Transport transport);
double getTravelTime(Transport transport);

bool readFile(string input, vector<Transport> hasharray[]);
bool writeToFile(string output, vector<Transport> hasharray[]);

string shipTypeToString(ShipType value);

