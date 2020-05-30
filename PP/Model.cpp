#include "Model.h"

int getHash( Transport transport )
{

	int sum = 0;
	sum += transport.speed;
	sum += transport.length;

	if ( transport.type == PLANE )
	{
		sum += transport.range;
		sum += transport.capacity;
	}
	else if ( transport.type == TRAIN )
	{
		sum += transport.count;
	}
	else if ( transport.type == SHIP )
	{
		sum += transport.displacement;
	}

	return sum % MAXHASH;
}

double getTravelTime( Transport transport )
{
	if ( transport.speed == 0 )
	{
		return INFINITY;
	}
	return static_cast<double>( transport.length ) / static_cast<double>( transport.speed );
}

bool readFile( ifstream& infile, vector<Transport> hasharray[] )
{
	if ( !infile.is_open() )
	{
		throw std::invalid_argument( "Can not read from file!" );
	}

	int count = 0;

	string line;
	getline( infile, line );
	count = stoi( line );

	if ( count < 0 )
	{
		throw std::invalid_argument( "Count of transport can not be negative!" );
	}

	for ( int i = 0; i < count; i++ )
	{
		Transport* tempTransport = new Transport();


		getline( infile, line );
		tempTransport->type = stoi( line );

		if ( ( tempTransport->type < 0 ) || ( tempTransport->type > 2 ) )
		{
			throw std::invalid_argument( "Unknown transport type!" );
		}

		getline( infile, line );
		tempTransport->speed = stoi( line );

		if ( tempTransport->speed < 0 )
		{
			throw std::invalid_argument( "Speed can not be negative!" );
		}

		getline( infile, line );
		tempTransport->length = stoi( line );

		if ( tempTransport->length < 0 )
		{
			throw std::invalid_argument( "Length can not be negative!" );
		}

		getline( infile, line );
		tempTransport->cargoWeight = stod( line );

		if ( tempTransport->cargoWeight < 0 )
		{
			throw std::invalid_argument( "Cargo weight can not be negative!" );
		}

		if ( tempTransport->type == PLANE )
		{
			getline( infile, line );
			tempTransport->range = stoi( line );
			if ( tempTransport->range < 0 )
			{
				throw std::invalid_argument( "Range can not be negative!" );
			}

			getline( infile, line );
			tempTransport->capacity = stoi( line );
			if ( tempTransport->capacity < 0 )
			{
				throw std::invalid_argument( "Capacity can not be negative!" );
			}
		}
		else if ( tempTransport->type == TRAIN )
		{
			getline( infile, line );
			tempTransport->count = stoi( line );
			if ( tempTransport->count < 0 )
			{
				throw std::invalid_argument( "Count can not be negative!" );
			}
		}
		else if ( tempTransport->type == SHIP )
		{
			getline( infile, line );
			tempTransport->displacement = stoi( line );
			if ( tempTransport->displacement < 0 )
			{
				throw std::invalid_argument( "Displacement can not be negative!" );
			}
			getline( infile, line );
			int value = stoi( line );
			if ( ( value < 0 ) || ( value > 2 ) )
			{
				throw std::invalid_argument( "Unknown ShipType!" );
			}
			tempTransport->shipType = static_cast<ShipType>( value );
		}

		int index = getHash( *tempTransport );
		hasharray[ index ].push_back( *tempTransport );
		delete tempTransport;
	}
	return true;
}

bool writeToFile( ofstream& outfile, vector<Transport> hasharray[] )
{
	if ( !outfile.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}

	int count = 0;

	for ( int i = 0; i < MAXHASH; i++ )
	{
		for ( int j = 0; j < (int) hasharray[ i ].size(); j++ )
		{
			Transport current = hasharray[ i ][ j ];
			if ( current.type == PLANE )
			{
				outfile << "Type of transport: PLANE\n";
				outfile << "Max capacity is " << current.capacity << endl;
				outfile << "Max range is " << current.range << endl;
			}
			else if ( current.type == TRAIN )
			{
				outfile << "Type of transport: TRAIN\n";
				outfile << "Count of train car is " << current.count << endl;
			}
			else if ( current.type == SHIP )
			{
				outfile << "Type of transport: SHIP\n";
				outfile << "Displacement is " << current.displacement << endl;
				outfile << "Type of ship is " << convertShipToString( current.shipType ) << endl;
			}
			outfile << "Distance is " << current.length << endl;
			outfile << "Max speed is " << current.speed << endl;
			outfile << "Cargo weight is " << current.cargoWeight << endl;

			outfile << "Travel time is " << getTravelTime( current ) << endl;
			outfile << endl;
		}
		count += (int) hasharray[ i ].size();
	}

	outfile << "There are " << count << " transports" << endl;


	return true;
}

