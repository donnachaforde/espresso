////////////////////////////////////////////////////////////////////////////////
//
// Args.cxx
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
#include <Args.hxx>
#include <strings.hxx>
using namespace espresso;

#include <ostream>
#include <strstream>
#include <iomanip>
#include <utility>
#include <cassert>
using namespace std; 






//------------------------------------------------------------------------------
//
// Function       : Args::Args
//
// Return type    : 
//
// Argument       : int argc
//
// Argument       : char* argv[]
//
// Argument       : const string& strProgramName
//
// Argument       : const string& strProgramDesc
//
// Argument       : const string& strVersion
//
// Argument       : const string& strCopyrightOwner
//
// Argument       : const string& strCopyrightYear
//
// Argument       : const string& strEMailAddressForBugs
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
Args::Args(int argc, 
		   char* argv[], 
		   const string& strProgramName, 
		   const string& strProgramDesc, 
		   const string& strVersion, 
		   const string& strCopyrightOwner,
		   const string& strCopyrightYear,
		   const string& strEMailAddressForBugs)
{
	m_argc = argc; 
	m_argv = argv; 
	m_envp = NULL; 
	m_strProgramName = strProgramName; 
	m_strProgramDesc = strProgramDesc;
	m_strVersion = strVersion; 
	m_strCopyrightOwner = strCopyrightOwner;
	m_strCopyrightYear = strCopyrightYear;
	m_strEMailAddressForBugs = strEMailAddressForBugs;
	m_isTargetPresent = false; 
	m_isInitialized = false;
}


//------------------------------------------------------------------------------
//
// Function       : Args::Args
//
// Return type    : 
//
// Argument       : int argc
//
// Argument       : char* argv[]
//
// Argument       : char* envp[]
//
// Argument       : const string& strProgramName
//
// Argument       : const string& strProgramDesc
//
// Argument       : const string& strVersion
//
// Argument       : const string& strCopyrightOwner
//
// Argument       : const string& strCopyrightYear
//
// Argument       : const string& strEMailAddressForBugs
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
Args::Args(int argc, 
		   char* argv[], 
		   char* envp[], 
		   const string& strProgramName, 
		   const string& strProgramDesc, 
		   const string& strVersion, 
		   const string& strCopyrightOwner,
		   const string& strCopyrightYear,
		   const string& strEMailAddressForBugs)
{
	m_argc = argc; 
	m_argv = argv; 
	m_envp = envp; 
	m_strProgramName = strProgramName; 
	m_strProgramDesc = strProgramDesc;
	m_strVersion = strVersion; 
	m_strCopyrightOwner = strCopyrightOwner;
	m_strCopyrightYear = strCopyrightYear;
	m_strEMailAddressForBugs = strEMailAddressForBugs;
	m_isTargetPresent = false; 
	m_isInitialized = false;

}


Args::~Args()
{
}



//------------------------------------------------------------------------------
//
// Function       : Args::addDefaults
//
// Return type    : void 
//
// Description    : Adds default args to the program (i.e. help, usage, version, info)
//
// Notes          : 
//
//------------------------------------------------------------------------------
void Args::addDefaults()
{
	// specify default common args
	this->add("help",	 Arg::NOARG, false, "Display this help message (and then exit).");
	this->add("usage",	 Arg::NOARG, false, "Display usage instructions.");
	this->add("version", Arg::NOARG, false, "Display version information.");
	this->add("info", Arg::NOARG, false, "Display build information about this executable.");

	// add default aliases
	this->addAlias("help", '?');
	this->addAlias("help", 'h');
	this->addAlias("usage", 'u');
	this->addAlias("version", 'v');
	this->addAlias("info", 'i');

	// flag that we've initialized ourselves
	m_isInitialized = true; 

	return;
}



