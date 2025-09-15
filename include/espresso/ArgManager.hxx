////////////////////////////////////////////////////////////////////////////////
//
// ArgMgr.hxx
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

#ifndef INCLUDED_ESPRESSO_ARGMANAGER_HXX
#define INCLUDED_ESPRESSO_ARGMANAGER_HXX




#include "IArgMgr.hxx"
#include "IArgRenderer.hxx"



namespace espresso
{


class ArgManager
{
public:

	ArgManager(IArgRenderer& argRenderer);
	~ArgManager();

	// copy ctor
	ArgManager(const ArgManager& rhs);


private:
	ArgManager& operator=(const ArgManager& rhs);

public:

	// automatic arg parsing & default handling
	virtual int parseAndProcessArgs(Args& args); 

	// arg handlers
	virtual void onRequestHelp(const Args& args);
	
	virtual void onRequestUsage(const Args& args);
	
	virtual void onRequestVersion(const Args& args);
	
	virtual void onRequestInfo(const Args& args);
	
	virtual void onArgError(const Args& args, const string strInvalidOption);

private:
	
	// our output renderer
	IArgRenderer& m_argRenderer; 

};


} // end-namespace




#endif // INCLUDED_ESPRESSO_ARGMANAGER_HXX
