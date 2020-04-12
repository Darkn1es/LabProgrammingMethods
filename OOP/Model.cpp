#include "Model.h"

#pragma region Transport

void Transport::ReadTransportFromFile(ifstream& in)
{
	string line;

	getline(in, line);
	_speed = atoi(line.c_str());

	getline(in, line);
	_length = atoi(line.c_str());
}

void Transport::WriteTransportToFile(ofstream& out)
{
	out << "Distance is  " << _length << endl;
	out << "Max speed is  " << _speed << endl;
	out << "Travel time is " << GetTravelTime() << endl;
	out << endl;
}

int Transport::GetSpeed()
{
	return _speed;
}

void Transport::SetSpeed(int value)
{
	_speed = value;
}

int Transport::GetLength()
{
	return _length;
}

void Transport::SetLength(int value)
{
	_length = value;
}

double Transport::GetTravelTime()
{
	return static_cast<double>(_length) / static_cast<double>(_speed);
}

bool Transport::Compare(Transport* value)
{
	return this->GetTravelTime() > value->GetTravelTime();
}

#pragma endregion

#pragma region Plane
int Plane::GetRange()
{
	return _range;
}
void Plane::SetRange(int value)
{
	_range = value;
}
int Plane::GetCapacity()
{
	return _capacity;
}

void Plane::SetCapacity(int value)
{
	_capacity = value;
}



void Plane::ReadTransportFromFile(ifstream& in)
{
	Transport::ReadTransportFromFile(in);

	string line;

	getline(in, line);
	_range = atoi(line.c_str());

	getline(in, line);
	_capacity = atoi(line.c_str());
}

void Plane::WriteTransportToFile(ofstream& out)
{
	out << "Type of transport: PLANE\n";
	out << "Max capacity is " << _capacity << endl;
	out << "Max range is " << _range << endl;

	Transport::WriteTransportToFile(out);

}

#pragma endregion

#pragma region Train
int Train::GetCount()
{
	return _count;
}
void Train::SetCount(int value)
{
	_count = value;
}
void Train::ReadTransportFromFile(ifstream& in)
{
	Transport::ReadTransportFromFile(in);

	string line;

	getline(in, line);
	_count = atoi(line.c_str());
}

void Train::WriteTransportToFile(ofstream& out)
{
	out << "Type of transport: TRAIN\n";
	out << "Count of train car is " << _count << endl;

	Transport::WriteTransportToFile(out);
}

#pragma endregion

#pragma region HashArray

int HashArray::getHash(Transport* transport)
{
	int sum = 0;
	sum += transport->GetLength();
	sum += transport->GetSpeed();
	if (typeid(*transport) == typeid(Plane))
	{
		Plane* plane = (Plane*)transport;
		sum += plane->GetCapacity();
		sum += plane->GetRange();

	}
	else if (typeid(*transport) == typeid(Train))
	{
		Train* train = (Train*)transport;
		sum += train->GetCount();
	}

	return sum % MAXHASH;
}

bool HashArray::ReadFile(ifstream& in)
{
	int count = 0;

	string line;
	getline(in, line);
	count = atoi(line.c_str());

	for (int i = 0; i < count; i++)
	{
		Transport* tempTrasport = nullptr;

		getline(in, line);
		int type = atoi(line.c_str());

		if (type == 0)
		{
			Plane* tempPlane = new Plane();
			tempPlane->ReadTransportFromFile(in);
			tempTrasport = tempPlane;
		}
		else if (type == 1)
		{
			Train* tempTrain = new Train();
			tempTrain->ReadTransportFromFile(in);
			tempTrasport = tempTrain;
		}
		else
		{
			tempTrasport = new Transport();
			tempTrasport->ReadTransportFromFile(in);
		}

		int hash = getHash(tempTrasport);

		Conteiner[hash].push_back(tempTrasport);
	}

	return true;
}

bool HashArray::WriteFile(ofstream& out)
{
	int count = 0;

	for (int i = 0; i < MAXHASH; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			Transport* current = Conteiner[i][j];
			current->WriteTransportToFile(out);
		}
		count += (int)Conteiner[i].size();
	}

	out << "There are " << count << " transports" << endl;

	return false;
}

void HashArray::Sort()
{
	for (int hashIndex = 0; hashIndex < MAXHASH; hashIndex++)
	{
		// Bubble sort
		int size = Conteiner[hashIndex].size();
		for (int i = 0; i < (size - 1); i++) 
		{
			for (int j = 0; j < (size - i - 1); j++) 
			{
				if (Conteiner[hashIndex][j]->Compare(Conteiner[hashIndex][j + 1])) 
				{
					Transport* temp = Conteiner[hashIndex][j];
					Conteiner[hashIndex][j] = Conteiner[hashIndex][j + 1];
					Conteiner[hashIndex][j + 1] = temp;
				}
			}
		}
		
	}
}


HashArray::HashArray()
{
	Conteiner = new vector<Transport*>[MAXHASH];

}

HashArray::~HashArray()
{
	for (int i = 0; i < MAXHASH; i++)
	{
		for (int j = 0; j < (int)Conteiner[i].size(); j++)
		{
			delete Conteiner[i][j];
		}
	}
	delete Conteiner;
	
}

#pragma endregion


