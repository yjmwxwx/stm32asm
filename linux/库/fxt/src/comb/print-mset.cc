// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "comb/comb-print.h"

#include "fxtio.h"

#include "fxttypes.h"

#include "jjassert.h"

// Enable heuristic check like asserting that
// a symbol appears at most 10000 times
// (which usually indicates an error like an under-run):
#define HEURISTIC_ASSERTS

ulong
print_multi_deltaset_as_set(const char *bla, const ulong *x, ulong n, bool cq/*=true*/)
// Print multi delta set x[0,..,n-1]  as set.
// Example:  x[]=[0,0,1,0,3,0,1] ==> "{2,4,4,4,6}"
// Return number of elements (5 in example).
// Parameter cq determines whether commas (and spaces) are printed between elements.
{
    if ( bla )  cout << bla;

    ulong pnz = n;  // position of last nonzero count
    for (ulong j=0; j<n; ++j)  if ( x[j]!=0 )  pnz = j;

    cout << "{ ";
    ulong num = 0;
    for (ulong k=0; k<n; ++k)
    {
        const ulong xk = x[k];
        if ( xk == 0 )  continue;
        num += xk;

#ifdef HEURISTIC_ASSERTS
        jjassert( xk <= 10000 );
#endif
        for (ulong j=0; j<xk; ++j)
        {
            cout << k;
            if ( (k!=pnz) || (j!=xk-1) )
                if ( cq )  cout << ", ";
        }
    }
    cout << " }";

    return  num;
}
// -------------------------


static const char *alph = "abcdefghijklmnopqrstuvwxyz";
//static const char *alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

ulong
print_multi_deltaset_as_set_alph(const char *bla, const ulong *x, ulong n, bool cq/*=true*/)
// Print multi delta set x[0,..,n-1]  as set of letters.
// Example:  x[]=[0,1,3,0,1] ==> "{b,c,c,c,e}"
// Return number of elements (5 in example).
// Parameter cq determines whether commas (and spaces) are printed between elements.
{
    jjassert( n <= 26 );  // only that many symbols

    if ( bla )  cout << bla;

    ulong pnz = n;  // position of last nonzero count
    for (ulong j=0; j<n; ++j)  if ( x[j]!=0 )  pnz = j;

    cout << "{ ";
    ulong num = 0;
    for (ulong k=0; k<n; ++k)
    {
        const ulong xk = x[k];
        if ( xk == 0 )  continue;
        num += xk;

#ifdef HEURISTIC_ASSERTS
        jjassert( (long)xk >= 0 );
#endif
        for (ulong j=0; j<xk; ++j)
        {
            cout << alph[k];
            if ( (k!=pnz) || (j!=xk-1) )
                if ( cq )  cout << ", ";
        }
    }
    cout << " }";

    return  num;
}
// -------------------------
