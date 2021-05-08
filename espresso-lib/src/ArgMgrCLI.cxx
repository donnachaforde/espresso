////////////////////////////////////////////////////////////////////////////////
//
// ArgMgrCLI.cxx
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
#include <ArgMgrCLI.hxx>
#include <Args.hxx>
using namespace espresso;

#include <iostream>
/*
#include <ostream>
#include <strstream>
#include <iomanip>
#include <utility>
#include <cassert>
*/
using namespace std; 



//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::ArgMgrCLI
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
ArgMgrCLI::ArgMgrCLI()
{
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::~ArgMgrCLI
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
ArgMgrCLI::~ArgMgrCLI()
{
}



//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::OnRequestHelp
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
void ArgMgrCLI::onRequestHelp(const Args& args)
{
	cout															<< endl
		 << args.getProgramDescription()							<< endl
																	<< endl 
		 << args.getUsage()											<< endl
																	<< endl 
		 << args.getOptionsDescriptions()							<< endl
																	<< endl
		 << args.getCopyrightNotice()								<< endl
		 << args.getBugReportingInstructions()						<< endl;

	return;
}



//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::OnRequestUsage
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
void ArgMgrCLI::onRequestUsage(const Args& args)
{
	cout << args.getUsage()											<< endl
																	<< endl 
		 << args.getCopyrightNotice()								<< endl;

	return;
}



//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::OnRequestVersion
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
void ArgMgrCLI::onRequestVersion(const Args& args)
{
	cout << args.getProgramName() << " " << args.getVersion()		<< endl 
		 << args.getCopyrightNotice()								<< endl;

	return;
}



//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::OnRequestInfo
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
void ArgMgrCLI::onRequestInfo(const Args& args)
{
	cout																			<< endl
		 << args.getProgramName() << " " << args.getVersion()						/*<< endl */
//																					<< endl
//		 << "Compiled: " << __TIME__ << " " << __DATE__								<< endl

#ifdef _DEBUG
		 << " [Debug]"															<< endl
#else
		 << " [Release]"															<< endl
#endif
																					<< endl;


	string strInfo = args.getProgramInfo();
	if (!strInfo.empty())
	{
		cout << strInfo																<< endl;
	}

	cout << "Built with the espresso library Version " << sys::getBuildVersion()
		 << " - compiled at " << __TIME__ << " " << __DATE__ << "."					<< endl
																					<< endl
		 << args.getCopyrightNotice()												<< endl
		 << args.getBugReportingInstructions()										<< endl;

	return;
}




int ArgMgrCLI::parseAndProcessArgs(Args& args)
{
	// use default handling of default args 
	int nRetVal = ArgMgr::parseAndProcessArgs(args);

	// report if it didn't work
	if (nRetVal == -1)
	{
		cout << "ERROR: Invalid option: '" << args.getInvalidOption() << "'. Use --help for option information." << endl;
	}

	return nRetVal;
}


//------------------------------------------------------------------------------
//
// Function       : ArgMgrCLI::OnArgError
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
void ArgMgrCLI::onArgError(const Args& args)
{
	cout << args.getUsage()											<< endl
																	<< endl 
		 << args.getCopyrightNotice()								<< endl;

	return;
}
