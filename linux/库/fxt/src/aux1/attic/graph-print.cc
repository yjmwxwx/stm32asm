// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "aux1/aux1double.h"  // norm()
#include "sort/minmaxmed23.h"  // max2()
#include "sort/minmax.h"  // min_max()

#include "fxtalloca.h"
#include "fxttypes.h"

#include "fxtio.h"

#define CHOP(x,eps)  (fabs(x)<(eps) ? 0 : (x))

#include <cmath> // fabs()


void
graph_print(const char *bla, const double *f, ulong n, ulong width/*=60*/, double eps/*=0.0*/)
{
    cout << endl;
    if ( bla )  cout << bla;

    ALLOCA(char, line, width+1);

    cout << "   norm = " << norm(f, n);
    cout << endl;

    double mi, ma;
    min_max(f, n, &mi, &ma);
    double mx = max2( fabs(mi), fabs(ma));
    ma =   mx * 1.1;
    mi = - mx * 1.1;
    double d = ma - mi;
    double v = ( d>1e-9 ? 1.0/d * (double)width : 0.0 );
    ulong z = ulong( -mi * v );  // zero position
    if ( z>width )  z = 0;
    line[width] = 0;

    for (ulong k=0; k<n; ++k)
    {
        double r = f[k];

        for (ulong j=0; j<=width; ++j)  line[j] = ' ';
        ulong g1 = z;
        ulong val = (ulong)( (r-mi)*v+0.01 );
        ulong g2 = val;
        if ( g1>g2 )  ::swap2(g1, g2);
        for (ulong j=g1; j<=g2; ++j)  line[j] = '-';

        if ( z )  line[z] = '|';
        line[val] = '*';
        cout << line;

        r = CHOP(r,eps);
        cout << "   ";
        cout.width( 12 );
        cout << r;
        cout << "   " << k;
        cout << endl;
    }
    cout << endl;
}
// -------------------------

