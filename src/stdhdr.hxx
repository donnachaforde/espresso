////////////////////////////////////////////////////////////////////////////////
//
// stdhdr.hxx
//
////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_STDHDR_HXX
#define INCLUDED_STDHDR_HXX

// VC++ one time include
#if _MSC_VER > 1000
	#pragma once
#endif 

////////////////////////////////////////////////////////////////////////////////
//
// Useful message macros
//

#ifdef ESPRESSO_ENABLE_TRACING

	// macro trick to get around using quotes
	#define _QUOTE(x)	#x
	#define QUOTE(x)	_QUOTE(x)

	// build messages
	#define NOTE(desc)			message("note : " desc)
	#define MSG(desc)			message(__FILE__ "(" QUOTE(__LINE__) ") : " desc)

	#define TODO(desc)			message(__FILE__ "(" QUOTE(__LINE__) ") : todo : " desc)
	#define DEVNOTE(desc)		message(__FILE__ "(" QUOTE(__LINE__) ") : Note : " desc)
	#define DEVWARNING(desc)	message(__FILE__ "(" QUOTE(__LINE__) ") : DevWarning : " desc)


#else

	#define NOTE(desc)			message("")
	#define MSG(desc)			message("")
	#define TODO(desc)			message("")
	#define DEVNOTE(desc)		message("")
	#define DEVWARNING(desc)	message("")

#endif


////////////////////////////////////////////////////////////////////////////////
// 
// build settings
//

// ensure we don't confuse debug and release builds
#ifdef NDEBUG
	#pragma message("note : Performing Release Build.")
	#undef DEBUG
	#undef _DEBUG
#else
	#ifdef WIN32
		#pragma message("note : Performing Debug Build.")
	#endif
	#ifndef DEBUG
		#define DEBUG
	#endif
	#ifndef _DEBUG
		#define _DEBUG
	#endif
#endif



////////////////////////////////////////////////////////////////////////////////
// 
// warning levels 
//

#ifdef WIN32

	#ifndef ESPRESSO_ENABLE_WARNINGS

		#if defined(DEBUG) || defined(_DEBUG)
			#pragma message("note : Disabling some common warnings generated by using the STL.")
		#endif
		
		#pragma warning( disable : 4786 ) // Ignore string too long caused by STL declarations
		#pragma warning( disable : 4503 ) // Ignore 'decorated name length exceeded and truncated' (template names can be very long)

	#else

		#pragma warning( default : 4786 ) // Ignore string too long caused by STL declarations
		#pragma warning( default : 4503 ) // Ignore 'decorated name length exceeded and truncated' (template names can be very long)
	
	#endif // ENABLE_WARNINGS

#endif // WIN32



////////////////////////////////////////////////////////////////////////////////
// 
// version info

namespace espresso
{
	static const char* BUILD_VERSION = "0.1.0.4 (Beta)";
}


////////////////////////////////////////////////////////////////////////////////
// 
// common external includes
//
#include <utility>
#include <cassert>
using namespace std; 




////////////////////////////////////////////////////////////////////////////////
// 
// common internal excludes
//
#include <espresso/sys.hxx>
using namespace espresso;




#endif // INCLUDED_STDHDR_HXX