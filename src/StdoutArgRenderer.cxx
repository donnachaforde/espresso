////////////////////////////////////////////////////////////////////////////////
//
// StdoutArgRenderer.cxx
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
#include <StdoutArgRenderer.hxx>
#include <Args.hxx>
using namespace espresso;

#include <iostream>
using namespace std; 



//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::StdoutArgRenderer
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
StdoutArgRenderer::StdoutArgRenderer()
{
}


//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::~StdoutArgRenderer
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
StdoutArgRenderer::~StdoutArgRenderer()
{
}



//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::OnRequestHelp
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
void StdoutArgRenderer::onRequestHelp(const Args& args)
{
	cout															<< endl
		 << args.getProgramDescription()							<< endl
																	<< endl 
		 << args.getUsage()											<< endl
																	<< endl 
		 << args.getOptionsDescriptions()							<< endl
																	<< endl
		 << args.getCopyrightNotice()								<< endl;

	return;
}



//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::OnRequestUsage
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
void StdoutArgRenderer::onRequestUsage(const Args& args)
{
	cout << args.getUsage()											<< endl
																	<< endl; 

	return;
}



//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::OnRequestVersion
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
void StdoutArgRenderer::onRequestVersion(const Args& args)
{
	cout << args.getProgramName() << " " << args.getVersion()		<< endl; 

	return;
}



//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::OnRequestInfo
//
// Return type    : void 
//
// Argument       : const Args& args
//
// Description    : 
//
// Notes          : 
//
// TODO: __TIME__ and __DATE__ relate to this library and not the binary linked 
// with it. Need to be able to print out the time of the binary.
//
//
//------------------------------------------------------------------------------
void StdoutArgRenderer::onRequestInfo(const Args& args)
{
	cout																			<< endl
		 << args.getProgramName() << " " << args.getVersion()						

#ifdef _DEBUG
		 << " [Debug]"																<< endl
#else
		 << " [Release]"															<< endl
#endif
																					<< endl;
	// show extra info if provided
	if (!args.getProgramDescription().empty())
	{
		cout << args.getProgramDescription()										<< endl
																					<< endl
																					<< endl;
	}


	cout << "Built using the espresso library, Version " << sys::getBuildVersion()
		 << " - compiled at " << __TIME__ << " " << __DATE__ << "."					<< endl
		 << "https://github.com/donnachaforde/espresso/releases"					<< endl
																					<< endl
		 << args.getBugReportingInstructions()										<< endl
																					<< endl
		 << args.getCopyrightNotice()												<< endl;

	return;
}




//------------------------------------------------------------------------------
//
// Function       : StdoutArgRenderer::OnArgError
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
void StdoutArgRenderer::onArgError(const Args& args, const string strInvalidOption)
{
	cout << "ERROR: Invalid option provided: - '" << strInvalidOption << "'" << endl 
																			 << endl;

	cout << args.getUsage()													 << endl
																			 << endl 
		 << args.getCopyrightNotice()										 << endl;

	return;
}
