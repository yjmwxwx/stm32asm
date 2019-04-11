#if !defined  HAVE_IS_PAREN_STRING_H__
#define       HAVE_IS_PAREN_STRING_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"
#include "fxttypes.h"


template <typename Type>
inline bool is_paren_string(const Type *str, ulong n2)
// Return whether parenthesis string is valid.
// Works for any pair of symbols.
{
    if ( n2==0 )  return true;  // nothing to do
    if ( n2 & 1UL )  return false;  // must have even length

    const Type c1 = str[0];     // opening paren
    const Type c0 = str[n2-1];  // closing paren
    long s = 0;  // running sum
    for (ulong js=0; js<n2; ++js)
    {
        const Type c = str[js];
        if ( c == c1 )  // opening paren
        {
            ++s;
        }
        else  // closing paren
        {
            if ( c != c0 )  return false;  // invalid symbol
            --s;
            if ( s < 0 )  return false;
        }
    }

    // GCC 4.9.1 with -Wstrict-overflow=5 issues the warning
    // "assuming signed overflow does not occur when
    //  simplifying conditional to constant"
    // This is a false positive.
    return (s==0);
}
// -------------------------


inline bool is_paren_string(const bitarray &B)
{
    ulong n2 = B.size();
    if ( n2==0 )  return true;  // nothing to do
    if ( n2 & 1UL )  return false;  // must have even length
    long s = 0;  // running sum
    for (ulong js=0; js<n2; ++js)
    {
        const bool c = B.test(js);
        if ( c )  // opening paren
        {
            ++s;
        }
        else  // closing paren
        {
            --s;
            if ( s < 0 )  return false;
        }
    }
    return (s==0);
}
// -------------------------

#endif  // !defined HAVE_IS_PAREN_STRING_H__
