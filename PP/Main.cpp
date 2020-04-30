#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include "Model.h"

#define DEBUG false;

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
	ifstream infile(inputPath);
	if (!infile.is_open())
	{
		return 1;
	}

	ofstream outfile(outputPath);
	if (!outfile.is_open())
	{
		return 1;
	}

	vector<Transport> hasharray[MAXHASH];

	readFile(infile, hasharray);


	sort(hasharray);

	writeToFile(outfile, hasharray);

	//result = writeToFile(outputPath, hasharray, TRAIN);

	return 0;
}

