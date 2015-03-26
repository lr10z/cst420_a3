//
// CST 420 - Assignment # 3
//
// Author: Leander Rodriguez
//
// File: rider.h
//
// Due date:  Sunday, August 4th by 11:59pm
//
// Declaration for a Rider class.
//


#ifndef  rider_H
#define  rider_H


#include  <string>
#include  <vector>

using  namespace  std;


//
// Declaration
//
class  Rider
{

  friend  istream  &operator>>( istream  &in, Rider  &rhs );

  public  :

	//
	// Constructor
	//
    Rider( const string  &name = "" )  :  m_name(name)  {}


	//
	// Methods
	//
    const string  &name()	 const	{ return  m_name;	 }
    const string  &country() const	{ return  m_country; }
    const string  &team()	 const	{ return  m_team;	 }

	float getStageTime( unsigned int stage ) const;


  private  :

	//
	// Member variables
	//
    string m_name;
    string m_country;
    string m_team;

	vector<float> m_times;

};


extern  bool  operator<( const Rider  &lhs, const Rider  &rhs );


#endif