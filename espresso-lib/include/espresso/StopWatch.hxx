////////////////////////////////////////////////////////////////////////////////
//
// StopWatch.hxx
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

#ifndef INCLUDED_ESPRESSO_STOPWATCH_HXX
#define INCLUDED_ESPRESSO_STOPWATCH_HXX

#include <ctime>


namespace espresso
{

	class StopWatch
	{
	public:		// construction

			StopWatch();
			~StopWatch();

	public:

		// start the timer
		time_t Start();

		// stop the timer
		time_t Stop();


		time_t Lap();


		// reset the timer 
		void Reset();


		// returns the duration
		time_t GetTiming();


	private:	// member vars

		time_t m_nStartTime;
		
		time_t m_nFinishTime;

		time_t m_nTiming;
	};
}

#endif // INCLUDED_ESPRESSO_STOPWATCH_HXX
