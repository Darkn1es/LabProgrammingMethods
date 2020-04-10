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

int getHash(Transport transport);

bool readFile(string input, vector<Transport> hasharray[]);
bool writeToFile(string output, vector<Transport> hasharray[]);

