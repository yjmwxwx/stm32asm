// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"

#include <cmath>  // floor()


void
print_fixed(const char *bla, double v, long nd, bool sq)
// Print exactly nd digits of v
// Print sign if sq!=0
{
    if ( bla )  cout << bla;
    if ( sq )  cout << (v>=0 ? '+' : '-');
    else       cout << (v>=0 ? ' ' : '-');
    if ( v < 0 )  v = -v;
    double f = floor(v);
    v -= f;
    cout << f;
    cout << '.';
    do { --nd; } while ( (f*=0.1)>1.0 );
    for ( ; nd>0; --nd)
    {
        v *= 10.0;
        f = floor(v);
        v -= f;
        cout << f;
    }
}
// -------------------------
