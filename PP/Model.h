#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int MAXHASH = 32;

enum TransportEnum
{
	PLANE,
	TRAIN,
	SHIP
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

int getHash( Transport transport );
double getTravelTime( Transport transport );

bool readFile( ifstream& infile, vector<Transport> hasharray[] );
bool writeToFile( ofstream& outfile, vector<Transport> hasharray[] );
bool writeToFile( ofstream& outfile, vector<Transport> hasharray[], int missingType );


string convertShipToString( ShipType value );

bool compare( Transport& a, Transport& b );
void sort( vector<Transport> array[] );


