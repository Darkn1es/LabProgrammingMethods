#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::getline;
using std::string;
using std::endl;


class Transport
{
private:
	int _speed;
	int _length;
	double _cargoWeight;
public:
	virtual void ReadTransportFromFile(ifstream& in);
	virtual void WriteTransportToFile(ofstream& out);
	int GetSpeed();
	void SetSpeed(int value);

	int GetLength();
	void SetLength(int value);

	double GetCargoWeight();
	void SetCargoWeight(double value);

	double GetTravelTime();
	
};

class Plane : public Transport
{
private:
	int _range;
	int _capacity;
public:
	int GetRange();
	void SetRange(int value);

	int GetCapacity();
	void SetCapacity(int value);

	void ReadTransportFromFile(ifstream& in) override;
	void WriteTransportToFile(ofstream& out) override;
};

class Train : public Transport
{
private:
	int _count;
public:
	int GetCount();
	void SetCount(int value);
	void ReadTransportFromFile(ifstream& in) override;
	void WriteTransportToFile(ofstream& out) override;
};

class Ship : public Transport
{
public:
	enum ShipType
	{
		LINER,
		TOW,
		TANKER,
	};

	int GetDisplacement();
	void SetDisplacement(int value);

	ShipType GetShipType();
	void SetShipType(ShipType value);

	void ReadTransportFromFile(ifstream& in) override;
	void WriteTransportToFile(ofstream& out) override;

private:
	int _displacement;
	ShipType _shipType;
	string shipTypeToString(ShipType value);
};


class HashArray
{
private:
	int getHash(Transport* transport);
public:
	vector<Transport*>* Conteiner;

	const int MAXHASH = 32;
	bool ReadFile(ifstream& in);
	bool WriteFile(ofstream& out);


	HashArray();
	~HashArray();
};
