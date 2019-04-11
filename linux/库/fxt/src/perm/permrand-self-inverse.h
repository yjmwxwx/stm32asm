#if !defined  HAVE_PERMRAND_SELF_INVERSE_H__
#define       HAVE_PERMRAND_SELF_INVERSE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "perm/permrand-cycle-type.h"  // random_cycle()

#include "aux0/swap.h"
#include "aux0/randf.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"

//#include "fxtio.h"
//#include "jjassert.h"


//inline void next_num_involutions(double &in0, double &in1, double &n1)
//// I(n) = I(n-1) + (n-1) * I(n-2)
//// WARNING: overflow for n>295
//{
//    double in2 = in1;
//    in1 = in0;
//    n1 += 1.0;
//    in0 = in1 + n1 * in2;
//}
//// -------------------------
//
//inline void prev_num_involutions(double &in0, double &in1, double &n1)
//// I(n-2) = ( I(n) - I(n-1) ) / (n-1)
//{
//    double in2 = (in0-in1)/n1;
//    in0 = in1;
//    in1 = in2;
//    n1 -= 1.0;
//}
//// -------------------------


inline void next_involution_branch_ratio(double &rat, double &n1)
// R(n) = 1 / ( 1 + (n-1) * R(n-1) )
// R(n+1) = 1 / ( 1 + n * R(n) )
{
    n1 += 1.0;
    rat = 1.0/( 1.0 + n1*rat );
}
// -------------------------

//inline void prev_involution_branch_ratio(double &rat, double &n1)
//// R(n-1) = ( 1/R(n) - 1 ) / ( n-1 )
//// WARNING: numerically unstable
//{
//    rat = (1.0/rat - 1.0)/(n1);
//    n1 -= 1.0;
//}
//// -------------------------

inline void init_involution_branch_ratios(double *b, ulong n)
{
// 0: 1 1.0
// 1: 2 0.5
// 2: 3 0.5
// 3: 4 0.4
// 4: 5 0.384615
// 5: 6 0.342105
// 6: 7 0.327586
// 7: 8 0.303665
// 8: 9 0.291603

    b[0] = 1.0;
    double rat = 0.5,  n1 = 1.0;
    for (ulong k=1; k<n; ++k)
    {
        b[k] = rat;
//        cout << "0: nr=" << k+1 << " b=" << rat << endl;
        next_involution_branch_ratio(rat, n1);
    }
//    cout << endl;
}
// -------------------------


template <typename Type>
inline void random_permute_self_inverse(Type *f, ulong n,
                                        ulong *tr=0,
                                        double *tb=0, bool bi=false)
// Permute the elements of f by a random self-inverse permutation (an involution).
// Set bi:=true to signal that the branch probabilities in tb[]
//   have been precomputed (via init_involution_branch_ratios()).
{
    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    for (ulong k=0; k<n; ++k)  r[k] = k;
    ulong nr = n;  // number of elements available
    // available positions are  r[0], ..., r[nr-1]

    double *b = tb;
    if ( tb==0 )  { b = new double[n];  bi=false; }
    if ( !bi )  init_involution_branch_ratios(b, n);

    while ( nr>=2 )
    {
        const ulong x1 = nr-1;   // choose last element
        const ulong r1 = r[x1];  // available position
        // remove from set:
        --nr;  // no swap needed if x1==last

//        const ulong x1 = rand_idx(nr);
//        const ulong r1 = r[x1];  // available position
//        --nr;  swap2(r[x1], r[nr]);

        const double rat = b[nr];  // probability to choose fixed point

        const double t = rnd01();  // 0 <= t < 1
        if ( t > rat )  // 2-cycle
        {
            const ulong x2 = rand_idx(nr);
            const ulong r2 = r[x2];  // random available position != r1
            --nr;  swap2(r[x2], r[nr]);  // remove from set
            swap2( f[r1], f[r2] );  // create a 2-cycle
        }
        // else fixed point, nothing to do
    }

    if ( tr==0 )  delete [] r;
    if ( tb==0 )  delete [] b;
}
// -------------------------


inline void random_self_inverse_permutation(ulong *f, ulong n,
                                            ulong *tr=0,
                                            double *tb=0, bool bi=false)
// Create a random permutation that is self-inverse (an involution).
{
    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    double *b = tb;
    if ( tb==0 )  { b = new double[n];  bi=false; }

    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_permute_self_inverse(f, n, r, b, bi);

    if ( tr==0 )  delete [] r;
    if ( tb==0 )  delete [] b;
}
// -------------------------



inline ulong rand_num_2cycles_involution(ulong n)
// Return number of 2-cycles for a random involution of n elements.
{
    ulong t0 = 0, t1 = 0;

    double rat = 0.5,  n1 = 1.0;
    for (ulong k=2; k<=n; ++k)
    {
        const double t = rnd01();  // 0 <= t < 1
        if ( t > rat )  // 2-cycle
        {
            ulong v = 1 + t1;  // == 1 + second-last
            t1 = t0;
            t0 = v;
        }
        else  // fixed point
        {
#if 1
            t1 = t0;
#else
            ulong v = t0;  // == last
            t1 = t0;
            t0 = v;
#endif
        }

        next_involution_branch_ratio(rat, n1);

//        cout << k << ": ";
//        cout << "[" << t1 << ", " << t0 << "]  ";
//        cout << "  b=" << rat << "  t=" << t;
//        cout << endl;
    }

    return t0;
}
// -------------------------


template <typename Type>
inline void random_permute_self_inverse1(Type *f, ulong n, ulong *tr=0)
// Permute the elements of f by a random involution.
// This routine avoids the array of branch probabilities.
{
    ulong *r = tr;
    if ( tr==0 )  r = new ulong[n];
    for (ulong k=0; k<n; ++k)  r[k] = k;  // initialize set
    ulong nr = n;  // number of elements available
    // available positions are  r[0], ..., r[nr-1]

    ulong n2c = rand_num_2cycles_involution(n);
//    jjassert( 2*n2c <= n );

//    // remove fixed point from set:  (not needed because cycle leader are selected randomly)
//    ulong nfp = n - 2*n2c;  // number of fixed points
//    while ( nfp-- )
//    {
//        const ulong i0 = rand_idx(nr);
//        --nr;  swap2( r[nr], r[i0] );  // remove position from set
//    }

    while ( n2c-- )  nr = random_cycle(f, 2, r, nr);

    if ( tr==0 )  delete [] r;
}
// -------------------------

inline void random_self_inverse_permutation1(ulong *f, ulong n, ulong *tr=0)
// Create a random involution.
// This routine avoids the array of branch probabilities.
{
    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_permute_self_inverse1(f, n, tr);
}
// -------------------------



#endif  // !defined HAVE_PERMRAND_SELF_INVERSE_H__
