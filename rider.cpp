//
// CST 420 - Assignment # 3
//
// Author: Leander Rodriguez
//
// File: rider.cpp
//
// Due date:  Sunday, August 4th by 11:59pm
//
// Definitions for the Rider class.
//


#include  <fstream>
#include  <sstream>
#include  <iterator>
#include  <numeric>
#include  "rider.h"

using  namespace  std;


//
// Equality operator. Riders are sorted based on their name.
//
bool  operator<( const Rider  &lhs, const Rider &rhs )
{
  return  lhs.name() < rhs.name();
}



//
// Stream extraction operator for Riders class.
//
istream  &operator>>( istream  &in, Rider  &rhs )
{

	//
	// Read in the Riders class's name, country, and team
	//
	in  >>  rhs.m_name  >>  rhs.m_country  >>  rhs.m_team;


    //
	// Read in the Rider class's stage times in seconds
	//
	string lineFromFile;
  
	getline( in, lineFromFile );


	//
	// Associate the line from the file with a stream
	//
	istringstream  inFrom( lineFromFile );

	
	//
	// Populate the Rider class's stage time container
	//
	rhs.m_times.clear();

  	copy(istream_iterator<float>(inFrom), istream_iterator<float>(), back_inserter( rhs.m_times ));  


	return  in;

}



//
// Returns a rider's stage time
//
float Rider::getStageTime( unsigned int stage ) const
{
	
	if( stage == 0 )
	{
		return float( accumulate( m_times.begin(), m_times.end(), 0.0 ) );
	}


	return m_times.at( stage-1 );
}
