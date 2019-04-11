#if !defined  HAVE_PERMRAND_DERANGE3_H__
#define       HAVE_PERMRAND_DERANGE3_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/rand-idx.h"
#include "aux0/randf.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "fxtio.h"
//#include "jjassert.h"


inline void init_derange3_branch_ratios(double *b, ulong N)
// Precompute branching probabilities for random derangements
//  with all cycles of length >= 3.
//   n ==  2, 3, 4,  5,   6,     7,      8,     9,
//         0, 0, 1,  1,  3/4,  16/19,  95/107, 321/361,
// b[] == [0, 0, 1,  1,  0.75, 0.8421, 0.8878,  0.8891,
// b[n-2] == (n-1) * D3(n-1) / D3(n)  (i.e. offset=2)
{
    b[0] = 0.0;  b[1]=0.0;
    double dn0 = 2.0,  dn1 = 0.0,  dn2 = 0.0;
    double n1 = 2.0,  n2 = 1.0;

    for (ulong n=2; n<N; ++n)
    {
#if 0  // unnormalized:
        const double dn3 = dn2;
        dn2 = dn1;
        dn1 = dn0;
        n1 += 1.0; n2 += 1.0;
        dn0 = n1*(dn1 + n2*dn3);
        b[n] = (n1) * dn1/dn0;  // == (n-1) * D3(n-1) / D3(n)
//        cout << setw(4) << n << ": bn=" << b[n] << endl;
#else  // normalized:
        double dn3 = dn2;
        dn2 = dn1;
        dn1 = 1.0;  // ==dn0;
        n1 += 1.0; n2 += 1.0;
        dn0 = n1*(dn1 + n2*dn3);
        dn1 /= dn0;
        dn2 /= dn0;
        dn3 /= dn0;
        // dn0 /= dn0;  // i.e. dn0==1.0
        b[n] = n1 * dn1;  // == (n-1) * D3(n-1) / D3(n)
//        cout << setw(4) << n << ": bn=" << b[n] << endl;
#endif
    }
}
// -------------------------

template <typename Type>
inline void random_derange3(Type *f, ulong n,
                            ulong *tr=0,
                            double *tb=0, bool bi=false)
// Permute the elements of f by a random derangement
//  with all cycles of length >= 3.
// Set bi:=true to signal that the branch probabilities in tb[]
//   have been precomputed (via init_derange3_branch_ratios()).
// Must have n >= 3.
{
//    jjassert( n >= 3 );

    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    for (ulong k=0; k<n; ++k)  r[k] = k;
    ulong nr = n;  // number of elements available
    // available positions are  r[0], ..., r[nr-1]

    double *b = tb;
    if ( tb==0 )  { b = new double[n];  bi=false; }
    if ( !bi )  init_derange3_branch_ratios(b, n);

    while ( nr>=2 )
    {
        const double rat = b[nr-2];
//        cout << nr << ":  rat=" << rat << endl;
//        cout << nr << ":    ~=" << 1.0*(nr-1)/nr << endl;
        const double t = rnd01();  // 0 <= t < 1

        const ulong x1 = nr-1;  // last element
        const ulong r1 = r[x1];
        // remove r[x1]=r1 from set:
        --nr;  // swap2(r[x1], r[nr]);  // (swap not needed if x1==last)


        if ( t < rat )  // join two cycles, leave resulting cycle open
        {
//            jjassert( nr>=1 );
            const ulong x2 = rand_idx(nr);  // random element !=last
            const ulong r2 = r[x2];
            swap2( f[r1], f[r2] );  // join cycles containing f[r1] and f[r2]
        }
        else  // connect cycles of 3 elements and remove all
        {
//            jjassert( nr>=2 );
            const ulong x2 = rand_idx(nr);  // random element !=last
            const ulong r2 = r[x2];
            --nr;  swap2(r[x2], r[nr]);  // remove r[x2]=r2 from set:

            const ulong x3 = rand_idx(nr);  // random element !=both
            const ulong r3 = r[x3];
            --nr;  swap2(r[x3], r[nr]);  // remove r[x3]=r3 from set:

            // random cyclic permutation of all three elements:
            swap2( f[r1], f[r3] );  // [c,b,a]
            if ( rnd01() < 0.5 )  swap2( f[r1], f[r2] );  // [b,c,a]
            else                  swap2( f[r2], f[r3] );  // [c,a,b]
        }
    }

    if ( tr==0 )  delete [] r;
    if ( tb==0 )  delete [] b;
}
// -------------------------


inline void random_derangement3(ulong *f, ulong n,
                                ulong *tr=0,
                                double *tb=0, bool bi=false)
// Create a random derangement with all cycle lengthes >=3.
{
    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_derange3(f, n, tr, tb, bi);
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_DERANGE3_H__
