#include "Model.h"

int getHash(Transport transport)
{
	int sum = 0;
	sum += transport.speed;
	sum += transport.length;

	if (transport.type == PLANE)
	{
		sum += transport.range;
		sum += transport.capacity;
	}
	else if (transport.type == TRAIN)
	{
		sum += transport.count;
	}


	return sum % MAXHASH;
}

double getTravelTime(Transport transport)
{
	return static_cast<double>(transport.length) / static_cast<double>(transport.speed);
}

bool readFile(string input, vector<Transport> hasharray[])
{

	int count = 0;
	// передать поток сразу
	ifstream infile(input);
	if (!infile.is_open())
	{
		return false;
	}

	string line;
	getline(infile, line);
	count = atoi(line.c_str());
	for (int i = 0; i < count; i++)
	{
		Transport* tempTransport = new Transport();


		getline(infile, line);
		tempTransport->type = atoi(line.c_str());

		getline(infile, line);
		tempTransport->speed = atoi(line.c_str());

		getline(infile, line);
		tempTransport->length = atoi(line.c_str());

		if (tempTransport->type == PLANE)
		{
			getline(infile, line);
			tempTransport->range = atoi(line.c_str());

			getline(infile, line);
			tempTransport->capacity = atoi(line.c_str());
		}
		else
		{
			getline(infile, line);
			tempTransport->count = atoi(line.c_str());
		}

		int index = getHash(*tempTransport);
		hasharray[index].push_back(*tempTransport);
		delete tempTransport;
	}
	infile.close();
}

bool writeToFile(string output, vector<Transport> hasharray[])
{
	ofstream outfile(output);
	if (!outfile.is_open())
	{
		return false;
	}
	int count = 0;

	for (int i = 0; i < MAXHASH; i++)
	{
		for (int j = 0; j < (int)hasharray[i].size(); j++)
		{
			Transport current = hasharray[i][j];
			if (current.type == PLANE)
			{
				outfile << "Type of transport: PLANE\n";
				outfile << "Max capacity is " << current.capacity << endl;
				outfile << "Max range is " << current.range << endl;
			}
			else if (current.type == TRAIN)
			{
				outfile << "Type of transport: TRAIN\n";
				outfile << "Count of train car is " << current.count << endl;
			}
			outfile << "Distance is  " << current.length << endl;
			outfile << "Max speed is  " << current.speed << endl;
			outfile << "Travel time is " << getTravelTime(current) << endl;
			outfile << endl;
		}
		count += (int)hasharray[i].size();
	}

	outfile << "There are " << count << " transports" << endl;


	outfile.close();
	return true;
}

bool compare(Transport& a, Transport& b)
{
	return getTravelTime(a) > getTravelTime(b);
}

void sort(vector<Transport> array[])
{
	for (int hashIndex = 0; hashIndex < MAXHASH; hashIndex++)
	{
		// Bubble sort
		int size = array[hashIndex].size();
		for (int i = 0; i < (size - 1); i++)
		{
			for (int j = 0; j < (size - i - 1); j++)
			{
				if (compare(array[hashIndex][j], array[hashIndex][j + 1]))
				{
					Transport temp = array[hashIndex][j];
					array[hashIndex][j] = array[hashIndex][j + 1];
					array[hashIndex][j + 1] = temp;
				}
			}
		}

	}
}
