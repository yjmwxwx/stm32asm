#if !defined  HAVE_PERMRAND_DERANGE_H__
#define       HAVE_PERMRAND_DERANGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "aux0/randf.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"


//#include <cmath>
//#include "jjassert.h"
//#include "fxtio.h"

//inline void next_num_derangements(double &dn0, double &dn1, double &n1)
//// D(n) = (n-1) * ( D(n-1) + D(n-2) )
//{
//    const double dn2 = dn1;  dn1 = dn0;  n1 += 1.0;
//    dn0 = n1*(dn1 + dn2);
//}
//// -------------------------


//inline void prev_num_derangements(double &dn0, double &dn1, double &n1)
//// D(n-2) = D(n) / (n-1) - D(n-1)
//// WARNING: numerically unstable
//{
//    double dn2 = dn0/n1 - dn1;
//    dn0 = dn1;
//    dn1 = dn2;
//    n1 -= 1.0;
//}
//// -------------------------


// number of precomputed branch ratios:
#define NUM_PBR 32  // OK for up to 106-bit mantissa

inline void init_derange_branch_ratios(double *b)
// Precompute branching probabilities for random derangements.
//   n ==  1, 2, 3,  4,      5,      6,      7,      8, ...
// b[] ==  0, 1, 0, 0.3333, 0.1818, 0.1698, 0.1423, 0.1250, ...
// b[n-1] == (n-1) * D(n-2) / D(n)
{
    b[0] = 0.0;  // unused
    b[1] = 1.0;
    double dn0 = 1.0,  dn1 = 0.0,  n1 = 1.0;
    for (ulong n=3; n<=NUM_PBR; ++n)
    {
#if 0  // unnormalized:
        const double dn2 = dn1;
//        next_num_derangements(dn0, dn1, n1);
        dn1 = dn0;
        n1 += 1.0;
        dn0 = n1*(dn1 + dn2);
        b[n-1] = (n1) * dn2/dn0;  // == (n-1) * D(n-2) / D(n)
#else  // normalized:  (must use for NUM_PBR>32)
        double dn2 = dn1;
        dn1 = 1.0;  // ==dn0;
        n1 += 1.0;
        dn0 = n1*(dn1 + dn2);
        dn1 /= dn0;
        dn2 /= dn0;
        // dn0 /= dn0;  // i.e. dn0==1.0
        b[n-1] = n1 * dn2;  // == (n-1) * D(n-2) / D(n)
#endif
    }
}
// -------------------------

inline double derange_branch_ratio(const double *b, ulong n)
// Reurn probability for closing cycle with n elements.
{
    if ( n<NUM_PBR )  return b[n];
    else              return 1.0/(double)n;  // relative error < 1.0e-32
}
// -------------------------



template <typename Type>
inline void random_derange(Type *f, ulong n,
                           ulong *tr=0,
                           double *tb=0, bool bi=false)
// Permute the elements of f by a random derangement.
// Set bi:=true to signal that the branch probabilities in tb[]
//   have been precomputed (via init_derange_branch_ratios()).
// Must have n > 1.
{
//    jjassert( n > 1 );

    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    for (ulong k=0; k<n; ++k)  r[k] = k;
    ulong nr = n;  // number of elements available
    // available positions are  r[0], ..., r[nr-1]

    double *b = tb;
    if ( tb==0 )  { b = new double[NUM_PBR];  bi=false; }
    if ( !bi )  init_derange_branch_ratios(b);

    while ( nr>=2 )
    {
        const ulong x1 = nr-1;  // last element
        const ulong r1 = r[x1];

        const ulong x2 = rand_idx(nr-1);  // random element !=last
        const ulong r2 = r[x2];

        swap2( f[r1], f[r2] );  // join cycles containing f[r1] and f[r2]

        // remove r[x1]=r1 from set:
        --nr;  // swap2(r[x1], r[nr]);  // swap not needed if x1==last

        const double rat = derange_branch_ratio(b, nr);
        const double t = rnd01();  // 0 <= t < 1
        if ( t < rat )  // close cycle
        {
            // remove r[x2]=r2 from set:
            --nr;  swap2(r[x2], r[nr]);
        }
        // else  cycle stays open
    }

    if ( tr==0 )  delete [] r;
    if ( tb==0 )  delete [] b;
}
// -------------------------


inline void random_derangement(ulong *f, ulong n,
                               ulong *tr=0,
                               double *tb=0, bool bi=false)
// Create a random permutation that has no fixed points (a derangement).
{
    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    double *b = tb;
    if ( tb==0 )  { b = new double[NUM_PBR];  bi=false; }

    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_derange(f, n, r, b, bi);

    if ( tr==0 )  delete [] r;
    if ( tb==0 )  delete [] b;
}
// -------------------------

#undef NUM_PBR


#endif  // !defined HAVE_PERMRAND_DERANGE_H__
