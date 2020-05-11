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



	return sum % MAXHASH;
}

bool readFile( ifstream& infile, vector<Transport> hasharray[] )
{

	int count = 0;


	string line;
	getline( infile, line );
	count = atoi( line.c_str() );
	for ( int i = 0; i < count; i++ )
	{
		Transport* tempTransport = new Transport();


		getline( infile, line );
		tempTransport->type = atoi( line.c_str() );

		getline( infile, line );
		tempTransport->speed = atoi( line.c_str() );

		getline( infile, line );
		tempTransport->length = atoi( line.c_str() );

		if ( tempTransport->type == PLANE )
		{
			getline( infile, line );
			tempTransport->range = atoi( line.c_str() );

			getline( infile, line );
			tempTransport->capacity = atoi( line.c_str() );
		}
		else
		{
			getline( infile, line );
			tempTransport->count = atoi( line.c_str() );
		}

		int index = getHash( *tempTransport );
		hasharray[ index ].push_back( *tempTransport );
		delete tempTransport;
	}

	return true;
}

bool writeToFile( ofstream& outfile, vector<Transport> hasharray[] )
{
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
			outfile << "Distance is  " << current.length << endl;
			outfile << "Max speed is  " << current.speed << endl;
			outfile << endl;
		}
		count += (int) hasharray[ i ].size();
	}

	outfile << "There are " << count << " transports" << endl;


	return true;
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
