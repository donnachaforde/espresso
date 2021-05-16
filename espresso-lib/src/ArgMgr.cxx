////////////////////////////////////////////////////////////////////////////////
//
// ArgMgr.cxx
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
#include <ArgMgr.hxx>
#include <Args.hxx>
using namespace espresso;


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
//ArgMgr::ArgMgr()
//{
//	this->m_argRenderer
//}

ArgMgr::ArgMgr(IArgRenderer& argRenderer) : m_argRenderer(argRenderer)
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
void ArgMgr::onRequestHelp(const Args& args)
{
	m_argRenderer.onRequestHelp(args);
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
void ArgMgr::onRequestUsage(const Args& args)
{
	m_argRenderer.onRequestUsage(args);
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
void ArgMgr::onRequestVersion(const Args& args)
{
	m_argRenderer.onRequestVersion(args);
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
void ArgMgr::onRequestInfo(const Args& args)
{
	m_argRenderer.onRequestInfo(args);
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
void ArgMgr::onArgError(const Args& args)
{
	m_argRenderer.onRequestInfo(args);
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
// Notes          : @todo This needs to be rewritten to (probably) just return a bool. As it stands, 
// and test such as if (!ParseAndProcessArgs()) will translate to 'false' when we return -1. 
//
//------------------------------------------------------------------------------
int ArgMgr::parseAndProcessArgs(Args& args)
{
	// parse the arg list
	if (!args.parse())
	{
		return -1;
	}


	// check for standard requests for help, usage, version and info
	if (args.isPresent("help") || args.isPresent('h') || args.isPresent('?'))
	{
		this->onRequestHelp(args);
		return 1;
	}
	else if (args.isPresent("usage"))
	{
		this->onRequestUsage(args);
		return 1;
	}
	else if (args.isPresent("version"))
	{
		this->onRequestVersion(args);
		return 1;
	}
	else if (args.isPresent("info"))
	{
		this->onRequestInfo(args);
		return 1;
	}
	else
	{
		// no default arg present
		return 0;
	}

}





