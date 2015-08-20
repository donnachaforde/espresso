////////////////////////////////////////////////////////////////////////////////
//
// Arg.cxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright © 1993-2008, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#include "stdhdr.hxx"
#include <Arg.hxx>
#include <strings.hxx>
using namespace espresso;

#include <ostream>
#include <strstream>
#include <iomanip>
#include <utility>
#include <cassert>
using namespace std; 


// ctor
Arg::Arg(const string& strSwitch, const type_t ArgType, const string& strDescription, bool IsValueRequired, string strValueHint, bool IsMandatory, bool IsCaseSensitive)
{
	m_strSwitch = strSwitch;
	m_ArgType = ArgType;
	m_strDescription = strDescription;
	m_IsValueRequired = IsValueRequired;
	m_strValueHint = strValueHint;
	m_IsMandatory = IsMandatory;
	m_IsCaseSensitive = IsCaseSensitive;
	m_IsPresent = false;
	m_IsValueSupplied = false;
	m_nValue = 0;
}


// copy ctor
Arg::Arg(const Arg& rhs)
{
	m_strSwitch			= rhs.m_strSwitch;
	m_ArgType			= rhs.m_ArgType;
	m_strDescription	= rhs.m_strDescription;
	m_strValue			= rhs.m_strValue;
	m_nValue			= rhs.m_nValue;
	m_IsMandatory		= rhs.m_IsMandatory;
	m_IsCaseSensitive	= rhs.m_IsCaseSensitive; 
	m_IsPresent			= rhs.m_IsPresent;
	m_IsValueRequired	= rhs.m_IsValueRequired;
	m_strValueHint		= rhs.m_strValueHint;
	m_IsValueSupplied   = rhs.m_IsValueSupplied;
}


Arg& Arg::operator=(const Arg& rhs)
{
	// check for assignment to self
	if (this != &rhs)
	{
		m_strSwitch			= rhs.m_strSwitch;
		m_ArgType			= rhs.m_ArgType;
		m_strDescription	= rhs.m_strDescription;
		m_strValue			= rhs.m_strValue;
		m_nValue			= rhs.m_nValue;
		m_IsMandatory		= rhs.m_IsMandatory;
		m_IsCaseSensitive	= rhs.m_IsCaseSensitive; 
		m_IsPresent			= rhs.m_IsPresent;
		m_IsValueRequired	= rhs.m_IsValueRequired;
		m_strValueHint		= rhs.m_strValueHint;
		m_IsValueSupplied   = rhs.m_IsValueSupplied;
	}

	return *this; 
}


Arg::~Arg()
{
}



string Arg::GetSwitch() const
{
	return m_strSwitch; 
}


Arg::type_t Arg::GetType() const
{
	return m_ArgType; 
}


long Arg::GetNumericValue() const
{
	return m_nValue; 
}


string Arg::GetStringValue() const
{
	return m_strValue; 
}


string Arg::GetDescription() const
{
	return m_strDescription;
}


bool Arg::IsMandatory() const
{
	return m_IsMandatory; 
}


bool Arg::IsPresent() const
{
	return m_IsPresent;
}


bool Arg::IsCaseSensitive() const
{
	return m_IsCaseSensitive;
}


bool Arg::IsValueRequired() const
{
	return m_IsValueRequired;
}


bool Arg::IsValueSupplied() const
{
	return m_IsValueSupplied;
}


string Arg::GetValueHint() const
{
	return m_strValueHint;
}

// a value for an arg is optional if it is not required but has a type other than none
bool Arg::IsValueOptional() const
{
	return (!this->IsValueRequired() && (m_ArgType != NOARG));
}





void Arg::SetSwitch(const string& strSwitch)
{
	m_strSwitch = strSwitch;
}


void Arg::SetArgType(const type_t ArgType)
{
	m_ArgType = ArgType; 
}


void Arg::SetStringValue(const string& strValue)
{
	m_strValue = strValue;
}


void Arg::SetDescription(const string& strDescription)
{
	m_strDescription = strDescription;
}


