////////////////////////////////////////////////////////////////////////////////
//
// espresso.hxx
//
////////////////////////////////////////////////////////////////////////////////
//
// Developed by Donnacha Forde (@DonnachaForde)
//
// Copyright © 1993-2025, Donnacha Forde. All rights reserved.
//
//
// This software is provided 'as is' without warranty, expressed or implied.
// Donnacha Forde accepts no responsibility for the use or reliability of this software. 
// 
////////////////////////////////////////////////////////////////////////////////


#ifndef INCLUDED_ESPRESSO_HXX
#define INCLUDED_ESPRESSO_HXX

// VC++ one time include
#if _MSC_VER > 1000
	#pragma once
#endif 




////////////////////////////////////////////////////////////////////////////////
// 
// headers
//

// forward declaration 
namespace espresso {}

#ifndef INCLUDED_ESPRESSO_ARGS_HXX
#include <espresso/Args.hxx>
#define INCLUDED_ESPRESSO_ARGS_HXX
#endif


#ifndef INCLUDED_ESPRESSO_ARGMANAGER_HXX
#include <espresso/ArgManager.hxx>
#define INCLUDED_ESPRESSO_ARGMANAGER_HXX
#endif

#ifndef INCLUDED_ESPRESSO_ARGMANAGERFACTORY_HXX
#include <espresso/ArgManagerFactory.hxx>
#define INCLUDED_ESPRESSO_ARGMANAGERFACTORY_HXX
#endif


#ifndef INCLUDED_ESPRESSO_STDOUTARGRENDERER_HXX
#include <espresso/StdoutArgRenderer.hxx>
#define ININCLUDED_ESPRESSO_STDOUTARGRENDERER_HXX
#endif


#ifndef INCLUDED_ESPRESSO_STRINGS_HXX
#include <espresso/strings.hxx>
#define INCLUDED_ESPRESSO_STRINGS_HXX
#endif


#ifndef INCLUDED_ESPRESSO_TIME_HXX
#include <espresso/time.hxx>
#define INCLUDED_ESPRESSO_TIME_HXX
#endif




#endif // INCLUDED_ESPRESSO_HXX

