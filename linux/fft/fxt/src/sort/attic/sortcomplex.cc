// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "sort/sortfunc.h"
#include "sort/sortcomplex.h"

#include "fxttypes.h"
#include "complextype.h"


static inline int
cmp_complex(const Complex &f, const Complex &g)
// Comparison function used for sorting complex numbers.
// Major order by real part, minor order by imaginary part.
{
    const double fr = f.real(),  gr = g.real();
    if ( fr!=gr )  return  (fr>gr ? +1 : -1);

    const double fi = f.imag(),  gi = g.imag();
    if ( fi!=gi )  return  (fi>gi ? +1 : -1);

    return  0;
}
// -------------------------

bool
is_complex_sorted(Complex *f, ulong n)
{
    return  is_sorted(f, n, cmp_complex);
}
// -------------------------

void
complex_sort(Complex *f, ulong n)
// major order wrt. real part
// minor order wrt. imag part
{
    quick_sort(f, n, cmp_complex);
}
// -------------------------

ulong
bsearch_complex(const Complex *f, ulong n, Complex v)
//
// return index of first element in f[] that is == v
// return n if there is no such element
// f[] must be sorted in ascending (major-real, minor-imag) order
//
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;
        if  ( cmp_complex(f[t], v) < 0 )  nlo = t + 1;
        else                              nhi = t;
    }

    if ( f[nhi]==v )  return nhi;
    else              return n;
}
// -------------------------

