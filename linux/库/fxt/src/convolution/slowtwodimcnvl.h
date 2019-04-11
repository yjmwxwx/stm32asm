#if !defined  HAVE_SLOWTWODIMCNVL_H__
#define       HAVE_SLOWTWODIMCNVL_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtalloca.h"
#include "restrict.h"

#include "aux1/copy.h"


template <typename Type>
void slow_twodim_convolution(const Type *f, const Type *g,
                             Type * restrict h,
                             ulong nr, ulong nc)
// (cyclic) two-dimensional convolution:  h[][] :=  f[][] (*) g[][]
// nr := number of rows,  nc := number of columns
// Use zero padded data for linear convolution.
{
    long nrs = (long)nr;
    long ncs = (long)nc;
    for (long rtau=0; rtau<nrs; ++rtau)
    {
        for (long ctau=0; ctau<ncs; ++ctau)
        {
            Type s=0;
            for (long r=0; r<nrs; ++r)
            {
                long r2 = rtau - r;
                if ( r2<0 )  r2 += nrs;

                for (long c=0; c<ncs; ++c)
                {
                    long c2 = ctau - c;
                    if ( c2<0 )  c2 += ncs;

                    s += ( f[r*ncs+c] * g[r2*ncs+c2] );
                }
            }
            h[rtau*ncs+ctau] = s;
        }
    }
}
// -------------------------

template <typename Type>
void slow_twodim_convolution(const Type *f, Type *g, ulong nr, ulong nc)
// (cyclic) two-dimensional convolution:  g[][] :=  f[][] (*) g[][]
// nr := number of rows,  nc := number of columns
// Use zero padded data for linear convolution.
// f may overlap with g
{
    ALLOCA(Type, h, nr*nc);  // slow algorithm ==> rather small table
    slow_twodim_convolution(f, g, h, nr, nc);
    acopy(h, g, nr*nc);
}
// -------------------------


#endif  // !defined HAVE_SLOWTWODIMCNVL_H__