//------------------------------------------------------------------------------
//
// Function       : Args::Add
//
// Return type    : bool 
//
// Argument       : const string& strSwitch
//
// Argument       : const Arg::type_t ArgType
//
// Argument       : const string& strDescription
//
// Argument       : bool isValueRequired /*= false*/
//
// Argument       : bool isRequired /*= false*/
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::add(const string& strSwitch, const Arg::type_t ArgType, bool isRequired, const string& strDescription, bool isValueRequired /*= false*/, string strValueHint /*= ""*/)
{
	// create an arg instance
	Arg arg(strSwitch, ArgType, isRequired, strDescription, isValueRequired, strValueHint);
	
	// add it to our internal list of args
	pair<arg_list_t::iterator, bool> nRetVal = m_argList.insert(make_pair(strSwitch, arg));
	return nRetVal.second;
}



bool Args::parse(/*inout*/ string& strInvalidOption)
{
	if (this->parse())
	{
		return true; 
	}
	else
	{
		strInvalidOption = m_strInvalidArgv; 
		return false; 
	}
}



//------------------------------------------------------------------------------
//
// Function       : Args::Parse
//
// Return type    : bool 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::parse()
{
	Arg* pArg = NULL; 

	for (int i = 1; i < m_argc; i++)							// for each of the parameters passed
	{
		bool IsExpectedParam = false; 
		bool IsValueAlreadySet = false; 
		char* pch = m_argv[i];

		if (::strncmp(pch, "--", 2) == 0)
		{
			pch++;
			pch++;
			assert((pch != NULL) || (*pch != '\0')); 
			assert(isalpha(*pch));
			assert(strings::isValidString(pch));

			// check if they're specifying the switch and value together - e.g. --switch=value
			char* szValue = ::strchr(pch, '='); 
			if (szValue != NULL)
			{
				if (!strings::isValidString(szValue + 1))
				{
					// nothing after the '='
					m_strInvalidArgv = m_argv[i];
					return false; 

				}
				else
				{
					// terminate the string to isolate the switch part
					*szValue = '\0';	
					
					// move on to the value part
					szValue++;
				}
			}

			// locate the arg & 
			arg_list_t::iterator iter = m_argList.find(pch);
			if (iter != m_argList.end())
			{
				IsExpectedParam = true; 

				pArg = &(iter->second); 
				pArg->setPresent(true);

				if (szValue != NULL)
				{
					// set value
					if (pArg->getType() == Arg::INTEGER)
					{
						pArg->setNumericValue(::atoi(szValue));
					}
					else if (pArg->getType() == Arg::STRING)
					{
						pArg->setStringValue(szValue);
					}
					
					pArg->setValueSupplied(true);
					IsValueAlreadySet = true; 
				}
			}

		}
		else if ((*pch == '-') || (*pch == '/'))
		{
			pch++;
			assert((pch != NULL) || (*pch != '\0')); 

			if (::isalpha(*pch) || ::ispunct(*pch))
			{
				// deal with single switch as well as concatenated switches
				while (*pch != '\0')
				{
					// look up each char (as a string)
					char szSwitch[2] = ""; 
					szSwitch[0] = *pch;
					szSwitch[1] = '\0';
					arg_list_t::iterator iter = m_argList.find(szSwitch);

					if (iter == m_argList.end())
					{
						// check aliases
						alias_list_t::iterator alias_iter = m_aliasList.find(*pch);
						if (alias_iter != m_aliasList.end())
						{
							iter = m_argList.find(alias_iter->second);
						}
					}
					
					if (iter != m_argList.end())
					{
						IsExpectedParam = true; 

						pArg = &(iter->second); 
						pArg->setPresent(true);
					}
					else
					{
						IsExpectedParam = false; 
						break; 
					}
					
					pch++;
				}
			}
		}

		if (IsExpectedParam)
		{
			if ((pArg->isValueRequired() || pArg->isValueOptional()) && !IsValueAlreadySet)
			{
				// process possible value
				if ( ((i + 1) < m_argc) && !((*m_argv[i + 1] == '-') || (*m_argv[i + 1] == '/')) )
				{
					i++; 

					if (pArg != NULL)
					{
						if (pArg->getType() == Arg::INTEGER)
						{
							pArg->setNumericValue(::atoi(m_argv[i]));
						}
						else if (pArg->getType() == Arg::STRING)
						{
							pArg->setStringValue(m_argv[i]);
						}
						
						pArg->setValueSupplied(true);
					}
				}
				else
				{
					if (pArg->isValueRequired())
					{
						// we expected a value for this switch but didn't get it
						m_strInvalidArgv = m_argv[i];
						return false; 
					}
				}
			}
		}
		else
		{
			// this is either an unexpected switch or it could be the target param, which must be the last item on the cmd line
			if ((*m_argv[i] == '-') || (*m_argv[i] == '/') || ((i + 1) != m_argc))
			{
				m_strInvalidArgv = m_argv[i];
				return false; 
			}
			else
			{
				m_isTargetPresent = true; 
				m_strTarget = m_argv[i];
			}

		}
	}
		
	return true;
}


