////////////////////////////////////////////////////////////////////////////////
//
// time.cxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright © 1993-2008, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#include "stdhdr.hxx"
#include <time.hxx>
using namespace espresso; 

#include <ctime>


/*static*/ string time::AsString(time_t nTimeInSecs)
{
	// convert to readable format
	struct tm* pUTCTime = ::gmtime(&nTimeInSecs);

	// convert to a string
	char* szTime = ::asctime(pUTCTime);

	return (string)szTime;

}

