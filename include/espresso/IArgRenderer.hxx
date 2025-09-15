////////////////////////////////////////////////////////////////////////////////
//
// IArgRenderer.hxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright �1993-20250, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ESPRESSO_IARGRENDERER_HXX
#define INCLUDED_ESPRESSO_IARGRENDERER_HXX


namespace espresso
{

// forward declarations
class Args;


struct IArgRenderer
{
	virtual ~IArgRenderer() {};

	// event handlers
	virtual void onRequestHelp(const Args& args) = 0;
	virtual void onRequestUsage(const Args& args) = 0;
	virtual void onRequestVersion(const Args& args) = 0;
	virtual void onRequestInfo(const Args& args) = 0;

	// ??
	virtual void onArgError(const Args& args, const string strInvalidOption) = 0;
};



} // end-namespace




#endif // INCLUDED_ESPRESSO_IARGRENDERER_HXX
