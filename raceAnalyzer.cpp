//
// CST 420 - Assignment # 3
//
// Author: Leander Rodriguez
//
// File: raceAnalyzer.cpp
//
// Due date:  Sunday, August 4th by 11:59pm
//
//


#include  <fstream>
#include  <algorithm>
#include  <functional>
#include  <iterator>
#include  <numeric>
#include  "raceAnalyzer.h"



//
// Functions local to this file
//
namespace
{

  //
  // Returns a name for a Rider object.
  //
  string  riderToName( const Rider &rider )
  {
    return  rider.name();
  }


  //
  // Returns a team for a Rider object.
  //
  string  riderToTeam( const Rider &rider )
  {
    return  rider.team();
  }


  //
  // Returns a country for a Rider object.
  //
  string  riderToCountry( const Rider &rider )
  {
    return  rider.country();
  }


  //
  // Returns a stage time for a Rider object.
  //
  float riderToStage( const Rider &rider, unsigned int stage )
  {
    return  rider.getStageTime( stage );
  }


  //
  // Returns a stage distance for a Rider object.
  //
  float  stageToDistance( const Stage &stage )
  {
	  return stage.stageMiles();
  }
  
 
  //
  // Predicate function to return the stage of a certain rider.
  //
  struct  stageMatch  :  public  binary_function<Rider, unsigned , float>
  {
    float  operator()( const Rider &rider, unsigned stage )  const
    {
		return riderToStage( rider, stage );
    }
  };
  
  


  //
  // Predicate function to determine if a rider is of a certain team.
  //
  struct  teamMatch  :  public  binary_function<Rider, string, bool>
  {
    bool  operator()( const Rider &rider, const string &team )  const
    {
      return  riderToTeam( rider )  ==  team;
    }
  };



  //
  // Predicate function to determine if a rider is of a certain country.
  //
   struct  countryMatch  :  public  binary_function<Rider, string, bool>
  {
    bool  operator()( const Rider &rider, const string &country )  const
    {
		return  riderToCountry( rider )  ==  country;
    }
  };



  //
  // Predicate function to only return the rider's stage time and name
  //
  struct RiderToPair : public binary_function<Rider, unsigned, RaceAnalyzer::PairResults>
  {

	  RaceAnalyzer::PairResults operator()( const Rider &rider, unsigned stage ) const
	  {
		  RaceAnalyzer::PairResults result;

		  result.first = int(rider.getStageTime( stage ));
		  result.second = rider.name();

		  return result;
	  }

  };
  
  
}





//
// Constructor. Read in data from files
//
RaceAnalyzer::RaceAnalyzer( const string  &stageFilename, const string &riderFileName )
{

	//
	// Used to iterate through each line of a file's data
	//
	typedef  istream_iterator<Rider>  RiderInIter;
	typedef  istream_iterator<Stage>  StageInIter;


	//
	// Open stages.txt file and check for successful open
	//
	ifstream  iStageFile( stageFilename );

	if( ! iStageFile )
	{
		cout  <<  "Error opening file: "  <<  stageFilename  <<  endl;

		throw  fileOpenFailure_;
	}


	//
	// Open riders.txt file and check for successful open
	//
	ifstream  iRiderFile( riderFileName );

	if( ! iRiderFile )
	{
		cout  <<  "Error opening file: "  <<  riderFileName  <<  endl;

		throw  fileOpenFailure_;
	}


	//
	// Populate Rider class container with data from file
	//
	copy( RiderInIter(iRiderFile), RiderInIter(), inserter( m_riders, m_riders.end() ) );


	//
	// Populate Stage class container with data from file
	//
	copy( StageInIter(iStageFile), StageInIter(), inserter( m_stageDistances, m_stageDistances.end() ) );


	//
	// Close files
	//
	iStageFile.close();
	iRiderFile.close();

}



//
// Returns the team name for a specified rider.
//
string  RaceAnalyzer::getTeam( const  string  &riderName )  const
{
	return riderToTeam( riderName );
}



//
// Returns the country name for a specified rider.
//
string  RaceAnalyzer::getCountry( const string  &riderName )  const 
{
	return riderToCountry( riderName );
}



//
// Returns the names of all the riders in the race.
//
RaceAnalyzer::StrSet  RaceAnalyzer::riders()  const
{
	StrSet  result;

	transform(  m_riders.begin(),
				m_riders.end(),
				inserter( result, result.end() ),
				riderToName );

	return  result;
}



