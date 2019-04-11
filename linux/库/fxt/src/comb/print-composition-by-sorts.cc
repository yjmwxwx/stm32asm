// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxtio.h"
#include "fxttypes.h"

void
print_composition_with_sorts(const char* bla, const ulong *va, const ulong *vs, ulong m)
// Print as vector of pairs P:S (for part:sort).
// Example: for va[]=[1, 2, 1, 3, 2] and s[]=[0, 1, 1, 0, 3]
// print [ 1:0 2:1 1:1 3:0 2:3 ]
{
    if ( bla )  cout << bla;

    cout << "[";
    for (ulong j=0; j<m; ++j)
    {
        cout << setw(2) << va[j];
        cout << ":" << vs[j];
        cout << " ";
    }
    cout << " ]";
}
// -------------------------


void
print_rev_composition_with_sorts(const char* bla, const ulong *va, const ulong *vs, ulong m)
// Print as vector of pairs P:S (for part:sort), reversed order.
// Example: for va[]=[1, 1, 2, 5, 7] and s[]=[0, 1, 1, 0, 3]
// print [ 7:3 5:0 2:1 1:1 1:0 ]
{
    if ( bla )  cout << bla;

    cout << "[";
    ulong j = m;
    while ( j-- )
    {
        cout << setw(2) << va[j];
        cout << ":" << vs[j];
        cout << " ";
    }
    cout << " ]";
}
// -------------------------


void
print_composition_by_sorts(const char* bla, const ulong *va, const ulong *vs, ulong m)
// Print as vector of vectors, one vector for each sort.
// Example: for va[]=[1, 2, 1, 3, 2] and s[]=[0, 1, 1, 0, 3]
// print [ [ 1 3 ]  [ 2 1 ]  [ ]  [2] ]
{
    if ( bla )  cout << bla;

    cout << "[ ";
    ulong ct = 0;
    ulong s = 0;
    while ( ct < m )
    {
        cout << "[ ";
        for (ulong j=0; j<m; ++j)
        {
            if ( vs[j] == s )
            {
                cout << va[j] << " ";
                ++ct;
            }
        }
        cout << "]  ";
        ++s;
    }
    cout << "]";
}
// -------------------------
