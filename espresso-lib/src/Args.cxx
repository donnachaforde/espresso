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
	m_IsTargetPresent = false; 
	m_IsInitialized = false;
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
	m_IsTargetPresent = false; 
	m_IsInitialized = false;

}


Args::~Args()
{
}



//------------------------------------------------------------------------------
//
// Function       : Args::Initialize
//
// Return type    : void 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
void Args::Initialize()
{
	// specify default common args
	this->Add("help",	 Arg::NOARG, "Display this help message (and then exit).");
	this->Add("usage",	 Arg::NOARG, "Display usage instructions (and then exit).");
	this->Add("version", Arg::NOARG, "Display version information (and then exit).");
	this->Add("info", Arg::NOARG, "Display information about this executable (and then exit).");

	// add default aliases
	this->AddAlias("help", '?');
	this->AddAlias("help", 'h');
	this->AddAlias("usage", 'u');
	this->AddAlias("version", 'v');
	this->AddAlias("info", 'i');

	// flag that we've initialized ourselves
	m_IsInitialized = true; 

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
// Argument       : bool IsValueRequired /*= false*/
//
// Argument       : bool IsMandatory /*= false*/
//
// Argument       : bool IsCaseSensitive /*= true*/
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::Add(const string& strSwitch, const Arg::type_t ArgType, const string& strDescription, bool IsValueRequired /*= false*/, string strValueHint /*= ""*/, bool IsMandatory /*= false*/, bool IsCaseSensitive /*= true*/)
{
	// create an arg instance
	Arg arg(strSwitch, ArgType, strDescription, IsValueRequired, strValueHint, IsMandatory, IsCaseSensitive); 
	
	// add it to our internal list of args
	pair<arg_list_t::iterator, bool> nRetVal = m_ArgList.insert(make_pair(strSwitch, arg));
	return nRetVal.second;
}



bool Args::Parse(/*inout*/ string& strInvalidOption)
{
	if (this->Parse())
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
bool Args::Parse()
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
			assert(strings::IsValidString(pch));

			// check if they're specifying the switch and value together - e.g. --switch=value
			char* szValue = ::strchr(pch, '='); 
			if (szValue != NULL)
			{
				if (!strings::IsValidString(szValue + 1))
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
			arg_list_t::iterator iter = m_ArgList.find(pch);
			if (iter != m_ArgList.end())
			{
				IsExpectedParam = true; 

				pArg = &(iter->second); 
				pArg->SetPresent(true);

				if (szValue != NULL)
				{
					// set value
					if (pArg->GetType() == Arg::INTEGER)
					{
						pArg->SetNumericValue(::atoi(szValue));
					}
					else if (pArg->GetType() == Arg::STRING)
					{
						pArg->SetStringValue(szValue);
					}
					
					pArg->SetValueSupplied(true);
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
					arg_list_t::iterator iter = m_ArgList.find(szSwitch);

					if (iter == m_ArgList.end())
					{
						// check aliases
						alias_list_t::iterator alias_iter = m_AliasList.find(*pch);
						if (alias_iter != m_AliasList.end())
						{
							iter = m_ArgList.find(alias_iter->second);
						}
					}
					
					if (iter != m_ArgList.end())
					{
						IsExpectedParam = true; 

						pArg = &(iter->second); 
						pArg->SetPresent(true);
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
			if ((pArg->IsValueRequired() || pArg->IsValueOptional()) && !IsValueAlreadySet)
			{
				// process possible value
				if ( ((i + 1) < m_argc) && !((*m_argv[i + 1] == '-') || (*m_argv[i + 1] == '/')) )
				{
					i++; 

					if (pArg != NULL)
					{
						if (pArg->GetType() == Arg::INTEGER)
						{
							pArg->SetNumericValue(::atoi(m_argv[i]));
						}
						else if (pArg->GetType() == Arg::STRING)
						{
							pArg->SetStringValue(m_argv[i]);
						}
						
						pArg->SetValueSupplied(true);
					}
				}
				else
				{
					if (pArg->IsValueRequired())
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
			// this is either an unexpected switch or it could be the target param (which must be last)
			if ((*m_argv[i] == '-') || (*m_argv[i] == '/') || ((i + 1) != m_argc))
			{
				m_strInvalidArgv = m_argv[i];
				return false; 
			}
			else
			{
				m_IsTargetPresent = true; 
				m_strTarget = m_argv[i];
			}

		}
	}
		
	return true;
}



//------------------------------------------------------------------------------
//
// Function       : Args::IsPresent
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
bool Args::IsPresent(const string& strSwitch) const
{
	arg_list_t::const_iterator c_iter = m_ArgList.find(strSwitch);

	if (c_iter != m_ArgList.end())
	{
		const Arg& arg = c_iter->second;
		return (arg.IsPresent());
	}
	else
	{
		return false;
	}
}



//------------------------------------------------------------------------------
//
// Function       : Args::IsPresent
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
bool Args::IsPresent(const char chAlias) const
{
	alias_list_t::const_iterator const_iter = m_AliasList.find(chAlias);
	if (const_iter != m_AliasList.end())
	{
		return (this->IsPresent(const_iter->second));
	}
	else
	{
		return false;
	}
}



//------------------------------------------------------------------------------
//
// Function       : Args::IsValueSupplied
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
bool Args::IsValueSupplied(const string& strSwitch) const
{
	arg_list_t::const_iterator c_iter = m_ArgList.find(strSwitch);

	if (c_iter != m_ArgList.end())
	{
		const Arg& arg = c_iter->second;
		return (arg.IsValueSupplied());
	}
	else
	{
		return false;
	}
}


//------------------------------------------------------------------------------
//
// Function       : Args::IsValueSupplied
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
bool Args::IsValueSupplied(const char chAlias) const
{
	alias_list_t::const_iterator const_iter = m_AliasList.find(chAlias);
	if (const_iter != m_AliasList.end())
	{
		return (this->IsValueSupplied(const_iter->second));
	}
	else
	{
		return false;
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
string Args::GetStringValue(const string& strSwitch) const
{
	string strTmp; 

	arg_list_t::const_iterator c_iter = m_ArgList.find(strSwitch);
	if (c_iter != m_ArgList.end())
	{
		const Arg& arg = c_iter->second;
		strTmp = arg.GetStringValue();
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
long Args::GetNumericValue(const string& strSwitch) const
{
	long nTmp = -1; 
	
	arg_list_t::const_iterator c_iter = m_ArgList.find(strSwitch);
	if (c_iter != m_ArgList.end())
	{
		const Arg& arg = c_iter->second;
		nTmp = arg.GetNumericValue();
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
bool Args::AddAlias(const string& strSwitch, const char chAlias)
{
	pair<alias_list_t::iterator, bool> nRetVal = m_AliasList.insert(make_pair(chAlias, strSwitch));
	return (nRetVal.second);
}


//------------------------------------------------------------------------------
//
// Function       : Args::IsTargetPresent
//
// Return type    : bool 
//
// Description    : 
//
// Notes          : 
//
//------------------------------------------------------------------------------
bool Args::IsTargetPresent() const
{
	return m_IsTargetPresent; 
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
string Args::GetTarget() const
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
string Args::GetInvalidOption() const
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
string Args::GetProgramName() const
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
string Args::GetProgramDescription() const
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
string Args::GetVersion() const
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
string Args::GetUsage() const
{
	string strUsage = "Usage: \n\n ";
	strUsage += this->GetProgramName();

	
	strUsage += " ";

	// has the user specified any args or did we specify our default args or has the use (i.e. 4 -?, -h, -v, -u)
	if ((m_IsInitialized && m_AliasList.size() > 4) || (!m_IsInitialized && !m_AliasList.empty()))
	{
		strUsage += "[-";
		for (alias_list_t::const_iterator iter = m_AliasList.begin(); iter != m_AliasList.end(); ++iter)
		{
			// exclude '?' as an option, as well as the other default options - i.e. -h, -u and -v
			if ((iter->first != '?') && (iter->first != 'h') && (iter->first != 'u') && (iter->first != 'v')&& (iter->first != 'i'))
			{
				strUsage += iter->first;
			}
		}
		strUsage += "] ";
	}

	// display each switch
	for (arg_list_t::const_iterator iter = m_ArgList.begin(); iter != m_ArgList.end(); ++iter)
	{
		const Arg* pArg = &(iter->second); 

		// exclude --help, --usage and --version switches from general usage list
		if ((pArg->GetSwitch() != "help") && (pArg->GetSwitch() != "usage") && (pArg->GetSwitch() != "version") && (pArg->GetSwitch() != "info"))
		{
			// optional switches are enclosed in solid braces
			if (!pArg->IsMandatory())
			{
				strUsage += "[";
			}
			
			strUsage += "--";
			strUsage += pArg->GetSwitch();

			if (pArg->IsValueRequired())
			{
				strUsage += "=";

				if (pArg->GetValueHint().size() > 0)
				{
					strUsage += pArg->GetValueHint();
				}
				else if (pArg->GetType() == Arg::INTEGER || pArg->GetType() == Arg::DOUBLE)
				{
					strUsage += "n";
				}
				else
				{
					strUsage += "value";
				}
			}
		
			if (!pArg->IsMandatory())
			{
				strUsage += "]";
			}
			
			strUsage += " ";
		}
	}

	// add this bit for those cli commands that have a target operand
	if (m_IsTargetPresent)
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
string Args::GetCopyrightNotice() const
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
string Args::GetBugReportingInstructions() const
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
string Args::GetOptionsDescriptions() const
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
string Args::GetInfo() const
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
void Args::AddInfo(const string& strInfo)
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
	return m_ArgList.begin();
}

Args::const_iterator Args::begin() const
{
	return m_ArgList.begin();
}

Args::iterator Args::end()
{
	return m_ArgList.end();
}

Args::const_iterator Args::end() const
{
	return m_ArgList.end();
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
		for (Args::alias_list_t::const_iterator alias_iter = args.m_AliasList.begin(); alias_iter != args.m_AliasList.end(); ++alias_iter)
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



