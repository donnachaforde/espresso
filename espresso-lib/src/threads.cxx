////////////////////////////////////////////////////////////////////////////////
//
// threads.cxx
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
#include <threads.hxx>
using namespace espresso; 


#ifdef WIN32

	#include <windows.h>
	#include <winbase.h>

#else	// pthreads

#endif



/*static*/ tid_t threads::GetCurrentThreadID()
{

	tid_t nThreadID = -1;

#ifdef WIN32

	nThreadID = ::GetCurrentThreadId();

#else	// pthreads


	nThreadID = ::pthread_self()

#endif

	return nThreadID;
}



/*static*/ void threads::Wait(long nNumMillisecs)
{

#ifdef WIN32

	::Sleep(nNumMillisecs);

#else	// pthreads


	// not yet implemented
	assert(false);

#endif


}