bool writeToFile( ofstream& outfile, vector<Transport> hasharray[], int missingType )
{
	if ( !outfile.is_open() )
	{
		throw std::invalid_argument( "Can not write to file!" );
	}

	int count = 0;

	for ( int i = 0; i < MAXHASH; i++ )
	{
		for ( int j = 0; j < (int) hasharray[ i ].size(); j++ )
		{
			Transport current = hasharray[ i ][ j ];
			if ( current.type == missingType )
			{
				count--;
				continue;
			}
			if ( current.type == PLANE )
			{
				outfile << "Type of transport: PLANE\n";
				outfile << "Max capacity is " << current.capacity << endl;
				outfile << "Max range is " << current.range << endl;
			}
			else if ( current.type == TRAIN )
			{
				outfile << "Type of transport: TRAIN\n";
				outfile << "Count of train car is " << current.count << endl;
			}
			else if ( current.type == SHIP )
			{
				outfile << "Type of transport: SHIP\n";
				outfile << "Displacement is " << current.displacement << endl;
				outfile << "Type of ship is " << convertShipToString( current.shipType ) << endl;
			}
			outfile << "Distance is " << current.length << endl;
			outfile << "Max speed is " << current.speed << endl;
			outfile << "Cargo weight is " << current.cargoWeight << endl;

			outfile << "Travel time is " << getTravelTime( current ) << endl;
			outfile << endl;
		}
		count += (int) hasharray[ i ].size();
	}

	outfile << "There are " << count << " transports" << endl;


	return true;
}

string convertShipToString( ShipType value )
{
	string result = "";
	switch ( value )
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

bool compare( Transport& a, Transport& b )
{
	return getTravelTime( a ) > getTravelTime( b );
}

void sort( vector<Transport> array[] )
{
	for ( int hashIndex = 0; hashIndex < MAXHASH; hashIndex++ )
	{
		// Bubble sort
		int size = array[ hashIndex ].size();
		for ( int i = 0; i < ( size - 1 ); i++ )
		{
			for ( int j = 0; j < ( size - i - 1 ); j++ )
			{
				if ( compare( array[ hashIndex ][ j ], array[ hashIndex ][ j + 1 ] ) )
				{
					Transport temp = array[ hashIndex ][ j ];
					array[ hashIndex ][ j ] = array[ hashIndex ][ j + 1 ];
					array[ hashIndex ][ j + 1 ] = temp;
				}
			}
		}

	}
}

void multiMethod( vector<Transport> hasharray[], ofstream& outfile )
{
	outfile << "Multimethod result" << endl;
	vector<Transport> list;
	// Join all vectors
	for ( int i = 0; i < MAXHASH; i++ )
	{
		if ( hasharray[ i ].size() == 0 )
		{
			continue;
		}
		list.insert( list.end(), hasharray[ i ].begin(), hasharray[ i ].end() );
	}

	for ( int i = 0; i < list.size() - 1; i++ )
	{
		int k1 = list[ i ].type;

		for ( int j = i + 1; j < list.size(); j++ )
		{
			int k2 = list[ j ].type;

			switch ( k1 )
			{
				case PLANE:
					switch ( k2 )
					{
						case PLANE:
							outfile << "PLANE and PLANE" << endl;
							break;
						case TRAIN:
							outfile << "PLANE and TRAIN" << endl;
							break;
						case SHIP:
							outfile << "PLANE and SHIP" << endl;
							break;
						default:
							outfile << "Unknown type" << endl;
							break;
					}
					break;
				case TRAIN:
					switch ( k2 )
					{
						case PLANE:
							outfile << "TRAIN and PLANE" << endl;
							break;
						case TRAIN:
							outfile << "TRAIN and TRAIN" << endl;
							break;
						case SHIP:
							outfile << "TRAIN and SHIP" << endl;
							break;
						default:
							outfile << "Unknown type" << endl;
							break;
					}
					break;
				case SHIP:
					switch ( k2 )
					{
						case PLANE:
							outfile << "SHIP and PLANE" << endl;
							break;
						case TRAIN:
							outfile << "SHIP and TRAIN" << endl;
							break;
						case SHIP:
							outfile << "SHIP and SHIP" << endl;
							break;
						default:
							outfile << "Unknown type" << endl;
							break;
					}
					break;
				default:
					outfile << "Unknown type" << endl;
					break;
			}
		}
	}
}

