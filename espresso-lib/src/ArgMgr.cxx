////////////////////////////////////////////////////////////////////////////////
//
// ArgMgr.cxx
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
#include <ArgMgr.hxx>
#include <Args.hxx>
using namespace espresso;

#include <iostream>
/*
#include <ostream>
#include <strstream>
#include <iomanip>
#include <utility>
#include <cassert>
*/
using namespace std; 



//------------------------------------------------------------------------------
//
// Function       : ArgMgr::ArgMgr
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
ArgMgr::ArgMgr()
{
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgr::~ArgMgr
//
// Return type    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
ArgMgr::~ArgMgr()
{
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgr::OnRequestHelp
//
// Return type    : void 
//
// Argument       : const Args& args
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void ArgMgr::OnRequestHelp(const Args& args)
{
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgr::OnRequestUsage
//
// Return type    : void 
//
// Argument       : const Args& args
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void ArgMgr::OnRequestUsage(const Args& args)
{
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgr::OnRequestVersion
//
// Return type    : void 
//
// Argument       : const Args& args
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void ArgMgr::OnRequestVersion(const Args& args)
{
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgr::OnRequestInfo
//
// Return type    : void 
//
// Argument       : const Args& args
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void ArgMgr::OnRequestInfo(const Args& args)
{
}





//------------------------------------------------------------------------------
//
// Function       : ArgMgr::ParseAndProcessArgs
//
// Return type    : int 
//
// Argument       : Args& args
//
// Description    : Parses the arg list and auto handles the default args.
//
//					The function returns:
//
//					-1 to indicate a failed parse (which the concrete ArgMgr implementation should handle)
//
//					1 to indicate a successful parse and an auto handled arg
//
//					0 to indicate a succesful parse but without any auto handled args
//
// Notes          : 
//
//------------------------------------------------------------------------------
int ArgMgr::ParseAndProcessArgs(Args& args)
{
	// parse the arg list
	if (!args.Parse())
	{
		return -1;
	}


	// check for standard requests for help, usage, version and info
	if (args.IsPresent("help") || args.IsPresent('h') || args.IsPresent('?'))
	{
		this->OnRequestHelp(args);
		return 1;
	}
	else if (args.IsPresent("usage"))
	{
		this->OnRequestUsage(args);
		return 1;
	}
	else if (args.IsPresent("version"))
	{
		this->OnRequestVersion(args);
		return 1;
	}
	else if (args.IsPresent("info"))
	{
		this->OnRequestInfo(args);
		return 1;
	}
	else
	{
		// no default arg present
		return 0;
	}

}





//------------------------------------------------------------------------------
//
// Function       : ArgMgr::OnArgError
//
// Return type    : void 
//
// Argument       : const Args& args
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void ArgMgr::OnArgError(const Args& args)
{
}
