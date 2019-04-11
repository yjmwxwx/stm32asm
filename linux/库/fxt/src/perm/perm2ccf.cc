// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"
#include "fxtio.h"
#include "fxttypes.h"


void
perm2ccf(const ulong *p, ulong n, ulong *c, bitarray *tb/*=0*/)
// Convert permutation in p[] (array form) into
// canonical cycle form (CCF), written to c[].
// Example:
// The permutation [4,3,2,0,1,9,8,5,6,7] has the
// cycles (0,4,1,3) (2) (5,9,7) (6,8).
// Writing the cycles such that each ends with its minimum
// and sorting with respect to minima (last elements) gives
// (4,1,3,0) (2) (9,7,5) (8,6) and the CCF is
// [4,1,3,0, 2, 9,7,5, 8,6].
{
    bitarray * b = tb;
    if ( 0==tb )  b = new bitarray(n);
    b->clear_all();

    ulong m = 0;  // minimum of unprocessed elements (==cycle end)
    ulong j = 0;  // position in c[]
    while ( m!=n )
    {
        ulong lc = m;  // last in cycle
        do
        {
            ulong nc = p[lc];  // next in cycle
            c[j] = nc;
            ++j;
            lc = nc;
            b->set(lc);  // mark as processed
        }
        while ( lc!=m );
        m = b->next_clear(m+1);  // ==n if no clear bit present
    }

    if ( 0==tb )  delete b;
}
// -------------------------

void
ccf2perm(const ulong *c, ulong n, ulong *p, bitarray *tb/*=0*/)
// Convert permutation in canonical cycle form (CCF) in c[] into
// array form, written to p[].
{
    bitarray * b = tb;
    if ( 0==tb )  b = new bitarray(n);
    b->clear_all();

    ulong m = 0;  // minimum of unprocessed elements (==cycle end)
    ulong j = 0;  // position in c[]
    while ( j!=n )
    {
        ulong lc = m;  // last in cycle
        do
        {
            ulong nc = c[j];  // next in cycle
            ++j;
            p[lc] = nc;
            lc = nc;
            b->set(lc);  // mark as processed
        }
        while ( lc!=m );  // until cycle end
        m = b->next_clear(m+1);  // ==n if no clear bit present
    }

    if ( 0==tb )  delete b;
}
// -------------------------


void
print_ccf(const char *bla, const ulong *c, ulong n, bitarray *tb/*=0*/)
// Print cycles of c[], interpreted as canonical cycle form (CCF).
// The minimal element of each cycle is printed last.
{
    if ( bla )  cout << bla;

    bitarray * b = tb;
    if ( 0==tb )  b = new bitarray(n);
    b->clear_all();

    ulong np = 3*n;  // for padding

    ulong m = 0;  // minimum of unprocessed elements (==cycle end)
    ulong j = 0;  // position in c[]
    while ( j!=n )
    {
        ulong lc = m;  // last in cycle
        cout << "(";  np-=1;
        do
        {
            ulong nc = c[j];  // next in cycle
            cout << nc;
            if ( nc!=m )  { cout << ", ";  np-=2; }
            ++j;
            lc = nc;
            b->set(lc);  // mark as processed
        }
        while ( lc!=m );  // until cycle end
        cout << ") ";  np-=2;
        m = b->next_clear(m+1);
    }

    for (  ; np; --np)  cout << " ";  // append blanks to max len

    if ( 0==tb )  delete b;
}
// -------------------------
