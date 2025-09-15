////////////////////////////////////////////////////////////////////////////////
//
// sys.hxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright �1993-20250, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_SYS_HXX
#define INCLUDED_SYS_HXX

#include <string>
using std::string; 



namespace espresso
{
	class sys
	{
	private:
		sys();

	public:

		static string getBuildVersion();

	};
}


#endif // INCLUDED_SYS_HXX
