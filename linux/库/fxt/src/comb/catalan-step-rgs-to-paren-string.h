#if !defined  HAVE_CATALAN_STEP_RGS_TO_PAREN_STRING_H__
#define       HAVE_CATALAN_STEP_RGS_TO_PAREN_STRING_H__
// This file is part of the FXT library.
// Copyright (C) 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//#include "jjassert.h"


inline void catalan_step_rgs_to_paren_string(const ulong *rgs, ulong n,  char *str)
{
    str[2*n] = '\0';
    if ( n==0 )  return;  // nothing to do

    ulong w = 0;  // write position in str[]
    ulong v = 0;  // previous value in rgs[]
    for (ulong j=0; j<n; ++j)
    {
        ulong t = rgs[j];
        while ( v < t )  { ++v;  str[w++] = ')'; }
        str[w++] = '(';
    }

    // last value implied to be n:
    while ( v < n )  { ++v;  str[w++] = ')'; }

//    jjassert( w == 2*n );
}
// -------------------------

#endif // !defined HAVE_CATALAN_STEP_RGS_TO_PAREN_STRING_H__
