// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"


void
print_composition_aa(const ulong *a, ulong m)
// Render composition as ASCII art.
{
    cout << endl;

    --a;  // make one-based

    ulong mx = 0;
    for (ulong j=1; j<=m; ++j)
        if ( a[j] > mx )  mx = a[j];

    for (ulong k=mx; k>0; --k)
    {
        cout << ' ';

        ulong kl = 0;  // last occurrence of element >=k
        for (ulong j=1; j<=m; ++j)
            if ( a[j]>=k )  kl = j;

        for (ulong j=1; j<=kl; ++j)
        {
            cout << ( a[j] >= k ? 'o' : ' ' );
        }
        cout << endl;
    }
}
// -------------------------

void
print_fountain_aa(const ulong *a, ulong m)
// Render composition as fountain of coin ASCII art.
{

    cout << endl;

    --a;  // make one-based

    ulong mx = 0;  // max value
    for (ulong j=1; j<=m; ++j)
        if ( a[j] > mx )  mx = a[j];

    for (ulong k=mx; k>0; --k)
    {
        cout << ' ';

        ulong kl = 0;  // last occurrence of element >=k
        for (ulong j=1; j<=m; ++j)
            if ( a[j]>=k )  kl = j;

        for (ulong j=0; j<=mx-k; ++j)  cout << ' ';  // fountain
        for (ulong j=1; j<=kl; ++j)
        {
            cout << ' ';  // fountain
            cout << ( a[j] >= k ? 'O' : ' ' );
        }
        cout << endl;
    }
}
// -------------------------
