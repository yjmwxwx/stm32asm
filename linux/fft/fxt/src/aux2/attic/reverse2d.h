#if !defined HAVE_REVERSE2D_H__
#define      HAVE_REVERSE2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "aux1/copy.h"


template <typename Type>
void reverse_horiz(Type **f, ulong nr, ulong nc)
// reverse order of rows
{
    while ( nr-- )  reverse(f[nr],nc);
}
// -------------------------


template <typename Type>
void reverse_vert(Type **f, ulong nr, ulong nc)
// reverse order of rows
{
    ulong nh = nr/2;
    if ( 0==nh )  return;
    if ( nr&1 )  nh += 1;  // n odd

    for (ulong k=0, i=nr-1; k<nh; ++k,--i)
    {
        swap(f[k], f[i], nc);  // swap(row[#k], row[#i]);
    }
}
// -------------------------


#endif // !defined HAVE_REVERSE2D_H__
