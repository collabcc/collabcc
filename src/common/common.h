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

// Use Boost.Predef
#include <boost/predef.h>

#include "basic.h"
#include "macros.h"

#include "assertion.h"


#endif // _COLLABCC_COMMON_COMMON_H_INCLUDED_
