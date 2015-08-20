////////////////////////////////////////////////////////////////////////////////
//
// Arg.hxx
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

	type_t GetType() const;

	string GetStringValue() const; 

	string GetDescription() const; 

	string GetSwitch() const;
	
	string GetValueHint() const;

	long GetNumericValue() const; 

	bool IsMandatory() const; 

	bool IsPresent() const;

	bool IsCaseSensitive() const; 

	bool IsValueRequired() const;
	
	bool IsValueOptional() const;

	bool IsValueSupplied() const;


private:	// modifiers

	void SetSwitch(const string& strSwitch);

	void SetArgType(const type_t ArgType);

	void SetStringValue(const string& strValue); 

	void SetDescription(const string& strDescription); 

	void SetNumericValue(const long nValue); 
	
	void SetMandatory(const bool IsMandatory); 

	void SetPresent(const bool IsPresent);

	void SetCaseSensitive(const bool IsCaseSensitive); 

	void SetValueRequired(const bool IsValueRequired); 

	void SetValueSupplied(bool IsValueSupplied);


private:	// member vars

	
	// verbose flag name
	string m_strSwitch;

	// type of arg
	type_t m_ArgType;
					
	// flag description
	string m_strDescription;

	// alphanumeric value
	string m_strValue;

	// value hint
	string m_strValueHint;

	// numeric value
	long m_nValue;
	
	// does this switch require a value
	bool m_IsValueRequired; 
	
	// is it a manadory argument
	bool m_IsMandatory;
	
	// indicates whether the flag is case sensitive or not
	bool m_IsCaseSensitive; //???
	
	// is the arg present? (in the arg list)
	bool m_IsPresent;

	bool m_IsValueSupplied; 

};




std::ostream& operator<<(std::ostream& os, const Arg& arg);



} // end-namespace


#include "Arg.inl"


#endif // INCLUDED_ESPRESSO_ARG_HXX
