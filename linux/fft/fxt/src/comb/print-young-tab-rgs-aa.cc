// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "comb/print-young-tab-rgs-aa.h"

#include "fxtio.h"
#include "fxttypes.h"



void
print_young_tab_rgs_aa(const ulong *A, const ulong *P, ulong n, ulong off/*=1*/)
// Render Young tableau as ASCII art.
// The value of the upper left element is determined by off.
// P must contain the partition (as weakly descending list)
//  that corresponds to A[].
// Example: for
//   A[] = [ 0 1 0 2 1 0 ]  (and P[] = [ 3 2 1 0 0 0 ])
// the output is
//  --- --- ---
// | 1 | 3 | 6 |
//  --- --- ---
// | 2 | 5 |
//  --- ---
// | 4 |
//  ---
{
    cout << " ";
    for (ulong j=0; j<P[0]; ++j)  cout << "--- ";
    cout << endl;

    for (ulong r=0, ct=0;  ct<n;  ++r)
    {
        cout << "|";
        for (ulong j=0; j<n; ++j)
        {
            if ( A[j] == r )
            {
                ct += 1;
                cout << setw(2) << (j + off) << " |";
            }
        }
        cout << endl;

        cout << " ";
        for (ulong j=0; j<P[r]; ++j)  cout << "--- ";
        cout << endl;
    }
}
// -------------------------
