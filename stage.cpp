//
// CST 420 - Assignment # 3
//
// Author: Leander Rodriguez
//
// File: stage.cpp
//
// Due date:  Sunday, August 4th by 11:59pm
//
// Definitions for the Stage class.
//



#include  "stage.h"

using  namespace  std;


//
// Stream extraction operator for Stages class.
//
istream  &operator>>( istream  &in, Stage  &rhs )
{

	//
	// Read in the distance of each stage
	//
	in  >>  rhs.m_stageMiles;


	return  in;
}