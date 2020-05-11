#include "Model.h"

using std::cout;


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
	outputPath = argv[2];
	*/
	ifstream infile(inputPath);

	ofstream outfile(outputPath);


	HashArray* hashArray = new HashArray();

	hashArray->ReadFile(infile);
	hashArray->WriteFile(outfile);
	hashArray->MultiMethod(outfile);

	return 0;
}

