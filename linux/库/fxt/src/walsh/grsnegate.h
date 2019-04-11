#if !defined  HAVE_GRSNEGATE_H__
#define       HAVE_GRSNEGATE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/parity.h"


template <typename Type>
void grs_negate(Type *f, ulong n)
// Negate elements at indices where the Golay-Rudin-Shapiro is negative.
{
    for (ulong k=0; k<n; ++k)
    {
        ulong gnq  =  parity( k & (k>>1) );  // == grs_negative_q(k)
        if ( gnq )  f[k] = -f[k];
    }
}
// -------------------------


#endif  // !defined HAVE_GRSNEGATE_H__
