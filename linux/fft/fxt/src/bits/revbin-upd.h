#if !defined HAVE_REVBIN_UPD_H__
#define      HAVE_REVBIN_UPD_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsperlong.h"
#include "bits/bitlow.h"

#include "fxttypes.h"

static inline ulong revbin_upd(ulong r, ulong h)
// Let n=2**ldn and h=n/2.
// Then, with r == revbin(x, ldn) at entry, return revbin(x+1, ldn)
// NOTE: routine will hang if called with r the all-ones word
{
    while ( ! ((r^=h) & h) )  h >>= 1;
    return  r;
}
// -------------------------


// bits/revbin-upd.cc:
extern ulong revbin_upd_tab[BITS_PER_LONG];

#define utab  revbin_upd_tab

static inline void make_revbin_upd_tab(ulong h)
// Initialize lookup table used by revbin_tupd()
{
    utab[0] = h;  // == n/2 == 1UL<<(ldn-1);
    for (ulong i=1; h!=0; ++i)
    {
        h >>= 1;
        utab[i] = utab[i-1] ^ h;
    }
}
// -------------------------

static inline ulong revbin_tupd(ulong r, ulong k)
// Let r==revbin(k, ldn) then
// return revbin(k+1, ldn).
// NOTE 1: need to call make_revbin_upd_tab(ldn) before usage
//         where ldn=log_2(n)
// NOTE 2: different argument structure than revbin_upd()
{
    k = lowest_one_idx( ~k );  // lowest zero idx
    r ^= utab[k];
    return r;
}
// -------------------------
#undef utab


#endif  // !defined HAVE_REVBIN_UPD_H__
