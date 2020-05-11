#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int MAXHASH = 32;

enum TransportEnum
{
	PLANE = 0,
	TRAIN = 1
};

struct Transport
{
	int type;

	int speed;
	int length;

	//Plane
	int range;
	int capacity;

	//Train
	int count;


};

int getHash( Transport transport );

bool readFile( ifstream& infile, vector<Transport> hasharray[] );
bool writeToFile( ofstream& outfile, vector<Transport> hasharray[] );

void multiMethod( vector<Transport> hasharray[], ofstream& outfile );