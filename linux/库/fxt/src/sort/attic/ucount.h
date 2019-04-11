#if !defined  HAVE_UCOUNT_H__
#define       HAVE_UCOUNT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
inline ulong eq_count(const Type *f, ulong n, Type v)
// Return number of elements that are ==v
{
    ulong ct = 0;
    while ( n-- )  if ( f[n]==v )  ++ct;
    return ct;
}
// -------------------------


template <typename Type>
inline ulong ne_count(const Type *f, ulong n, Type v)
// Return number of elements that are !=v
{
    return  n - eq_count(f, n, v);
}
// -------------------------


template <typename Type>
inline ulong ge_count(const Type *f, ulong n, Type v)
// Return number of elements that are >=v
{
    ulong ct = 0;
    while ( n-- )  if ( f[n]>=v )  ++ct;
    return ct;
}
// -------------------------


template <typename Type>
inline ulong le_count(const Type *f, ulong n, Type v)
// Return number of elements that are <=v
{
    ulong ct = 0;
    while ( n-- )  if ( f[n]<=v )  ++ct;
    return ct;
}
// -------------------------


#endif  // !defined HAVE_UCOUNT_H__
