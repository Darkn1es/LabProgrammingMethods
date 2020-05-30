#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include "Model.h"

#define DEBUG false;

using namespace std;


int main( int argc, char* argv[] )
{
	string inputPath = "input.txt";
	string outputPath = "output.txt";

#if !DEBUG

	if ( argc != 3 )
	{
		cout << "Type input and output files\n";
		return 1;
	}

	inputPath = argv[ 1 ];
	outputPath = argv[ 2 ];

#endif
	try
	{
		ifstream infile( inputPath );
		infile.exceptions( std::ifstream::failbit | std::ifstream::badbit );


		ofstream outfile( outputPath );

		vector<Transport> hasharray[ MAXHASH ];

		readFile( infile, hasharray );


		sort( hasharray );

		writeToFile( outfile, hasharray );

		//result = writeToFile(outputPath, hasharray, TRAIN);
		multiMethod( hasharray, outfile );

		infile.close();
		outfile.close();
	}
	catch ( invalid_argument& c )
	{
		cerr << c.what();
		return 2;
	}
	catch ( std::ifstream::failure e )
	{
		cerr << "Wrong input file";
		return 1;
	}
	catch ( ... )
	{
		cerr << "Exception :( ";
		return 3;
	}
	return 0;
}

