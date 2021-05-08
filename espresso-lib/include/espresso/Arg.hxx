////////////////////////////////////////////////////////////////////////////////
//
// Arg.hxx
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

#ifndef INCLUDED_ESPRESSO_ARG_HXX
#define INCLUDED_ESPRESSO_ARG_HXX

#include <ostream>
#include <string>
using std::string;




namespace espresso
{



////////////////////////////////////////////////////////
class Arg
{
public:		// typedef

	enum type_t {STRING, INTEGER, DATE, DOUBLE, NOARG };


public:		// friends

	friend class Args; 

public:		// construction

	Arg(const string& strSwitch, const type_t ArgType, const string& strDescription, bool IsValueRequired, string strValueHint, bool IsMandatory, bool IsCaseSensitive);
	
	// copy ctor
	Arg(const Arg& rhs);
	
	// assignment operator 
	Arg& operator=(const Arg& rhs);
	
	~Arg();


public:		// operators

	// less than operator - required for std::map (held by Args class)
	inline bool operator<(const Arg& rhs);


public:		// accessors

	type_t getType() const;

	string getStringValue() const; 

	string getDescription() const; 

	string getSwitch() const;
	
	string getValueHint() const;

	long getNumericValue() const; 

	bool isMandatory() const; 

	bool isPresent() const;

	bool isCaseSensitive() const; 

	bool isValueRequired() const;
	
	bool isValueOptional() const;

	bool isValueSupplied() const;


private:	// modifiers

	void setSwitch(const string& strSwitch);

	void setArgType(const type_t ArgType);

	void setStringValue(const string& strValue); 

	void setDescription(const string& strDescription); 

	void setNumericValue(const long nValue); 
	
	void setMandatory(const bool IsMandatory); 

	void setPresent(const bool IsPresent);

	void setCaseSensitive(const bool IsCaseSensitive); 

	void setValueRequired(const bool IsValueRequired); 

	void setValueSupplied(bool IsValueSupplied);


private:	// member vars

	
	// verbose flag name
	string m_strSwitch;

	// type of arg
	type_t m_argType;
					
	// flag description
	string m_strDescription;

	// alphanumeric value
	string m_strValue;

	// value hint
	string m_strValueHint;

	// numeric value
	long m_nValue;
	
	// does this switch require a value
	bool m_isValueRequired; 
	
	// is it a manadory argument
	bool m_isMandatory;
	
	// indicates whether the flag is case sensitive or not
	bool m_isCaseSensitive; //???
	
	// is the arg present? (in the arg list)
	bool m_isPresent;

	bool m_isValueSupplied; 

};




std::ostream& operator<<(std::ostream& os, const Arg& arg);



} // end-namespace


#include "Arg.inl"


#endif // INCLUDED_ESPRESSO_ARG_HXX
