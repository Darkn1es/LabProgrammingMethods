#include "Model.h"

#pragma region Transport

void Transport::ReadTransportFromFile( ifstream& in )
{
	if ( !in.is_open() )
	{
		throw std::invalid_argument( "Can not read from file!" );
	}
	string line;

	getline( in, line );
	SetSpeed( stoi( line ) );

	getline( in, line );
	SetLength( stoi( line ) );

	getline( in, line );
	SetCargoWeight( stod( line ) );

}

void Transport::WriteTransportToFile( std::ofstream& out )
{
	if ( !out.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}

	out << "Distance is " << _length << endl;
	out << "Max speed is " << _speed << endl;
	out << "Cargo weight is " << _cargoWeight << endl;
	out << "Travel time is " << GetTravelTime() << endl;
	out << endl;
}

int Transport::GetSpeed()
{
	return _speed;
}

void Transport::SetSpeed( int value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Speed can not be negative!" );
	}

	_speed = value;
}

int Transport::GetLength()
{
	return _length;
}

void Transport::SetLength( int value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Length can not be negative!" );
	}

	_length = value;
}

double Transport::GetCargoWeight()
{
	return _cargoWeight;
}

void Transport::SetCargoWeight( double value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Cargo weight can not be negative!" );
	}

	_cargoWeight = value;
}

double Transport::GetTravelTime()
{
	if ( _speed == 0 )
	{
		return INFINITY;
	}

	return static_cast<double>( _length ) / static_cast<double>( _speed );
}

bool Transport::Compare( Transport* value )
{
	if ( value == nullptr )
	{
		throw std::invalid_argument( "Transport is null!" );
	}

	return this->GetTravelTime() > value->GetTravelTime();
}

void Transport::MultiMethod( Transport* other, ofstream& out )
{
	out << "Unknown transport" << endl;
}

void Transport::MMPlane( ofstream& out )
{
	out << "Unknown transport" << endl;
}

void Transport::MMTrain( ofstream& out )
{
	out << "Unknown transport" << endl;
}

void Transport::MMShip( ofstream& out )
{
	out << "Unknown transport" << endl;
}

#pragma endregion

#pragma region Plane
int Plane::GetRange()
{
	return _range;
}
void Plane::SetRange( int value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Range can not be negative!" );
	}

	_range = value;
}
int Plane::GetCapacity()
{
	return _capacity;
}

void Plane::SetCapacity( int value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Capacity can not be negative!" );
	}

	_capacity = value;
}



void Plane::ReadTransportFromFile( ifstream& in )
{
	if ( !in.is_open() )
	{
		throw std::invalid_argument( "Can not read from file!" );
	}
	Transport::ReadTransportFromFile( in );

	string line;

	getline( in, line );
	SetRange( stoi( line ) );

	getline( in, line );
	SetCapacity( stoi( line ) );
}

void Plane::WriteTransportToFile( ofstream& out )
{
	if ( !out.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}
	out << "Type of transport: PLANE\n";
	out << "Max capacity is " << _capacity << endl;
	out << "Max range is " << _range << endl;

	Transport::WriteTransportToFile( out );

}

void Plane::MultiMethod( Transport* other, ofstream& out )
{
	other->MMPlane( out );
}

void Plane::MMPlane( ofstream& out )
{
	out << "PLANE and PLANE" << endl;
}

void Plane::MMTrain( ofstream& out )
{
	out << "TRAIN and PLANE" << endl;
}

void Plane::MMShip( ofstream& out )
{
	out << "SHIP and PLANE" << endl;
}

#pragma endregion

#pragma region Train
int Train::GetCount()
{
	return _count;
}
void Train::SetCount( int value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Count can not be negative!" );
	}

	_count = value;
}
void Train::ReadTransportFromFile( ifstream& in )
{
	if ( !in.is_open() )
	{
		throw std::invalid_argument( "Can not read from file!" );
	}
	Transport::ReadTransportFromFile( in );

	string line;

	getline( in, line );
	SetCount( stoi( line ) );
}

