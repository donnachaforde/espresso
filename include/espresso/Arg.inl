////////////////////////////////////////////////////////////////////////////////
//
// Arg.inl
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (donnacha.forde@simply-components.com)           
//
// Copyright © 1993-2020, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_ESPRESSO_ARGS_INL
#define INCLUDED_ESPRESSO_ARGS_INL



namespace espresso
{

	inline bool Arg::operator<(const Arg& rhs)
	{
		return (m_strSwitch < rhs.m_strSwitch);
	}

} // end-namespace



#endif // INCLUDED_ESPRESSO_ARGS_INL
