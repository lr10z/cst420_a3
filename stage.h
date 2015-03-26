//
// CST 420 - Assignment # 3
//
// Author: Leander Rodriguez
//
// File: stages.h
//
// Due date:  Sunday, August 4th by 11:59pm
//
// Declaration for a Stage class.
//


#ifndef  stage_H
#define  stage_H


#include  <iostream>
#include  <string>

using  namespace  std;


//
// Declaration
//
class  Stage
{

  friend  istream  &operator>>( istream  &in, Stage  &rhs );

  public  :

	//
	// Constructor
	//
    Stage( const float &stageMiles = 0.0 )  :  m_stageMiles(stageMiles)  {}


	//
	// Method
	//
    float  stageMiles()	const { return  m_stageMiles; }


  private  :

	//
	// Member variable
	//
    float m_stageMiles;
	
};


#endif