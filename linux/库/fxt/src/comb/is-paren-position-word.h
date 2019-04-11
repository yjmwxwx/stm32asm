#if !defined  HAVE_IS_PAREN_POSITION_WORD_H__
#define       HAVE_IS_PAREN_POSITION_WORD_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline bool is_paren_position_word(const Type *x, ulong n)
// Return whether x[] is a valid word of parenthesis positions.
{
    if ( n==0 )  return true;  // nothing to do
    if ( x[0] != 0 )  return false;

    for (ulong j=1; j<n; ++j)
        if ( x[j]<=x[j-1] )  return false;

    ulong s=0;  // sum
    ulong j=0, i=0;
    while ( j < n )
    {
        for (  ; i<x[j]; ++i)
        {
            if ( s==0 )  return false;
            --s;
        }
        ++s;  ++i;  ++j;
    }
    for ( ; i<2*n; ++i)
    {
        if ( s==0 )  return false;
        --s;
    }
    return  (s==0);
}
// -------------------------


#endif // !defined HAVE_IS_PAREN_POSITION_WORD_H__