//------------------------------------------------------------------------------
//
// Function       : Args::isRequired
//
// Return type    : bool 
//
// Argument       : const string& strSwitch
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::isRequired(const string& strSwitch) const
{
	arg_list_t::const_iterator c_iter = m_argList.find(strSwitch);

	if (c_iter != m_argList.end())
	{
		const Arg& arg = c_iter->second;
		return (arg.isRequired());
	}
	else
	{
		return false;
	}
}


//------------------------------------------------------------------------------
//
// Function       : Args::isPresent
//
// Return type    : bool 
//
// Argument       : const string& strSwitch
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::isPresent(const string& strSwitch) const
{
	arg_list_t::const_iterator c_iter = m_argList.find(strSwitch);

	if (c_iter != m_argList.end())
	{
		const Arg& arg = c_iter->second;
		return (arg.isPresent());
	}
	else
	{
		return false;
	}
}



//------------------------------------------------------------------------------
//
// Function       : Args::isPresent
//
// Return type    : bool 
//
// Argument       : const char chAlias
//
// Description    : 2-step lookup
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::isPresent(const char chAlias) const
{
	alias_list_t::const_iterator const_iter = m_aliasList.find(chAlias);
	if (const_iter != m_aliasList.end())
	{
		return (this->isPresent(const_iter->second));
	}
	else
	{
		return false;
	}
}



//------------------------------------------------------------------------------
//
// Function       : Args::isValueSupplied
//
// Return type    : bool 
//
// Argument       : const string& strSwitch
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::isValueSupplied(const string& strSwitch) const
{
	arg_list_t::const_iterator c_iter = m_argList.find(strSwitch);

	if (c_iter != m_argList.end())
	{
		const Arg& arg = c_iter->second;
		return (arg.isValueSupplied());
	}
	else
	{
		return false;
	}
}


//------------------------------------------------------------------------------
//
// Function       : Args::isValueSupplied
//
// Return type    : bool 
//
// Argument       : const char chAlias
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::isValueSupplied(const char chAlias) const
{
	alias_list_t::const_iterator const_iter = m_aliasList.find(chAlias);
	if (const_iter != m_aliasList.end())
	{
		return (this->isValueSupplied(const_iter->second));
	}
	else
	{
		return false;
	}
}





//------------------------------------------------------------------------------
//
// Function       : Args::getType
//
// Return type    : bool 
//
// Argument       : const string& strSwitch
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
Arg::type_t Args::getType(const string& strSwitch) const
{
	arg_list_t::const_iterator c_iter = m_argList.find(strSwitch);

	if (c_iter != m_argList.end())
	{
		const Arg& arg = c_iter->second;
		return (arg.getType());
	}
	else
	{
		return Arg::NOARG;
	}
}


