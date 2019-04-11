// This file is part of the FXT library.
// Copyright (C) 2012, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtio.h"

void
print_setpart(const char *bla, const ulong *r, ulong n,
              ulong ns, ulong off/*=1*/)
// Print length-n RGS s[] for set partition as set partition.
// Offset off is added to all elements.
// ns should be the number of sets, it is computed if given as zero.
{
    if ( bla )  cout << bla;

    if ( (ns==0) && (n!=0) )  // compute ns if given as 0
    {
        ulong mx = 0;
        for (ulong j=0; j<n; ++j)
            if ( r[j] > mx )  mx = r[j];
        ns = mx + 1;
    }

    for (ulong s=0; s<ns; ++s)
    {
        cout << "{";
        ulong u = 0;
        for (ulong k=0; k<n; ++k)  u += (r[k]==s );

        for (ulong k=0; k<n; ++k)
        {
            if ( r[k] == s )
            {
                cout << (k+off);
                if ( --u )  cout << ", ";
            }
        }
        cout << "}";

        if ( s+1 < ns )  cout << ", ";
    }
}
// -------------------------

