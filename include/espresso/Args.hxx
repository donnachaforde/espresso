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
	void addDefaults(); 


private:	// disable copy ctor & assignment operator

	Args(const Args& rhs);
	Args& operator=(const Args& rhs);


public:

	// facilitate the ability to stream the arg list
	friend std::ostream& operator<<(std::ostream& os, const Args& args);



public:		// modifiers

	// add an arg/switch to the expected arg list
	bool add(const string& strSwitch, const Arg::type_t ArgType, bool isRequired, const string& strDescription, bool isValueRequired = false, string strValueHint = "");

	// specify an alias for a switch - i.e. a single char representation of a switch - e.g. -v or /v for --version
	bool addAlias(const string& strSwitch, const char chAlias);

	// parse the arg list
	bool parse();

	// parse the arg list but can return an erroneous option - todo: consider dropping in favour of Parse()/GetInvalidOption() usage.
	bool parse(/*inout*/ string& strInvalidOption);


	// append info about the executable
	void addProgramInfo(const string& strInfo);

public:		// property accessors

	// get the executable's name
	string getProgramName() const;
	
	// get the short desciption for this executable
	string getProgramDescription() const;

	// get the version of the executable
	string getVersion() const;

	// get the usage instructions for this executable - this is auto-generated from the list of args specified
	string getUsage() const;

	// get detailed usage descriptions for each option
	string getOptionsDescriptions() const;

	// retrieve the copyright notice for this executable - this is constructed using the copyright owner and timestamp supplied
	string getCopyrightNotice() const;

	// get the e-mail address for reporting bugs with this executable - generated msg from the e-mail address supplied
	string getBugReportingInstructions() const;

	// get any executable info (optionally added by user)
	string getProgramInfo() const;

	// is there a target arg at the end of the arg list
	bool isTargetPresent() const;

	// retrieve the target arg
	string getTarget() const; 

	// retrieve the arg/switch that caused the parsing to fail
	string getInvalidOption() const; 

	

public:		// Arg accessors - must specify the switch or alias
	
	// get arg desc
	string getDescription(const string& strSwitch) const; 

	// get the stringified version of the value for this switch
	string getStringValue(const string& strSwitch) const; 

	// get the numeric version of the value for this switch
	long getNumericValue(const string& strSwitch) const; 

	// is this a required arg
	bool isRequired(const string& strSwitch) const; 

	// is the arg present on the arg list
	bool isPresent(const string& strSwitch) const; 

	// is the arg present on the arg list, identified by this alias
	bool isPresent(const char chAlias) const; 

	// was a value supplied for this switch
	bool isValueSupplied(const string& strSwitch) const; 

	// was a value supplied for the switch with this char alias
	bool isValueSupplied(const char chAlias) const; 

	// is this arg case sensitive
	bool isCaseSensitive(const string& strSwitch) const; 

	// retrieve the arg-type for this switch
	Arg::type_t getType(const string& strSwitch) const; 
							  

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
	bool   m_isTargetPresent; 

	// flag to record whether the user choose to initialize us (and use the default switches)
	bool   m_isInitialized;
	
	// internal placeholder used to report which arg is invalid
	string m_strInvalidArgv; 
	
	// map switch to argument
	arg_list_t m_argList; 

	// alias lookup
	alias_list_t m_aliasList;
};


// friend function to enable streaming of Arg class (as arg list)
std::ostream& operator<<(std::ostream& os, const Args& args);



} // end-namespace




#endif // INCLUDED_ESPRESSO_ARGS_HXX
