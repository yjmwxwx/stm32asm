#if !defined  HAVE_PERMRAND_CYCLE_TYPE_H__
#define       HAVE_PERMRAND_CYCLE_TYPE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"

//#include "jjassert.h"
//#include "fxtio.h"


template <typename Type>
inline ulong random_cycle(Type *f, ulong cl, ulong *r, ulong nr)
// Permute a random subset (of size cl)
// of those elements in f whose positions are given in
// r[0], ..., r[nr-1] by a random cycle of size cl.
// Must have  nr >= cl  and  cl != 0.
// Complexity O(cl).
{
//    jjassert( nr>=cl );
//    jjassert( cl!=0 );

    if ( cl==1 )  // just remove a random position from r[]
    {
        const ulong i = rand_idx(nr);
        --nr;  swap2( r[nr], r[i] );  // remove position from set
    }
    else  // cl >= 2
    {
        const ulong i0 = rand_idx(nr);
        const ulong k0 = r[i0];  // position of cycle leader
        const Type f0 = f[k0];  // cycle leader
        --cl;
        --nr;  swap2( r[nr], r[i0] );  // remove position from set

        ulong kp = k0;  // position of predecessor in cycle
        do  // create cycle
        {
            const ulong i = rand_idx(nr);
            const ulong k = r[i];  // random available position
            f[kp] = f[k];       // move element
            --nr;  swap2( r[nr], r[i] );  // remove position from set
            kp = k;  // update predecessor
        }
        while ( --cl );

        f[kp] = f0;   // close cycle
    }

    return nr;
}
// -------------------------


template <typename Type>
inline void random_permute_cycle_type(Type *f, ulong n, const ulong *c,
                                      ulong *tr=0)
// Permute the elements of f by a random permutation of prescribed cycle type.
// The permutation will have c[k] cycles of length k+1.
// Must have s <= n where s := sum(k=0, n-1, c[k]).
// If s < n then the permutation will have n-s fixed points.
// Complexity O(n).
{
    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    for (ulong k=0; k<n; ++k)  r[k] = k;  // initialize set
    ulong nr = n;  // number of elements available
    // available positions are  r[0], ..., r[nr-1]

    for (ulong k=0; k<n; ++k)
    {
        ulong nc = c[k];  // number of cycles of length k+1;
        if ( nc==0 )  continue;  // no cycles of this length
        const ulong cl = k+1;  // cycle length
        do
        {
            nr = random_cycle(f, cl, r, nr);
        }
        while ( --nc );
    }

    if ( tr==0 )  delete [] r;
}
// -------------------------


inline void random_cycle_type_permutation(ulong *p, ulong n, const ulong *c,
                                          ulong *tr=0)
// Create a random permutation with prescribed cycle type.
// Complexity O(n).
{
    for (ulong k=0; k<n; ++k)  p[k] = k;
    random_permute_cycle_type(p, n, c, tr);
}
// -------------------------


template <typename Type>
inline void random_permute_cycle_type(Type *f, ulong n,
                                      const ulong *m, ulong nm,
                                      const ulong *len,
                                      ulong *tr=0)
// Permute the elements of f by a random permutation of
// prescribed cycle type given as partition:
// The permutation will have m[k] cycles of length len[k]
// where k = 0,1,...,nm-1.
// Must have s <= n where s := sum(k=0, nm-1, m[k]*len[k]).
// If s < n then the permutation will have n-s fixed points.
// Complexity O(n).
{
    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    for (ulong k=0; k<n; ++k)  r[k] = k;  // initialize set
    ulong nr = n;  // number of elements available
    // available positions are  r[0], ..., r[nr-1]

    for (ulong k=0; k<nm; ++k)
    {
        ulong nc = m[k];  // number of cycles of length len[k];
        if ( nc==0 )  continue;  // no cycles of this length
        const ulong cl = len[k];  // cycle length
        do
        {
            nr = random_cycle(f, cl, r, nr);
        }
        while ( --nc );
    }

    if ( tr==0 )  delete [] r;
}
// -------------------------


inline void random_cycle_type_permutation(ulong *p, ulong n,
                                          const ulong *m, ulong nm,
                                          const ulong *len,
                                          ulong *tr=0)
// Create a random permutation with prescribed cycle type.
// Complexity O(n).
{
    for (ulong k=0; k<n; ++k)  p[k] = k;
    random_permute_cycle_type(p, n, m, nm, len, tr);
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_CYCLE_TYPE_H__
