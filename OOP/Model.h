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
public:
	virtual void ReadTransportFromFile(ifstream& in);
	virtual void WriteTransportToFile(ofstream& out);
	int GetSpeed();
	void SetSpeed(int value);

	int GetLength();
	void SetLength(int value);

	
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