void Arg::SetNumericValue(const long nValue)
{
	m_nValue = nValue;
}


void Arg::SetMandatory(const bool IsMandatory)
{
	m_IsMandatory = IsMandatory;
}


void Arg::SetPresent(const bool IsPresent)
{
	m_IsPresent = IsPresent;
}


void Arg::SetCaseSensitive(const bool IsCaseSensitive)
{
	m_IsCaseSensitive = IsCaseSensitive;
}


void Arg::SetValueRequired(const bool IsValueRequired)
{
	m_IsValueRequired = IsValueRequired;
}


void Arg::SetValueSupplied(bool IsValueSupplied)
{
	m_IsValueSupplied = IsValueSupplied;
}









////////////////////////////////////////////////////////////////////////////////
// stream operators
//


std::ostream& espresso::operator<<(std::ostream& os, const Arg& arg)
{
	const int SIZE_OF_LINE = 80;
	const int SIZE_OF_INDENT = 8; 
	const int SIZE_OF_TEXT = (SIZE_OF_LINE - SIZE_OF_INDENT);


	//
	// stream out the switch (plus an indication of a value where necessary)
	//
	
	string strSwitch = "--";
	strSwitch += arg.GetSwitch();

	if (arg.IsValueRequired())
	{
		if (arg.GetValueHint().size() > 0)
		{
			strSwitch += "=<";
			strSwitch += arg.GetValueHint();
			strSwitch += ">";
		}
		else if (arg.GetType() == Arg::INTEGER)
		{
			strSwitch += "=<int>";
		}
		else
		{
			strSwitch += "=<value>";
		}
	}

//	os << setiosflags(ios::left) << setw(SIZE_OF_INDENT) << strSwitch;
	os << strSwitch	<< endl;
//	os << setiosflags(ios::right) << setw(SIZE_OF_INDENT);


	//
	// stream out the help description
	//

	if (arg.GetDescription().size() <= SIZE_OF_TEXT)
	{
		os << setiosflags(ios::left) << setw(SIZE_OF_INDENT) << "";
		os << arg.GetDescription(); 
	}
	else
	{
		//
		// format the help into indented blocks 
		//

		string strDesc = arg.GetDescription(); 
		
		string strLine; 
		string strFormattedOutput; 
		
		// find first word
		string::size_type nBegin = 0; 
		string::size_type nEnd = strDesc.find(" ");

		while (nEnd != string::npos)
		{
			// extract the word
			string strWord(strDesc, nBegin, (nEnd - nBegin));
			
			// handle paragraph formatting
			if ((strLine.size() + strWord.size()) > SIZE_OF_TEXT)
			{
				// copy & rest the line
				strFormattedOutput += strLine; 
				strLine = "";

				// handle indentation
				strFormattedOutput += "\n";
				for (int i = 0; i < SIZE_OF_INDENT; i++)
				{
					strFormattedOutput += " ";
				}

				// drop the leading space on the word - coz next line will start with this word
				strWord = string(strWord, 1, strWord.size()); 
			}

			// copy the word
			strLine += strWord; 
	
			// find next word
			nBegin = nEnd;
			nEnd = strDesc.find(" ", nBegin + 1);
		}

		
		//
		// handle last word and last line formatting
		//

		// last word
		string strWord(strDesc, nBegin, (strDesc.size() - nBegin));

		// handle paragraph formatting
		if ((strLine.size() + strWord.size()) > SIZE_OF_TEXT)
		{
			// copy & rest the line
			strFormattedOutput += strLine; 
			strLine = "";

			// handle indentation
			strFormattedOutput += "\n";
			for (int i = 0; i < SIZE_OF_INDENT; i++)
			{
				strFormattedOutput += " ";
			}

			// drop the leading space on the word - coz next line will start with this word
			strWord = string(strWord, 1, strWord.size()); 

		}
		
		strLine += strWord; 
		strFormattedOutput += strLine; 


		// write formatted help desc
		os << strFormattedOutput;
 	}

	return os;
}
