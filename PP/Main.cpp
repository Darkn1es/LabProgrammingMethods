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
	try
	{
		ifstream infile(inputPath);
		infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


		ofstream outfile(outputPath);

		vector<Transport> hasharray[MAXHASH];

		readFile(infile, hasharray);


		sort(hasharray);

		writeToFile(outfile, hasharray);

		//result = writeToFile(outputPath, hasharray, TRAIN);
	}
	catch (std::invalid_argument & c)
	{
		std::cerr << c.what();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Wrong input file";
	}
	catch (...)
	{
		std::cerr << "Exception :( ";
	}
	return 0;
}

