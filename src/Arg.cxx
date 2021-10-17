////////////////////////////////////////////////////////////////////////////////
//
// Arg.cxx
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
	m_argType = ArgType;
	m_strDescription = strDescription;
	m_isValueRequired = IsValueRequired;
	m_strValueHint = strValueHint;
	m_isMandatory = IsMandatory;
	m_isCaseSensitive = IsCaseSensitive;
	m_isPresent = false;
	m_isValueSupplied = false;
	m_nValue = 0;
}


// copy ctor
Arg::Arg(const Arg& rhs)
{
	m_strSwitch			= rhs.m_strSwitch;
	m_argType			= rhs.m_argType;
	m_strDescription	= rhs.m_strDescription;
	m_strValue			= rhs.m_strValue;
	m_nValue			= rhs.m_nValue;
	m_isMandatory		= rhs.m_isMandatory;
	m_isCaseSensitive	= rhs.m_isCaseSensitive; 
	m_isPresent			= rhs.m_isPresent;
	m_isValueRequired	= rhs.m_isValueRequired;
	m_strValueHint		= rhs.m_strValueHint;
	m_isValueSupplied   = rhs.m_isValueSupplied;
}


Arg& Arg::operator=(const Arg& rhs)
{
	// check for assignment to self
	if (this != &rhs)
	{
		m_strSwitch			= rhs.m_strSwitch;
		m_argType			= rhs.m_argType;
		m_strDescription	= rhs.m_strDescription;
		m_strValue			= rhs.m_strValue;
		m_nValue			= rhs.m_nValue;
		m_isMandatory		= rhs.m_isMandatory;
		m_isCaseSensitive	= rhs.m_isCaseSensitive; 
		m_isPresent			= rhs.m_isPresent;
		m_isValueRequired	= rhs.m_isValueRequired;
		m_strValueHint		= rhs.m_strValueHint;
		m_isValueSupplied   = rhs.m_isValueSupplied;
	}

	return *this; 
}


Arg::~Arg()
{
}



string Arg::getSwitch() const
{
	return m_strSwitch; 
}


Arg::type_t Arg::getType() const
{
	return m_argType; 
}


long Arg::getNumericValue() const
{
	return m_nValue; 
}


string Arg::getStringValue() const
{
	return m_strValue; 
}


string Arg::getDescription() const
{
	return m_strDescription;
}


bool Arg::isMandatory() const
{
	return m_isMandatory; 
}


bool Arg::isPresent() const
{
	return m_isPresent;
}


bool Arg::isCaseSensitive() const
{
	return m_isCaseSensitive;
}


bool Arg::isValueRequired() const
{
	return m_isValueRequired;
}


bool Arg::isValueSupplied() const
{
	return m_isValueSupplied;
}


string Arg::getValueHint() const
{
	return m_strValueHint;
}

// a value for an arg is optional if it is not required but has a type other than none
bool Arg::isValueOptional() const
{
	return (!this->isValueRequired() && (m_argType != NOARG));
}





void Arg::setSwitch(const string& strSwitch)
{
	m_strSwitch = strSwitch;
}


void Arg::setArgType(const type_t ArgType)
{
	m_argType = ArgType; 
}


void Arg::setStringValue(const string& strValue)
{
	m_strValue = strValue;
}


void Arg::setDescription(const string& strDescription)
{
	m_strDescription = strDescription;
}


void Arg::setNumericValue(const long nValue)
{
	m_nValue = nValue;
}


void Arg::setMandatory(const bool IsMandatory)
{
	m_isMandatory = IsMandatory;
}


void Arg::setPresent(const bool IsPresent)
{
	m_isPresent = IsPresent;
}


void Arg::setCaseSensitive(const bool IsCaseSensitive)
{
	m_isCaseSensitive = IsCaseSensitive;
}


void Arg::setValueRequired(const bool IsValueRequired)
{
	m_isValueRequired = IsValueRequired;
}


void Arg::setValueSupplied(bool IsValueSupplied)
{
	m_isValueSupplied = IsValueSupplied;
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
	strSwitch += arg.getSwitch();

	if (arg.isValueRequired())
	{
		if (arg.getValueHint().size() > 0)
		{
			strSwitch += "=<";
			strSwitch += arg.getValueHint();
			strSwitch += ">";
		}
		else if (arg.getType() == Arg::INTEGER)
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

	if (arg.getDescription().size() <= SIZE_OF_TEXT)
	{
		os << setiosflags(ios::left) << setw(SIZE_OF_INDENT) << "";
		os << arg.getDescription(); 
	}
	else
	{
		//
		// format the help into indented blocks 
		//

		string strDesc = arg.getDescription(); 
		
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
