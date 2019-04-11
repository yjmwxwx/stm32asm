// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/print-bin.h"
#include "fxtio.h"

#include "fxttypes.h"  // ulong


void
bitmat_print(const char *bla, const ulong *M, ulong n, ulong nv/*=0*/)
{
    const char * c01 = ".1";
    if ( bla )  cout << bla << endl;
    if ( 0==nv )  nv = n;
    for (ulong k=0; k<nv; ++k)
    {
        ulong v = M[k];
        print_bin_vec("  ", v, n, c01);
        cout << endl;
    }
}
// -------------------------
