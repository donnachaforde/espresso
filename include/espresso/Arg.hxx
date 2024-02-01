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

	Arg(const string& strSwitch, const type_t ArgType, bool isRequired, const string& strDescription, bool isValueRequired, string strValueHint);
	
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

	bool isRequired() const; 

	bool isPresent() const;

	bool isValueRequired() const;
	
	bool isValueOptional() const;

	bool isValueSupplied() const;


private:	// modifiers

	void setSwitch(const string& strSwitch);

	void setArgType(const type_t ArgType);

	void setStringValue(const string& strValue); 

	void setDescription(const string& strDescription); 

	void setNumericValue(const long nValue); 
	
	void setRequired(const bool isMandatory); 

	void setPresent(const bool isPresent);

	void setValueRequired(const bool isValueRequired); 

	void setValueSupplied(bool isValueSupplied);


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
	
	// is it a required argument
	bool m_isRequired;
	
	// is the arg present? (in the arg list)
	bool m_isPresent;

	// has a value been supplied for an arg that requires a value
	bool m_isValueSupplied; 

};




std::ostream& operator<<(std::ostream& os, const Arg& arg);



} // end-namespace


#include "Arg.inl"


#endif // INCLUDED_ESPRESSO_ARG_HXX