//------------------------------------------------------------------------------
//
// Function       : Args::GetStringValue
//
// Return type    : string 
//
// Argument       : const string& strSwitch
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getStringValue(const string& strSwitch) const
{
	string strTmp; 

	arg_list_t::const_iterator c_iter = m_argList.find(strSwitch);
	if (c_iter != m_argList.end())
	{
		const Arg& arg = c_iter->second;
		strTmp = arg.getStringValue();
	}

	return strTmp; 
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetNumericValue
//
// Return type    : long 
//
// Argument       : const string& strSwitch
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
long Args::getNumericValue(const string& strSwitch) const
{
	long nTmp = -1; 
	
	arg_list_t::const_iterator c_iter = m_argList.find(strSwitch);
	if (c_iter != m_argList.end())
	{
		const Arg& arg = c_iter->second;
		nTmp = arg.getNumericValue();
	}

	return nTmp; 
}


//------------------------------------------------------------------------------
//
// Function       : Args::AddAlias
//
// Return type    : bool 
//
// Argument       : const string& strSwitch
//
// Argument       : const char chAlias
//
// Description    : 
//
// Notes          : 
//
// TODO: Add case-sensitivity to aliases? (, bool IsCaseSensitive /*= true*/)
//
//------------------------------------------------------------------------------
bool Args::addAlias(const string& strSwitch, const char chAlias)
{
	pair<alias_list_t::iterator, bool> nRetVal = m_aliasList.insert(make_pair(chAlias, strSwitch));
	return (nRetVal.second);
}


//------------------------------------------------------------------------------
//
// Function       : Args::isTargetPresent
//
// Return type    : bool 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::isTargetPresent() const
{
	return m_isTargetPresent; 
}


//------------------------------------------------------------------------------
//
// Function       : Args::GetTarget
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getTarget() const
{
	return m_strTarget;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetInvalidOption
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getInvalidOption() const
{
	return m_strInvalidArgv;
}





////////////////////////////////////////////////////////////////////////////////
// property accessors
//
//


//------------------------------------------------------------------------------
//
// Function       : Args::GetProgramName
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getProgramName() const
{
	return m_strProgramName;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetProgramDescription
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getProgramDescription() const
{
	return m_strProgramDesc;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetVersion
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getVersion() const
{
	return m_strVersion;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetUsage
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getUsage() const
{
	//
	// exe name
	//

	string strUsage = "Usage: \n\n ";
	strUsage += this->getProgramName();
	strUsage += " ";


	//
	// add list of aliases defined by the user (we don't include generic /? /h /u /v and /i)
	//

	static const int NUM_GENERIC_ALIASES = 5;

	if ((m_isInitialized && m_aliasList.size() > NUM_GENERIC_ALIASES) || (!m_isInitialized && !m_aliasList.empty()))
	{
		strUsage += "[-";
		for (alias_list_t::const_iterator iter = m_aliasList.begin(); iter != m_aliasList.end(); ++iter)
		{
			// exclude default aliases
			if ((iter->first != '?') && (iter->first != 'h') && (iter->first != 'u') && (iter->first != 'v')&& (iter->first != 'i'))
			{
				strUsage += iter->first;
			}
		}
		strUsage += "] ";
	}

	// display each switch
	for (arg_list_t::const_iterator iter = m_argList.begin(); iter != m_argList.end(); ++iter)
	{
		const Arg* pArg = &(iter->second); 

		// exclude --help, --usage and --version switches from general usage list
		if ((pArg->getSwitch() != "help") && (pArg->getSwitch() != "usage") && (pArg->getSwitch() != "version") && (pArg->getSwitch() != "info"))
		{
			// optional switches are enclosed in solid braces
			if (!pArg->isRequired())
			{
				strUsage += "[";
			}
			
			strUsage += "--";
			strUsage += pArg->getSwitch();

			if (pArg->isValueRequired())
			{
				strUsage += "=";

				if (pArg->getValueHint().size() > 0)
				{
					strUsage += pArg->getValueHint();
				}
				else if (pArg->getType() == Arg::INTEGER || pArg->getType() == Arg::DOUBLE)
				{
					strUsage += "n";
				}
				else
				{
					strUsage += "value";
				}
			}
		
			if (!pArg->isRequired())
			{
				strUsage += "]";
			}
			
			strUsage += " ";
		}
	}

	// add this bit for those cli commands that have a target operand
	if (m_isTargetPresent)
	{
		strUsage += "<target>";
	}
	
	return strUsage;

}


//------------------------------------------------------------------------------
//
// Function       : Args::GetCopyrightNotice
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getCopyrightNotice() const
{
	string strCopyrightNotice;
	
	if (!m_strCopyrightOwner.empty() && !m_strCopyrightYear.empty())
	{
		//strCopyrightNotice = "Copyright© ";
		strCopyrightNotice = "Copyright ";
		strCopyrightNotice += m_strCopyrightYear;
		strCopyrightNotice += ", ";
		strCopyrightNotice += m_strCopyrightOwner;
		strCopyrightNotice += ". All rights reserved.";
	}

	return strCopyrightNotice;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetBugReportingInstructions
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getBugReportingInstructions() const
{
	string strBugReportingInstructions; 

	if (!m_strEMailAddressForBugs.empty())
	{
		strBugReportingInstructions += "Report bugs to ";
		strBugReportingInstructions += m_strEMailAddressForBugs;	
		strBugReportingInstructions += ".";	
	}
	return strBugReportingInstructions;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetOptionsDescriptions
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getOptionsDescriptions() const
{
	string strOptions = "Options:\n\n";
	
	// retrieve options using our own stream operators - devnote: ostrstream has quirky usage 
	ostrstream ostr;
	ostr << *this << std::ends;
	strOptions += ostr.str();
	ostr.freeze(false);

	return strOptions;
}



//------------------------------------------------------------------------------
//
// Function       : Args::GetInfo
//
// Return type    : string 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
string Args::getProgramInfo() const
{
	return m_strInfo;
}



//------------------------------------------------------------------------------
//
// Function       : Args::AddInfo
//
// Return type    : void 
//
// Argument       : const string& strInfo
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void Args::addProgramInfo(const string& strInfo)
{
	if (!m_strInfo.empty())
	{
		m_strInfo += "\n";
	}

	m_strInfo += strInfo;
}







////////////////////////////////////////////////////////////////////////////////
// container methods
//

Args::iterator Args::begin()
{
	return m_argList.begin();
}

Args::const_iterator Args::begin() const
{
	return m_argList.begin();
}

Args::iterator Args::end()
{
	return m_argList.end();
}

Args::const_iterator Args::end() const
{
	return m_argList.end();
}







////////////////////////////////////////////////////////////////////////////////
// stream operators
//

std::ostream& espresso::operator<<(std::ostream& os, const Args& args)
{
	// display switches
	for (Args::const_iterator citer = args.begin(); citer != args.end(); ++citer)
	{
		// indent switch info
		//os << "   ";

		Arg arg = citer->second;

		// find any aliases - have to manually search the list (map)
		for (Args::alias_list_t::const_iterator alias_iter = args.m_aliasList.begin(); alias_iter != args.m_aliasList.end(); ++alias_iter)
		{
			if (citer->first.compare(alias_iter->second) == 0)
			{
				os << "-" << alias_iter->first << ", ";
			}

		}
	
	
		os << arg << endl
				  << endl;
	}


//	// display switches
//	for (Args::const_iterator citer = args.begin(); citer != args.end(); ++citer)
//	{
//		os << citer->second << endl
//							<< endl;
//	}
//
//
//	// display aliases?
//	if (args.m_AliasList.size() > 0)
//	{
//		os << endl;
//
//		string strAlias;
//		for (Args::alias_list_t::const_iterator alias_iter = args.m_AliasList.begin(); alias_iter != args.m_AliasList.end(); ++alias_iter)
//		{
//			strAlias = " -";
//			strAlias += alias_iter->first;
//			strAlias += " | ";
//			strAlias += "/";
//			strAlias += alias_iter->first;
//
//			os << setiosflags(ios::left) << setw(20) << strAlias << "Same as --" << alias_iter->second << "."	<< endl;
//																												/*<< endl;*/
//		}
//	}


	return os; 
}