void Train::WriteTransportToFile( ofstream& out )
{
	if ( !out.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}
	out << "Type of transport: TRAIN\n";
	out << "Count of train car is " << _count << endl;

	Transport::WriteTransportToFile( out );
}

void Train::MultiMethod( Transport* other, ofstream& out )
{
	other->MMTrain( out );
}

void Train::MMPlane( ofstream& out )
{
	out << "PLANE and TRAIN" << endl;
}

void Train::MMTrain( ofstream& out )
{
	out << "TRAIN and TRAIN" << endl;
}

void Train::MMShip( ofstream& out )
{
	out << "SHIP and TRAIN" << endl;
}

#pragma endregion

#pragma region HashArray

int HashArray::getHash( Transport* transport )
{
	if ( transport == nullptr )
	{
		throw std::invalid_argument( "Transport is null!" );
	}

	int sum = 0;
	sum += transport->GetLength();
	sum += transport->GetSpeed();
	if ( typeid( *transport ) == typeid( Plane ) )
	{
		Plane* plane = (Plane*) transport;
		sum += plane->GetCapacity();
		sum += plane->GetRange();

	}
	else if ( typeid( *transport ) == typeid( Train ) )
	{
		Train* train = (Train*) transport;
		sum += train->GetCount();
	}
	else if ( typeid( *transport ) == typeid( Ship ) )
	{
		Ship* ship = (Ship*) transport;
		sum += ship->GetDisplacement();
	}

	return sum % MAXHASH;
}

bool HashArray::ReadFile( ifstream& in )
{
	if ( !in.is_open() )
	{
		throw std::invalid_argument( "Can not read from file!" );
	}

	int count = 0;

	string line;
	getline( in, line );
	count = stoi( line );
	if ( count < 0 )
	{
		throw std::invalid_argument( "Count of transport can not be negative!" );
	}

	for ( int i = 0; i < count; i++ )
	{
		Transport* tempTrasport = nullptr;

		getline( in, line );
		int type = stoi( line );

		if ( type == 0 )
		{
			Plane* tempPlane = new Plane();
			tempPlane->ReadTransportFromFile( in );
			tempTrasport = tempPlane;
		}
		else if ( type == 1 )
		{
			Train* tempTrain = new Train();
			tempTrain->ReadTransportFromFile( in );
			tempTrasport = tempTrain;
		}
		else if ( type == 2 )
		{
			Ship* tempShip = new Ship();
			tempShip->ReadTransportFromFile( in );
			tempTrasport = tempShip;
		}
		else
		{
			throw std::invalid_argument( "Unknown transport type!" );
		}

		int hash = getHash( tempTrasport );

		Conteiner[ hash ].push_back( tempTrasport );
	}

	return true;
}

bool HashArray::WriteFile( ofstream& out )
{
	if ( !out.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}

	size_t count = 0;

	for (size_t i = 0; i < MAXHASH; i++ )
	{
		for (size_t j = 0; j <  Conteiner[ i ].size(); j++ )
		{
			Transport* current = Conteiner[ i ][ j ];
			current->WriteTransportToFile( out );
		}
		count += Conteiner[ i ].size();
	}

	out << "There are " << count << " transports" << endl;

	return false;
}

bool HashArray::WriteFile( ofstream& out, const type_info& missingType )
{
	if ( !out.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}

	size_t count = 0;

	for (size_t i = 0; i < MAXHASH; i++ )
	{
		for (size_t j = 0; j <  Conteiner[ i ].size(); j++ )
		{
			Transport* current = Conteiner[ i ][ j ];
			// Skip chosen type
			if ( missingType == typeid( *current ) )
			{
				count--;
				continue;
			}
			current->WriteTransportToFile( out );
		}
		count +=  Conteiner[ i ].size();
	}

	out << "There are " << count << " transports" << endl;

	return false;
}

