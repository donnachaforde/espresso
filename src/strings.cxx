////////////////////////////////////////////////////////////////////////////////
//
// strings.cxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright © 1993-2020, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#include "stdhdr.hxx"
#include <strings.hxx>
using namespace espresso; 



//------------------------------------------------------------------------------
//
// Function name	: IsValidString
//
// Return type		: bool 
//
// Argument         : const char* szCandidate
//
// Argument         : unsigned long nMaxSize /*= 0*/
//
// Description	    : Checks that a char*, which is meant to be a string, is likely
//					  to be a string by:
//	
//					  1. Checking it's not null
//
//					  2. It's not empty
//
//					  3. Optionally, checking to see if it's within range (in terms of size)
//
//
// Assumption       : We're working wih ANSI chars
//
//------------------------------------------------------------------------------
/*static*/ bool strings::isValidString(const char* szCandidate, unsigned long nMaxSize /*= 0*/)
{
	if ( (szCandidate == NULL) || (*szCandidate == '\0') )
	{
		return false;
	}
	else if ((nMaxSize > 0) && (::strlen(szCandidate) > nMaxSize))		
	{
		// user has specified optional param so must 
		// verify that string is within range
		return false; 
	}
	else
	{
		return true; 
	}
}


//------------------------------------------------------------------------------
//
// Function       : IsValidString
//
// Return type    : bool 
//
// Argument       : string strCandidate
//
// Argument       : unsigned long nMaxSize /*= 0*/
//
// Description    : std::string version of char* check
//
// Notes          : 
//
//------------------------------------------------------------------------------
/*static*/ bool strings::isValidString(string strCandidate, unsigned long nMaxSize /*= 0*/)
{
	if (strCandidate.length() == 0)
	{
		return false;
	}
	else if ((nMaxSize > 0) && (strCandidate.length() > nMaxSize))		
	{
		// user has specified optional param so must 
		// verify that string is within range
		return false; 
	}
	else
	{
		return true; 
	}

}
