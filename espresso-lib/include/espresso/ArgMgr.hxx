////////////////////////////////////////////////////////////////////////////////
//
// ArgMgr.hxx
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

#ifndef INCLUDED_ESPRESSO_ARGMGR_HXX
#define INCLUDED_ESPRESSO_ARGMGR_HXX




#include "IArgMgr.hxx"



namespace espresso
{


class ArgMgr : public IArgMgr
{
public:
	ArgMgr();
	virtual ~ArgMgr();

private:
	ArgMgr(const ArgMgr& rhs);
	ArgMgr& operator=(const ArgMgr& rhs);

public:

	// automatic arg parsing & default handling
	virtual int parseAndProcessArgs(Args& args); 

	// arg handlers
	virtual void onRequestHelp(const Args& args);
	
	virtual void onRequestUsage(const Args& args);
	
	virtual void onRequestVersion(const Args& args);
	
	virtual void onRequestInfo(const Args& args);
	
	virtual void onArgError(const Args& args);
};


} // end-namespace




#endif // INCLUDED_ESPRESSO_ARGMGR_HXX
