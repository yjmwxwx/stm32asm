// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/revbin.h"
#include "fxttypes.h"
#include "fxtio.h"


void
print_bit_set(const char *bla, ulong x, ulong rq/*=0*/)
// Print delta set given as word x as set.
// Example:       x=[0,0,1,0,1,1] ==> { 0, 1, 3 }
// if rq!=0 then print set for rq-bit reversed binary word:
// Example: rq=6, x=[0,0,1,0,1,1] ==> { 3, 1, 0 }
{
    if ( bla )  cout << bla;
    cout << "{ ";
    if ( rq )  x = revbin(x, rq);
    ulong n = 0;
    while ( x )
    {
        if ( x & 1 )
        {
            cout << n;
            if ( x>>1 )  cout << ",";
            cout << " ";
        }
//        else
//        {
//            cout << " ";
//            if ( x>>1 )  cout << ",";
//            cout << " ";
//        }

        ++n;
        x >>= 1;
    }
    cout << "}";
}
// -------------------------

