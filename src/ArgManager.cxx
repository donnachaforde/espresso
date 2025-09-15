////////////////////////////////////////////////////////////////////////////////
//
// ArgMgr.cxx
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

#include "stdhdr.hxx"
#include <ArgManager.hxx>
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

ArgManager::ArgManager(IArgRenderer& argRenderer) : m_argRenderer(argRenderer)
{
}

ArgManager::ArgManager(const ArgManager& rhs) : m_argRenderer(rhs.m_argRenderer)
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
ArgManager::~ArgManager()
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
void ArgManager::onRequestHelp(const Args& args)
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
void ArgManager::onRequestUsage(const Args& args)
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
void ArgManager::onRequestVersion(const Args& args)
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
void ArgManager::onRequestInfo(const Args& args)
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
void ArgManager::onArgError(const Args& args, const string strInvalidOption)
{
	m_argRenderer.onArgError(args, strInvalidOption);
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
//					0 to indicate a successful parse but without any auto handled args
//
// Notes          : @todo This needs to be rewritten to (probably) just return a bool. As it stands, 
// and test such as if (!ParseAndProcessArgs()) will translate to 'false' when we return -1. 
//
//------------------------------------------------------------------------------
int ArgManager::parseAndProcessArgs(Args& args)
{
	// parse the arg list
	string strInvalidOption; 
	if (!args.parse(strInvalidOption))
	{
		this->onArgError(args, strInvalidOption);
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
	else if (args.isTargetRequired() && !args.isTargetPresent())
	{
		this->onRequestUsage(args);
		return -1;
	}
	else if (!args.isRequiredArgsPresent())
	{
		this->onRequestUsage(args);
		return -1;
	}
	else
	{
		// no default arg present
		return 0;
	}

}





