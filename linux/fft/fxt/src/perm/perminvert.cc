// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/bitarray.h"

#include "bits/bit2pow.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"
#include "restrict.h"

void
make_inverse(const ulong *f, ulong * restrict g, ulong n)
// Set (as permutation) g to the inverse of f
{
    for (ulong k=0; k<n; ++k)  g[f[k]] = k;
}
// -------------------------


void
make_inverse(ulong *f, ulong n, bitarray *bp/*=0*/)
// Set (as permutation) f to its own inverse.
// In-place version.
{
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    for (ulong k=0; k<n; ++k)
    {
        if ( tp->test_clear(k) )  continue;  // already processed
        tp->set(k);

        // invert a cycle:
        ulong i = k;
        ulong g = f[i];  // next index
        while ( 0==(tp->test_set(g)) )
        {
            ulong t = f[g];
            f[g] = i;
            i = g;
            g = t;
        }
        f[g] = i;
    }

    if ( 0==bp )  delete tp;
}
// -------------------------


static const ulong s1 = 1UL << (BITS_PER_LONG - 1);  // highest bit is tag bit
static const ulong s0 = ~s1;  // all bits but tag bit

static inline void SET(ulong *f, ulong k)  { f[k & s0] |= s1; }
static inline void CLEAR(ulong *f, ulong k)  { f[k & s0] &= s0; }
static inline bool TEST(ulong *f, ulong k)  { return (0 != (f[k & s0] & s1)); }

void
make_inverse_notag(ulong *f, ulong n)
// Set (as permutation) f to its own inverse.
// In-place version using highest bits of array as tag-bits.
{
    for (ulong k=0; k<n; ++k)
    {
        if ( TEST(f, k) ) { CLEAR(f, k);  continue; }  // already processed
        SET(f, k);

        // invert a cycle:
        ulong i = k;
        ulong g = f[i];  // next index
        while ( 0==TEST(f, g) )
        {
            ulong t = f[g];
            f[g] = i;
            SET(f, g);
            i = g;
            g = t;
        }
        f[g] = i;

        CLEAR(f, k);  // leave no tag bits set
    }
}
// -------------------------


void
boothroyd_invert(ulong *f, ulong n, bitarray *bp/*=0*/)
// Set f to its own inverse. Boothroyd's algorithm.
// Complexity is n*log(n), so make_inverse() is faster.
// Knuth says the algorithm is ingenious, so its here.
// In-place version.
{
    bp = 0;
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    for (ulong m=0; m<n; ++m)
    {
        ulong j = m;
        ulong i = f[j];
        while ( tp->test(j) )  // already processed
        {
            j = i;
            i = f[j];  // next index
        }

        f[j] = f[i];
        f[i] = m;

        tp->set(i);
        //  j stays untagged !
    }

    if ( 0==bp )  delete tp;
}
// -------------------------
