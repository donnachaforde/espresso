////////////////////////////////////////////////////////////////////////////////
//
// StopWatch.cxx
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

#include "stdhdr.hxx"
#include <StopWatch.hxx>
using namespace espresso;

#include <ctime>
using namespace std;



StopWatch::StopWatch()
{
	this->reset();
}


StopWatch::~StopWatch()
{
}


time_t StopWatch::start()
{
	m_nStartTime = ::time(NULL);
	return m_nStartTime;
}

		
time_t StopWatch::stop()
{
	m_nFinishTime = ::time(NULL);
	m_nTiming += (m_nFinishTime - m_nStartTime);
	return (m_nFinishTime - m_nStartTime);
}


void StopWatch::reset()
{
	m_nStartTime = 0;
	m_nFinishTime = 0;
	m_nTiming = 0;
}


time_t StopWatch::lap()
{
	time_t m_LapTime = ::time(NULL);
	return (m_LapTime - m_nStartTime);
}


time_t StopWatch::getTiming()
{
	return m_nTiming;
}