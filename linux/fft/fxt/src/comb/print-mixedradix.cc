// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtio.h"

void
print_mixedradix(const char *bla, const ulong *f, ulong n, bool dfz/*=false*/)
// Print n-digit mixed radix number in f[].
// If dfz is true then Dots are printed For Zeros.
{
    if ( bla )  cout << bla;
    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        ulong t = f[k];
        if ( t!=0 )  cout << t;
        else         cout << (dfz?'.':'0');
        cout << " ";
    }
    cout << "]";
}
// -------------------------
