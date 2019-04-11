// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht-default.h"
#include "fht/fht2d.h"
#include "bits/bit2pow.h"  // ld()
#include "fxttypes.h"  // ulong



void
row_column_fht(double *f, ulong nr, ulong nc)
// FHT over rows and columns.
// This is _not_ a 2-dimensional FHT.
// nr := number of rows
// nc := number of columns
{
    ulong n = nr * nc;

    // fht over rows:
    ulong ldc = ld(nc);
    for (ulong k=0; k<n; k+=nc)  fht(f+k, ldc);

    // fht over columns:
    double *w = new double[nr];
    for (ulong k=0; k<nc; k++)  skip_fht(f+k, nr, nc, w);
    delete [] w;
}
// -------------------------


void
y_transform(double *f, ulong nr, ulong nc)
// Transforms row-column-FHT to 2-dimensional FHT.
// Self-inverse.
// nr := number of rows
// nc := number of columns
{
    const ulong rh = (nr+1)/2,  ch = (nc+1)/2;
    const ulong n = nr*nc;
    for (ulong tr=1, ctr=nc;  tr<rh;  tr++, ctr+=nc)  // ctr=nc*tr
    {
        double *pa = f + ctr;
        double *pb = pa + nc;
        double *pc = f + n - ctr;
        double *pd = pc + nc;
        for (ulong tc=1; tc<ch; tc++)
        {
            pa++;
            pb--;
            pc++;
            pd--;
            double e = (*pa + *pd - *pb - *pc) * 0.5;
            *pa -= e;
            *pb += e;
            *pc += e;
            *pd -= e;
        }
    }
}
// -------------------------


void
twodim_fht(double *f, ulong nr, ulong nc)
// 2-dimensional fast Hartley transform (FHT)
// nr := number of rows
// nc := number of columns
{
    row_column_fht(f, nr, nc);
    y_transform(f, nr, nc);
}
// -------------------------
