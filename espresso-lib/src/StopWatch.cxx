////////////////////////////////////////////////////////////////////////////////
//
// StopWatch.cxx
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
#include <StopWatch.hxx>
using namespace espresso;

#include <ctime>
using namespace std;



StopWatch::StopWatch()
{
	this->Reset();
}


StopWatch::~StopWatch()
{
}


time_t StopWatch::Start()
{
	m_nStartTime = ::time(NULL);
	return m_nStartTime;
}

		
time_t StopWatch::Stop()
{
	m_nFinishTime = ::time(NULL);
	m_nTiming += (m_nFinishTime - m_nStartTime);
	return (m_nFinishTime - m_nStartTime);
}


void StopWatch::Reset()
{
	m_nStartTime = 0;
	m_nFinishTime = 0;
	m_nTiming = 0;
}


time_t StopWatch::Lap()
{
	time_t m_LapTime = ::time(NULL);
	return (m_LapTime - m_nStartTime);
}


time_t StopWatch::GetTiming()
{
	return m_nTiming;
}