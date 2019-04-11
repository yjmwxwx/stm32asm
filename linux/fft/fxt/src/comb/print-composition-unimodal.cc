// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"

#include "fxttypes.h"


void
print_composition_unimodal(const char *bla,
                           const ulong *va, const ulong *vs,
                           ulong m)
// Print a partition where each part (except the greatest)
// can be of two sorts as a unimodal composition.
{
    if ( bla )  cout << bla;

    cout << "[ ";
    if ( m != 0 )
    {
        ulong j = 0;
        while ( j != m )
        {
            if ( vs[j] == 0 )
//                cout << setw(2) << va[j] << " ";
                cout << va[j] << " ";
            ++j;
        }
        cout << " "; // extra space after maximal value
        do
        {
            --j;
            if ( vs[j] != 0 )
//                cout << setw(2) << va[j] << " ";
                cout << va[j] << " ";
        }
        while ( j != 0 );

    }
    cout << "]";

}
// -------------------------
