////////////////////////////////////////////////////////////////////////////////
//
// time.hxx
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

#ifndef INCLUDED_ESPRESSO_TIME_HXX
#define INCLUDED_ESPRESSO_TIME_HXX


#include <string>

namespace espresso
{

	class time
	{
	
	private:	// non-instanciating class - scoping only
		
		// disable default ctor
		time();


	public:	// public interface

		static string AsString(time_t nTimeInSecs); 


	};

}

#endif // INCLUDED_ESPRESSO_TIME_HXX
