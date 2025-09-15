////////////////////////////////////////////////////////////////////////////////
//
// threads.hxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright � 1993-2025, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ESPRESSO_THREADS_HXX
#define INCLUDED_ESPRESSO_THREADS_HXX

#ifndef WIN32
	#include <pthread.h>
#endif



#ifdef WIN32

	//typedef DWORD tid_t; 
	typedef int tid_t; 

#else	// pthreads

	typedef pthread_t tid_t;

#endif




namespace espresso
{

	class threads
	{
	
	private:	// non-instanciating class - scoping only
		
		// disable default ctor
		threads();


	public:	// public interface

		static tid_t getCurrentThreadID(); 

		static void wait(long nNumMillisecs);

	};

}

#endif // INCLUDED_ESPRESSO_THREADS_HXX
