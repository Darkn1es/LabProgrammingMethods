#include "Model.h"
#define DEBUG 1;

using std::cout;


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

	HashArray* hashArray = new HashArray();

	hashArray->ReadFile(infile);
	hashArray->WriteFile(outfile);


	return 0;
}