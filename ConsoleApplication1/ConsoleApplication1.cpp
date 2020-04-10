#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include "Model.h"

using namespace std;


int main(int argc, char* argv[])
{
	string inputPath = "input.txt";
	string outputPath = "output.txt";
	if (argc != 3)
	{
		cout << "Type input and output files\n";
		return 1;
	}

	inputPath = argv[1];
	outputPath = argv[2];

	vector<Transport> hasharray[MAXHASH];
	bool result = readFile(inputPath, hasharray);
	if (!result)
	{
		cout << "Bad input file!\n";
		return 1;
	}
	result = writeToFile(outputPath, hasharray);
	if (!result)
	{
		cout << "Bad output file!\n";
		return 1;
	}

	return 0;
}

