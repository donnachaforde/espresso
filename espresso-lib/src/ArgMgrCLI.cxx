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
void ArgMgrCLI::OnRequestHelp(const Args& args)
{
	cout															<< endl
		 << args.GetProgramDescription()							<< endl
																	<< endl 
		 << args.GetUsage()											<< endl
																	<< endl 
		 << args.GetOptionsDescriptions()							<< endl
																	<< endl
		 << args.GetCopyrightNotice()								<< endl
		 << args.GetBugReportingInstructions()						<< endl;

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
void ArgMgrCLI::OnRequestUsage(const Args& args)
{
	cout << args.GetUsage()											<< endl
																	<< endl 
		 << args.GetCopyrightNotice()								<< endl;

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
void ArgMgrCLI::OnRequestVersion(const Args& args)
{
	cout << args.GetProgramName() << " " << args.GetVersion()		<< endl 
		 << args.GetCopyrightNotice()								<< endl;

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
void ArgMgrCLI::OnRequestInfo(const Args& args)
{
	cout																			<< endl
		 << args.GetProgramName() << " " << args.GetVersion()						/*<< endl */
//																					<< endl
//		 << "Compiled: " << __TIME__ << " " << __DATE__								<< endl

#ifdef _DEBUG
		 << " [Debug]"															<< endl
#else
		 << " [Release]"															<< endl
#endif
																					<< endl;


	string strInfo = args.GetInfo();
	if (!strInfo.empty())
	{
		cout << strInfo																<< endl;
	}

	cout << "Built with the espresso library Version " << sys::GetBuildVersion()
		 << " - compiled at " << __TIME__ << " " << __DATE__ << "."					<< endl
																					<< endl
		 << args.GetCopyrightNotice()												<< endl
		 << args.GetBugReportingInstructions()										<< endl;

	return;
}




int ArgMgrCLI::ParseAndProcessArgs(Args& args)
{
	// use default handling of default args 
	int nRetVal = ArgMgr::ParseAndProcessArgs(args);

	// report if it didn't work
	if (nRetVal == -1)
	{
		cout << "ERROR: Invalid option: '" << args.GetInvalidOption() << "'. Use --help for option information." << endl;
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
void ArgMgrCLI::OnArgError(const Args& args)
{
	cout << args.GetUsage()											<< endl
																	<< endl 
		 << args.GetCopyrightNotice()								<< endl;

	return;
}
