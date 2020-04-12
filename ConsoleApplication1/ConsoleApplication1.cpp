#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include "Model.h"

#define DEBUG 1;

using namespace std;


int main(int argc, char* argv[])
{
	string inputPath = "input.txt";
	string outputPath = "output.txt";

#if !DEBUG

	if (argc != 3)
	{
		cout << "Type input and output files\n";
		return 1;
	}

	inputPath = argv[1];
	outputPath = argv[2];

#endif

	vector<Transport> hasharray[MAXHASH];
	bool result = readFile(inputPath, hasharray);
	if (!result)
	{
		cout << "Bad input file!\n";
		return 1;
	}
	//result = writeToFile(outputPath, hasharray);
	result = writeToFile(outputPath, hasharray, TRAIN);
	if (!result)
	{
		cout << "Bad output file!\n";
		return 1;
	}

	return 0;
}

