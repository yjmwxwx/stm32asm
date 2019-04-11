// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"
#include "fxttypes.h"


void
print_partition_asc_aa(const ulong *a, ulong m)
{
    cout << endl;

    --a;  // make one-based
    for (ulong k=1; k<=m; ++k)
    {
        cout << ' ';
        for (ulong j=1; j<=a[k]; ++j)  cout << 'o';
        cout << endl;
    }
}
// -------------------------

void
print_partition_asc_conj_aa(const ulong *a, ulong m)
{
    cout << endl;

    --a;  // make one-based
    ulong mx = a[m];
    for (ulong k=mx; k>0; --k)
    {
        cout << ' ';

        ulong j;
        for (j=1; a[j]<k; ++j)  { ; }
        for ( ; j<=m; ++j)  cout << 'o';

        cout << endl;
    }
}
// -------------------------


void
print_partition_desc_aa(const ulong *a, ulong m)
{
    cout << endl;

    --a;  // make one-based
    for (ulong k=1; k<=m; ++k)
    {
        cout << ' ';
        for (ulong j=1; j<=a[k]; ++j)  cout << 'o';
        cout << endl;
    }
}
// -------------------------

void
print_partition_desc_conj_aa(const ulong *a, ulong m)
{
    cout << endl;

    --a;  // make one-based
    ulong mx = a[1];
    for (ulong k=1; k<=mx; ++k)
    {
        cout << ' ';

        ulong kl = 0;  // last occurrence of element >=k
        for (ulong j=1; j<=m; ++j)
        {
            if ( a[j]>=k )  kl = j;
            else  break;
        }

        for (ulong j=1; j<=kl; ++j)  cout << 'o';

        cout << endl;
    }
}
// -------------------------

