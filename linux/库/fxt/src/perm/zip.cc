// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "complextype.h"
#include "perm/revbinpermute.h"


void
zip(double *f, ulong n)
//
// lower half --> even indices
// upper half --> odd indices
// n must be a power of 2.
//
// same as transposing the array as 2 x n/2 - matrix
//
// useful to combine real/imag part into a Complex array
// called by real_imag_to_complex()
{
//    ulong nh = n/2;
//    revbin_permute(f, nh);  revbin_permute(f+nh, nh);
//    revbin_permute(f, n);
    // =^=
    revbin_permute(f, n);
    revbin_permute((Complex *)f, n/2);  // jjcast
}
// -------------------------


void
unzip(double *f, ulong n)
//
// inverse of zip():
// put part of data with even indices
// sorted into the lower half,
// odd part into the upper half
// n must be a power of 2.
//
// same as transposing the array as n/2 x 2 - matrix
//
// useful to separate real/imag part from a Complex array
// called by complex_to_real_imag()
{
//    ulong nh = n/2;
//    revbin_permute(f, n);
//    revbin_permute(f, nh);  revbin_permute(f+nh, nh);
    // =^=
    revbin_permute((Complex *)f, n/2);  // jjcast
    revbin_permute(f, n);
}
// -------------------------
