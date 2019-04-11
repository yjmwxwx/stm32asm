#if !defined HAVE_HAARPERMUTE_H__
#define      HAVE_HAARPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "perm/revbinpermute.h"


template <typename Type>
void haar_permute(Type *f, ulong n)
// Reorder autoput of inplace_haar() as in haar()
// To be called after inplace_haar()
{
    revbin_permute(f, n);
    // here: high freq are in upper half

    // m=(2,) 4, 8, ..., n/2: (revbin_permute()s do not overlap)
    for (ulong m=4; m<=n/2; m*=2)  revbin_permute(f+m, m);
}
// -------------------------


template <typename Type>
void inverse_haar_permute(Type *f, ulong n)
// Reorder autoput of inverse_inplace_haar() as in inverse_haar()
// To be called before inverse_inplace_haar()
{
    // m=(2,) 4, 8, ..., n/2:
    for (ulong m=4; m<=n/2; m*=2)  revbin_permute(f+m, m);
    revbin_permute(f, n);
}
// -------------------------


#endif  // !defined HAVE_HAARPERMUTE_H__
