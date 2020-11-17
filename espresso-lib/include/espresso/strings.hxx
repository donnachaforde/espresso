////////////////////////////////////////////////////////////////////////////////
//
// strings.hxx
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

#ifndef INCLUDED_ESPRESSO_STRINGS_H
#define INCLUDED_ESPRESSO_STRINGS_H

#include <string>
using std::string; 

namespace espresso
{

	class strings
	{
	// strings is a non-instanciating class - scoping only
	private:
		strings();


	public:

		static bool IsValidString(const char* szCandidate, unsigned long nMaxSize = 0);
	
		static bool IsValidString(string strCandidate, unsigned long nMaxSize = 0);
	};

}

#endif // INCLUDED_ESPRESSO_STRINGS_H