//
// Returns the names of all the teams in the race.
//
RaceAnalyzer::StrSet  RaceAnalyzer::teams()  const
{
	StrSet  result;

	transform(  m_riders.begin(),
				m_riders.end(),
				inserter( result, result.end() ),
				riderToTeam );

	return  result;
}



//
// Returns the names of all the countries represented
// in the race.
//
RaceAnalyzer::StrSet  RaceAnalyzer::countries()  const
{
	StrSet  result;

	transform(  m_riders.begin(),
				m_riders.end(),
				inserter( result, result.end() ),
				riderToCountry );

	return  result;
}



//
// Returns riders' stage/race times based on the
// criteria specified by the parameters.
//
RaceAnalyzer::Results  RaceAnalyzer::riderResults( unsigned stage, const string &team, const string &country ) const
{


	//
	// Copy of Rider class data is created
	//
	typedef list<Rider>	RiderList;

	RiderList riders( m_riders.begin(), m_riders.end() ); 

		
	//
	// Eliminate riders that are not part of the team specified
	//
	if( team.length() )
	{

		RiderList::iterator  new_end  =  remove_if( riders.begin(), 
												    riders.end(), 
													not1( bind2nd(teamMatch(), team) ) );

		riders.erase(new_end, riders.end());

	}
	

	
	//
	// Eliminate all riders that are not from the country specified
	//
	if( country.length() )
	{

		RiderList::iterator  new_end  =  remove_if( riders.begin(), 
												 riders.end(), 
												 not1( bind2nd(countryMatch(), country) ) );

		riders.erase(new_end, riders.end());

	}
	



	//
	// Remaining riders that fit criteria are stored
	//
	Results  remainingResults;

	
	transform( riders.begin(),
			   riders.end(),
			   inserter( remainingResults, remainingResults.end() ),
			   bind2nd( RiderToPair(), stage) );
			   

	remainingResults.sort();


	//
	// Only the remaining riders' names and stage times are returned
	//
	return remainingResults;
	
}



//
// Returns stage/race time for the specified team/stage. A
// team time for a stage is sum of the numRiders fastest
// times for the team.
//
Seconds  RaceAnalyzer::teamTime( const string  &teamName, unsigned stage, unsigned numRiders ) const
{

	//
	// Copy of Rider class data is created
	//
	typedef list<Rider>	RiderList;

	RiderList riders( m_riders.begin(), m_riders.end() ); 



	//
	// Eliminate riders that are not part of the team specified
	//
	if( teamName.length() )
	{

		RiderList::iterator  new_end  =  remove_if( riders.begin(), 
													riders.end(), 
													not1( bind2nd(teamMatch(), teamName) ) );

		riders.erase(new_end, riders.end());

	}



	//
	// Stage times of remaining riders are stored
	//
	list<Seconds> riderTimes;


	transform(  riders.begin(),
				riders.end(),
				inserter( riderTimes, riderTimes.end() ),
				bind2nd( stageMatch(), stage ) );
				

	//
	// Stage times get sorted; fastest to slowest
	//
	riderTimes.sort();



	//
	// Times of fastest numRiders are kept, other riders' times
	// are removed
	// 
	list<Seconds>::iterator new_end = riderTimes.begin();

	advance( new_end, numRiders );
	
	riderTimes.erase(new_end, riderTimes.end());



	if( stage == 0 )
	{
		list<int> fastestTeam( riderTimes.begin(), riderTimes.end() );

		fastestTeam.sort();
	
		int sumTimes = accumulate( fastestTeam.begin(), fastestTeam.end(), 0 );

		return sumTimes;
	}



	//
	// Accumulated fastest times are returned
	//
	return accumulate( riderTimes.begin(), riderTimes.end(), 0 );

}

 


//
// Converts the time for a stage/race into miles-per-hour.
//
RaceAnalyzer::MPH  RaceAnalyzer::calcMPH( Seconds  seconds, unsigned  stage )  const
{
	
	//
	// Converts seconds to hours
	//
	double hours = seconds / 3600.0;

	
	//
	// Returns the MPH of the entire race
	//
	double totalMiles = 0.0;


	if( stage == 0 )
	{

		vector<float> distances;

		transform( m_stageDistances.begin(),
				   m_stageDistances.end(),
				   inserter( distances, distances.end() ),
				   stageToDistance );


		totalMiles = accumulate( distances.begin(), distances.end(), 0.0 );


		return totalMiles / hours;

	}



	//
	// Finds the MPH for a specific stage of the race
	//
	MPH mph = m_stageDistances[ stage - 1 ].stageMiles() / hours;



	return mph;

}
