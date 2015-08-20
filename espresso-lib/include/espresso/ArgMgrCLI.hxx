////////////////////////////////////////////////////////////////////////////////
//
// ArgMgrCLI.hxx
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

#ifndef INCLUDED_ESPRESSO_ARGMGRCLI_HXX
#define INCLUDED_ESPRESSO_ARGMGRCLI_HXX




#include "ArgMgr.hxx"



namespace espresso
{


class ArgMgrCLI : public ArgMgr
{
public:
	ArgMgrCLI();
	virtual ~ArgMgrCLI();

private:
	ArgMgrCLI(const ArgMgrCLI& rhs);
	ArgMgrCLI& operator=(const ArgMgrCLI& rhs);

public:

	// automatic arg parsing & default handling
	virtual int ParseAndProcessArgs(Args& args); 

	// arg handlers
	virtual void OnRequestHelp(const Args& args);
	
	virtual void OnRequestUsage(const Args& args);
	
	virtual void OnRequestVersion(const Args& args);
	
	virtual void OnRequestInfo(const Args& args);
	
	virtual void OnArgError(const Args& args);
};


} // end-namespace




#endif // INCLUDED_ESPRESSO_ARGMGRCLI_HXX
