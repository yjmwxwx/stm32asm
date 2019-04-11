// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"
#include "fxttypes.h"


void
print_partition_asc_conj(const char *bla, const ulong *a, ulong m)
{
    if ( bla )  cout << bla;

    cout << "[ ";
    if ( m )
    {
        ulong r = m;  // read position
        ulong p = 0;  // part to write
        do
        {
            p += 1;
            r -= 1;
            ulong d = a[r] - ( r!=0 ? a[r-1] : 0 );
            while ( d-- )  cout << p << " ";
        }
        while ( r );
    }
    cout << "]";
}
// -------------------------

void
print_partition_desc_conj(const char *bla, const ulong *a, ulong m)
{
    if ( bla )  cout << bla;

    cout << "[ ";
    if ( m )
    {
        --a;  // make one-based
        ulong mx = a[1];
        for (ulong k=1; k<=mx; ++k)
        {
            ulong kl = 0;  // last occurrence of element >=k
            for (ulong j=1; j<=m; ++j)
            {
                if ( a[j]>=k )  kl = j;
                else  break;
            }

            cout << kl << " ";
        }
    }
    cout << "]";
}
// -------------------------
