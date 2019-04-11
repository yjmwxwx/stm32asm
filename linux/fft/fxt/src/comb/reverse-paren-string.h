#if !defined  HAVE_REVERSE_PAREN_STRING_H__
#define       HAVE_REVERSE_PAREN_STRING_H__
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
inline void reverse_paren_string(const Type *str, ulong n2, Type *st2)
// Reverse string and swap '(' and ')'
// Works for any pair of symbols.
// Works in-place if str==0.
{
    if ( n2==0 )  return;  // nothing to do

    const Type c1 = str[0];     // e.g., '('
    const Type c0 = str[n2-1];  // e.g., ')'
    for (ulong j=0, k=n2-1; j<k; ++j, --k)
    {
        Type sj = str[j], sk = str[k];
        st2[j] = ( sk == c1 ? c0 : c1 );
        st2[k] = ( sj == c1 ? c0 : c1 );
    }
}
// -------------------------


template <typename Type>
inline void reverse_paren_string(Type *str, ulong n2)
// Reverse string and swap '(' and ')'
// Works for any pair of symbols.
// Works in-place if str==0.
{
    if ( n2==0 )  return;  // nothing to do

    const Type c1 = str[0];     // e.g., '('
    const Type c0 = str[n2-1];  // e.g., ')'
    for (ulong j=0, k=n2-1; j<k; ++j, --k)
    {
        Type sj = str[j], sk = str[k];
        str[j] = ( sk == c1 ? c0 : c1 );
        str[k] = ( sj == c1 ? c0 : c1 );
    }
}
// -------------------------


#endif  // !defined HAVE_REVERSE_PAREN_STRING_H__
