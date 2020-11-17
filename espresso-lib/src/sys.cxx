////////////////////////////////////////////////////////////////////////////////
//
// sys.cxx
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
#include <sys.hxx>
using namespace espresso; 


/*static*/ string sys::GetBuildVersion()
{
	return BUILD_VERSION;
}
