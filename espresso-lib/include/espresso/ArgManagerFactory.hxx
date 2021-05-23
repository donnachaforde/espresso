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

#ifndef INCLUDED_ESPRESSO_ARGMANAGERFACTORY_HXX
#define INCLUDED_ESPRESSO_ARGMANAGERFACTORY_HXX





#include "IArgRenderer.hxx"



namespace espresso
{

// forward declaration
class ArgMgr;


class ArgManagerFactory
{


private:
	ArgManagerFactory();
	virtual ~ArgManagerFactory();
	ArgManagerFactory(const ArgManagerFactory& rhs);
	ArgManagerFactory& operator=(const ArgManagerFactory& rhs);


public:
	// create a default instance of an ArgMgr (that uses a stdout renderer)
	static ArgMgr createInstance();
	static ArgMgr createInstance(IArgRenderer& argRenderer);
};


} // end-namespace




#endif // INCLUDED_ESPRESSO_ARGMANAGERFACTORY_HXX
