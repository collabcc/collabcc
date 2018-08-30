#ifndef _COLLABCC_COMMON_COMMON_H_INCLUDED_
#define _COLLABCC_COMMON_COMMON_H_INCLUDED_

//
// Sanity check: Exactly one of BUILD_COLLABCC, BUILD_COLLABCCD, BUILD_COLLABCCCTL,
// BUILD_UNITTEST shall be defined true-like
//
#if !BUILD_COLLABCC && !BUILD_COLLABCCD && !BUILD_COLLABCCCTL && !BUILD_UNITTEST
#error "BUG: None of the following is defined true-like: BUILD_COLLABCC, BUILD_COLLABCCD, BUILD_COLLABCCCTL, BUILD_UNITTEST"
#elif (!!BUILD_COLLABCC + !!BUILD_COLLABCCD + !!BUILD_COLLABCCCTL + !!BUILD_UNITTEST > 1)
#error "BUG: More than one of the following is defined true-like: BUILD_COLLABCC, BUILD_COLLABCCD, BUILD_COLLABCCCTL, BUILD_UNITTEST"
#endif


#include <generated/config.h>

// Disable warning:
// "The POSIX name for this item is deprecated.
// Instead, use the ISO C and C++ conformant name: _xxx. See online help for details"
// Don't put it after Boost.Predef - it's too late.
#define _CRT_NONSTDC_NO_WARNINGS 1

// Disable warning:
// "This function or variable may be unsafe. Consider using xxx_s instead.
// To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details"
// Don't put it after Boost.Predef - it's too late.
#define _CRT_SECURE_NO_WARNINGS 1


// Use Boost.Predef
#define BOOST_DATE_TIME_NO_LIB
#include <boost/predef.h>

// Use windows headers if we are building on Windows
#if BOOST_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ntsecapi.h>  // for RtlGenRandom
#include <io.h>
#endif


#include "basic.h"
#include "macros.h"

#include "assertion.h"


#endif // _COLLABCC_COMMON_COMMON_H_INCLUDED_
