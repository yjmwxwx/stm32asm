// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "array-len.h"
#include "fxttypes.h"


const ulong idoneal_tab[] =
// idoneal numbers
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 21, 22, 24, 25, 28, 30,
    33, 37, 40, 42, 45, 48, 57, 58, 60, 70, 72, 78, 85, 88, 93, 102, 105,
    112, 120, 130, 133, 165, 168, 177, 190, 210, 232, 240, 253, 273, 280,
    312, 330, 345, 357, 385, 408, 462, 520, 760, 840, 1320, 1365, 1848
};
// -------------------------

const ulong npqr_tab[] =
// Only non-prime quadratic residues for these moduli.
// All of them (with the exception of 56) are idoneal.
{
    2, 3, 4, 5, 8, 12, 15, 16, 24, 28, 40, 48, 56, 60, 72, 88,
    112, 120, 168, 232, 240, 280, 312, 408, 520, 760, 840,
    1320, 1848
};
// -------------------------


inline bool is_idoneal(ulong x)
// Return true if the number x is idoneal
{
    const ulong idoneal_tab_len = ARRAY_LEN(idoneal_tab);
    ulong idx = bsearch(idoneal_tab, idoneal_tab_len, x);
    return  ( idoneal_tab_len != idx );
}
// -------------------------


inline ulong is_npqr(ulong x)
// Return true if the number x is a modulus such
// that no squares mod x are primes.
{
    const ulong npqr_tab_len = ARRAY_LEN(npqr_tab);
    ulong idx = bsearch(npqr_tab, npqr_tab_len, x);
    return  ( npqr_tab_len != idx );
}
// -------------------------
