////////////////////////////////////////////////////////////////////////////////
//
// IArgMgr.hxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright � 1993-2020, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ESPRESSO_IARGMGR_HXX
#define INCLUDED_ESPRESSO_IARGMGR_HXX


namespace espresso
{

// forward declarations
class Args;


struct IArgMgr
{
	virtual ~IArgMgr() {};

	// automatic arg parsing & default handling
	virtual int parseAndProcessArgs(Args& args) = 0; 

	// event handlers
	virtual void onRequestHelp(const Args& args) = 0;
	virtual void onRequestUsage(const Args& args) = 0;
	virtual void onRequestVersion(const Args& args) = 0;
	virtual void onRequestInfo(const Args& args) = 0;

	// ??
	virtual void onArgError(const Args& args) = 0;
};



} // end-namespace




#endif // INCLUDED_ESPRESSO_IARGMGR_HXX
