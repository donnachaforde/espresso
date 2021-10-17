////////////////////////////////////////////////////////////////////////////////
//
// ArgRenderer.hxx
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

#ifndef INCLUDED_ESPRESSO_STDOUTARGRENDERER_HXX
#define INCLUDED_ESPRESSO_STDOUTARGRENDERER_HXX


#include "IArgRenderer.hxx"



namespace espresso
{


class StdoutArgRenderer : public IArgRenderer

{
public:
	StdoutArgRenderer();
	virtual ~StdoutArgRenderer();

private:
	StdoutArgRenderer(const StdoutArgRenderer& rhs);
	StdoutArgRenderer& operator=(const StdoutArgRenderer& rhs);

public:


	// default arg handlers
	virtual void onRequestHelp(const Args& args);
	
	virtual void onRequestUsage(const Args& args);
	
	virtual void onRequestVersion(const Args& args);
	
	virtual void onRequestInfo(const Args& args);
	
	virtual void onArgError(const Args& args);
};


} // end-namespace




#endif // INCLUDED_ESPRESSO_STDOUTARGRENDERER_HXX
