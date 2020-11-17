////////////////////////////////////////////////////////////////////////////////
//
// Args.hxx
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

#ifndef INCLUDED_ESPRESSO_ARGS_HXX
#define INCLUDED_ESPRESSO_ARGS_HXX

#include <ostream>
#include <list>
#include <map>
#include <string>
using std::list; 
using std::map; 
using std::string;


#include "Arg.hxx"



namespace espresso
{

class Args
{
public:		// construction

	Args(int argc, 
		 char* argv[], 
		 const string& strProgramName, 
		 const string& strProgramDesc, 
		 const string& strVersion, 
		 const string& strCopyrightOwner = "", 
		 const string& strCopyrightYear = "", 
		 const string& strEMailAddressForBugs = "");
	
	// same as above except it also takes the environment ptr - envp (i.e. list of env vars)
	Args(int argc, 
		 char* argv[], 
		 char* envp[], 
		 const string& strProgramName, 
		 const string& strProgramDesc, 
		 const string& strVersion, 
		 const string& strCopyrightOwner = "", 
		 const string& strCopyrightYear = "", 
		 const string& strEMailAddressForBugs = "");
	
	~Args();

	// set up default args - i.e. --version, --help and --usage; don't invoke if not required
	void Initialize(); 


private:	// disable copy ctor & assignment operator

	Args(const Args& rhs);
	Args& operator=(const Args& rhs);


public:

	// facilitate the ability to stream the arg list
	friend std::ostream& operator<<(std::ostream& os, const Args& args);



public:		// modifiers

	// add an arg/switch to the expected arg list
	bool Add(const string& strSwitch, const Arg::type_t ArgType, const string& strDescription, bool IsValueRequired = false, string strValueHint = "", bool IsMandatory = false, bool IsCaseSensitive = true);

	// specify an alias for a switch - i.e. a single char representation of a switch - e.g. -v or /v for --version
	bool AddAlias(const string& strSwitch, const char chAlias);

	// parse the arg list
	bool Parse();

	// parse the arg list but can return an erroneous option - todo: consider dropping in favour of Parse()/GetInvalidOption() usage.
	bool Parse(/*inout*/ string& strInvalidOption);


	// append info about the executable
	void AddInfo(const string& strInfo);

public:		// property accessors

	// get the executable's name
	string GetProgramName() const;
	
	// get the short desciption for this executable
	string GetProgramDescription() const;

	// get the version of the executable
	string GetVersion() const;

	// get the usage instructions for this executable - this is auto-generated from the list of args specified
	string GetUsage() const;

	// get detailed usage descriptions for each option
	string GetOptionsDescriptions() const;

	// retrieve the copyright notice for this executable - this is constructed using the copyright owner and timestamp supplied
	string GetCopyrightNotice() const;

	// get the e-mail address for reporting bugs with this executable - generated msg from the e-mail address supplied
	string GetBugReportingInstructions() const;

	// get any executable info (optionally added by user)
	string GetInfo() const;

	// is there a target arg at the end of the arg list
	bool IsTargetPresent() const;

	// retrieve the target arg
	string GetTarget() const; 

	// retrieve the arg/switch that caused the parsing to fail
	string GetInvalidOption() const; 

	

public:		// Arg accessors - must specify the switch or alias
	
	// get arg desc
	string GetDescription(const string& strSwitch) const; 

	// get the stringified version of the value for this switch
	string GetStringValue(const string& strSwitch) const; 

	// get the numeric version of the value for this switch
	long GetNumericValue(const string& strSwitch) const; 

	// is this a required arg
	bool IsMandatory(const string& strSwitch) const; 

	// is the arg present on the arg list
	bool IsPresent(const string& strSwitch) const; 

	// is the arg present on the arg list, identified by this alias
	bool IsPresent(const char chAlias) const; 

	// was a value supplied for this switch
	bool IsValueSupplied(const string& strSwitch) const; 

	// was a value supplied for the switch with this char alias
	bool IsValueSupplied(const char chAlias) const; 

	// is this arg case sensitive
	bool IsCaseSensitive(const string& strSwitch) const; 

	// retrieve the arg-type for this switch
	Arg::type_t GetType(const string& strSwitch) const; 
							  

private:		// internal typedefs - shorthand definitions

	typedef string argkey; 

	typedef map<argkey, Arg> arg_list_t; 

	typedef map<char, argkey> alias_list_t;

	typedef arg_list_t::iterator iterator;
	
	typedef arg_list_t::const_iterator const_iterator;


private:	// internal accessors
	
	iterator begin();
	
	const_iterator begin() const;
	
	iterator end();
	
	const_iterator end() const;


private:	// member vars

	// corresponds to argc 
	int m_argc; 

	// corresponds to argv
	char** m_argv; 

	// corresponds to envp
	char** m_envp; 

	// name of the executing binary
	string m_strProgramName; 

	// short desc of executing binary
	string m_strProgramDesc;

	// binary version
	string m_strVersion;

	// copyright owner - used when writing to stdout
	string m_strCopyrightOwner;

	// copyright year or range - used when writing to stdout (e.g. 2007 or 2005-2007)
	string m_strCopyrightYear;

	// e-mail address for reporting bugs with the binary
	string m_strEMailAddressForBugs;

	// the target argument - will be the last arg on the list
	string m_strTarget; 

	// executable info
	string m_strInfo; 

	// flag to indicate whether the target arg is present on the arg list
	bool   m_IsTargetPresent; 

	// flag to record whether the user choose to initialize us (and use the default switches)
	bool   m_IsInitialized;
	
	// internal placeholder used to report which arg is invalid
	string m_strInvalidArgv; 
	
	// map switch to argument
	arg_list_t m_ArgList; 

	// alias lookup
	alias_list_t m_AliasList;
};


// friend function to enable streaming of Arg class (as arg list)
std::ostream& operator<<(std::ostream& os, const Args& args);



} // end-namespace




#endif // INCLUDED_ESPRESSO_ARGS_HXX
