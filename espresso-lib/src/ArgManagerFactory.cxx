////////////////////////////////////////////////////////////////////////////////
//
// ArgManagerFactory.cxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright © 3-2020, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#include "stdhdr.hxx"
#include <ArgManagerFactory.hxx>
#include <ArgManager.hxx>
#include <StdoutArgRenderer.hxx>
using namespace espresso;


using namespace std; 



//------------------------------------------------------------------------------
//
// Function       : createInstance
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------


/*static*/ ArgManager ArgManagerFactory::createInstance()
{
	static StdoutArgRenderer stdoutArgRenderer;
	return createInstance(stdoutArgRenderer);
}


/*static*/ ArgManager ArgManagerFactory::createInstance(IArgRenderer& argRenderer)
{
	// the arg manager is a singleton
	static ArgManager argMgr(argRenderer);
	return argMgr;
}