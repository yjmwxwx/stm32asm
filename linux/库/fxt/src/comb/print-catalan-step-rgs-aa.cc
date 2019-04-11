// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"
#include "fxttypes.h"

void
catalan_step_rgs_print_aa(const ulong *a, ulong n)
// Render the lattice path for the RGS as ASCII art.
// The path for the RGS a[] starts at (0, 0)==(0, a[0]),
// goes over the points (k, a[k]) for 1 <= k <= n-1,
// and ends at (n, n)==(n, a[n]).
// Steps are (+1,0) and (+1,+1) and the path does not
// go below the diagonal (k, k) for 0 <= k <= n.
{
    cout << endl;
    for (ulong r=n; r>0; --r)
    {
        cout << ' ';
        ulong i1 = a[r-1];
        ulong i = (r==n ? n : a[r]);  // do not read a[n]
        ulong w;
        for (w=0; w<i1; ++w)  cout << ' ';
        if ( w<i )  { cout << '.'; ++w; }
        for (   ; w<i; ++w)  cout << '_';

        if ( r != n )  cout << '|';
        cout << endl;
    }
}
// -------------------------

