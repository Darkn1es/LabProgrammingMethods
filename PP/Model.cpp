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
	else if (transport.type == SHIP)
	{
		sum += transport.displacement;
	}

	return sum % MAXHASH;
}

double getTravelTime(Transport transport)
{
	return static_cast<double>(transport.length) / static_cast<double>(transport.speed);
}

bool readFile(ifstream& infile, vector<Transport> hasharray[])
{

	int count = 0;

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

		getline(infile, line);
		tempTransport->cargoWeight = atof(line.c_str()); 

		if (tempTransport->type == PLANE)
		{
			getline(infile, line);
			tempTransport->range = atoi(line.c_str());

			getline(infile, line);
			tempTransport->capacity = atoi(line.c_str());
		}
		else if (tempTransport->type == TRAIN)
		{
			getline(infile, line);
			tempTransport->count = atoi(line.c_str());
		}
		else if (tempTransport->type == SHIP)
		{
			getline(infile, line);
			tempTransport->displacement = atoi(line.c_str());

			getline(infile, line);
			tempTransport->shipType = static_cast<ShipType>(atoi(line.c_str()));
		}

		int index = getHash(*tempTransport);
		hasharray[index].push_back(*tempTransport);
		delete tempTransport;
	}
	infile.close();
	return true;
}

bool writeToFile(ofstream& outfile, vector<Transport> hasharray[])
{
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
			else if (current.type == SHIP)
			{
				outfile << "Type of transport: SHIP\n";
				outfile << "Displacement is " << current.displacement << endl;
				outfile << "Type of ship is " << shipTypeToString(current.shipType) << endl;
			}
			outfile << "Distance is " << current.length << endl;
			outfile << "Max speed is " << current.speed << endl;
			outfile << "Cargo weight is " << current.cargoWeight << endl;

			outfile << "Travel time is " << getTravelTime(current) << endl;
			outfile << endl;
		}
		count += (int)hasharray[i].size();
	}

	outfile << "There are " << count << " transports" << endl;


	outfile.close();
	return true;
}

bool writeToFile(ofstream& outfile, vector<Transport> hasharray[], int missingType)
{
	int count = 0;

	for (int i = 0; i < MAXHASH; i++)
	{
		for (int j = 0; j < (int)hasharray[i].size(); j++)
		{
			Transport current = hasharray[i][j];
			if (current.type == missingType)
			{
				count--;
				continue;
			}
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
			else if (current.type == SHIP)
			{
				outfile << "Type of transport: SHIP\n";
				outfile << "Displacement is " << current.displacement << endl;
				outfile << "Type of ship is " << shipTypeToString(current.shipType) << endl;
			}
			outfile << "Distance is " << current.length << endl;
			outfile << "Max speed is " << current.speed << endl;
			outfile << "Cargo weight is " << current.cargoWeight << endl;

			outfile << "Travel time is " << getTravelTime(current) << endl;
			outfile << endl;
		}
		count += (int)hasharray[i].size();
	}

	outfile << "There are " << count << " transports" << endl;


	outfile.close();
	return true;
}

string shipTypeToString(ShipType value)
{
	string result = "";
	switch (value)
	{
	case LINER:
		result = "LINER";
		break;
	case TOW:
		result = "TOW";
		break;
	case TANKER:
		result = "TANKER";
		break;
	default:
		break;
	}
	return result;
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

