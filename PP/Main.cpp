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
	/*if (argc != 3)
	{
		cout << "Type input and output files\n";
		return 1;
	}

	inputPath = argv[1];
	outputPath = argv[2];*/
	ifstream infile( inputPath );
	ofstream outfile( outputPath );

	vector<Transport> hasharray[MAXHASH];
	readFile( infile, hasharray);

	writeToFile( outfile, hasharray);
	multiMethod( hasharray, outfile );

	infile.close();
	outfile.close();

	return 0;
}