void HashArray::Sort()
{
	for (size_t hashIndex = 0; hashIndex < MAXHASH; hashIndex++ )
	{
		// Bubble sort
		size_t size = Conteiner[ hashIndex ].size();
		for (size_t i = 0; i < ( size - 1 ); i++ )
		{
			for (size_t j = 0; j < ( size - i - 1 ); j++ )
			{
				if ( Conteiner[ hashIndex ][ j ]->Compare( Conteiner[ hashIndex ][ j + 1 ] ) )
				{
					Transport* temp = Conteiner[ hashIndex ][ j ];
					Conteiner[ hashIndex ][ j ] = Conteiner[ hashIndex ][ j + 1 ];
					Conteiner[ hashIndex ][ j + 1 ] = temp;
				}
			}
		}

	}
}

void HashArray::MultiMethod( ofstream& out )
{
	out << "Multimethod result" << endl;
	vector<Transport*> list;
	// Join all vectors
	for (size_t i = 0; i < MAXHASH; i++ )
	{
		if ( Conteiner[ i ].size() == 0 )
		{
			continue;
		}
		list.insert( list.end(), Conteiner[ i ].begin(), Conteiner[ i ].end() );
	}

	for (size_t i = 0; i < list.size() - 1; i++ )
	{
		for (size_t j = i + 1; j < list.size(); j++ )
		{
			list[ i ]->MultiMethod( list[ j ], out );
		}
	}
}



HashArray::HashArray()
{

}

HashArray::~HashArray()
{
	for ( size_t i = 0; i < MAXHASH; i++ )
	{
		for (size_t j = 0; j < Conteiner[ i ].size(); j++ )
		{
			delete Conteiner[ i ][ j ];
		}
	}

}

#pragma endregion

#pragma region Ship

int Ship::GetDisplacement()
{
	return _displacement;
}

void Ship::SetDisplacement( int value )
{
	if ( value < 0 )
	{
		throw std::invalid_argument( "Displacement can not be negative!" );
	}

	_displacement = value;
}

Ship::ShipType Ship::GetShipType()
{
	return _shipType;
}

void Ship::SetShipType( ShipType value )
{
	if ( ( value < 0 ) || ( value > 2 ) )
	{
		throw std::invalid_argument( "Unknown ShipType!" );
	}
	_shipType = value;
}

void Ship::ReadTransportFromFile( ifstream& in )
{
	if ( !in.is_open() )
	{
		throw std::invalid_argument( "Can not read from file!" );
	}
	Transport::ReadTransportFromFile( in );

	string line;

	getline( in, line );
	_displacement = stoi( line );

	getline( in, line );
	_shipType = static_cast<ShipType>( stoi( line ) );

}

void Ship::WriteTransportToFile( ofstream& out )
{
	if ( !out.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}
	out << "Type of transport: SHIP\n";
	out << "Displacement is " << _displacement << endl;
	out << "Type of ship is " << convertShipToString( _shipType ) << endl;

	Transport::WriteTransportToFile( out );
}

void Ship::MultiMethod( Transport* other, ofstream& out )
{
	other->MMShip( out );
}

void Ship::MMPlane( ofstream& out )
{
	out << "PLANE and SHIP" << endl;
}

void Ship::MMTrain( ofstream& out )
{
	out << "TRAIN and SHIP" << endl;
}

void Ship::MMShip( ofstream& out )
{
	out << "SHIP and SHIP" << endl;
}

string Ship::convertShipToString( ShipType value )
{
	string result = "";
	switch ( value )
	{
		case Ship::LINER:
			result = "LINER";
			break;
		case Ship::TOW:
			result = "TOW";
			break;
		case Ship::TANKER:
			result = "TANKER";
			break;
		default:
			break;
	}
	return result;
}

#pragma endregion


