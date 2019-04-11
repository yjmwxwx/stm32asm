// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/permq.h"
#include "ds/bitarray.h"
#include "ds/left-right-array.h"

#include "fxttypes.h"


bool
is_identity(const ulong *f, ulong n)
// Return whether f[] is the identical permutation,
// i.e. whether f[k]==k for all k= 0...n-1
{
    for (ulong k=0; k<n; ++k)  if ( f[k] != k )  return false;
    return true;
}
// -------------------------

bool
has_fixed_points(const ulong *f, ulong n)
// Return whether f[k]==k for any k= 0...n-1
{
    for (ulong k=0; k<n; ++k)  if ( f[k] == k )  return true;
    return false;
}
// -------------------------


ulong
count_fixed_points(const ulong *f, ulong n)
// Return number of fixed points in f[]
{
    ulong ct = 0;
    for (ulong k=0; k<n; ++k)  ct += ( f[k] == k );
    return ct;
}
// -------------------------

ulong
count_descents(const ulong *f, ulong n)
// Return number of descents in f[]
{
    if ( n<=1 ) return 0;
    ulong ct = 0;
    ulong vl =f[0],  v;
    for (ulong k=1; k<n; ++k)
    {
        v = f[k];
        ct += ( v<vl );
        vl = v;
    }
    return ct;
}
// -------------------------


ulong
count_excedances(const ulong *f, ulong n, bool eq/*=true*/)
// Return number of excedances in f[]:
// an excedance is a position k where f[k]>k.
// If eq==false then return number of k such that f[k]<k
{
    ulong ct = 0;
    if ( eq )  for (ulong k=0; k<n; ++k)  ct += ( f[k]>k );
    else       for (ulong k=0; k<n; ++k)  ct += ( f[k]<k );
    return ct;
}
// -------------------------

ulong
count_inversions(const ulong *f, ulong n)
// Return number of inversions in f[],
// i.e. number of pairs k,j where k<j and f[k]>f[j]
// Algorithm is O(n^2).
{
    ulong ct = 0;
    for (ulong k=1; k<n; ++k)
    {
        ulong fk = f[k];
        for (ulong j=0; j<k; ++j)  ct += ( fk<f[j] );
    }
    return ct;
}
// -------------------------

ulong
count_inversions(const ulong *f, ulong n, left_right_array *tLR)
// Return number of inversions in f[],
// i.e. number of pairs k,j where k<j and f[k]>f[j]
// Version for large arrays, algorithm is O(n*log_2(n))
{
    left_right_array *LR = tLR;
    if ( tLR==0 )  LR = new left_right_array(n);

    ulong ct = 0;
    LR->set_all();
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = LR->num_SLE( f[k] );
        LR->get_set_idx_chg( i );
        ct += i;
    }

    if ( tLR==0 )  delete LR;
    return ct;
}
// -------------------------



bool
is_derangement(const ulong *f, ulong n)
// Return whether f[] is a derangement of identity,
// i.e. whether f[k]!=k for all k
{
    for (ulong k=0; k<n; ++k)  if ( f[k] == k )  return false;
    return true;
}
// -------------------------


bool
is_derangement(const ulong *f, const ulong *g, ulong n)
// Return whether f[] is a derangement of g[],
// i.e. whether f[k]!=g[k] for all k
{
    for (ulong k=0; k<n; ++k)  if ( f[k] == g[k] )  return false;
    return true;
}
// -------------------------


bool
is_connected(const ulong *f, ulong n)
// Return whether permutation is connected (indecomposable),
// i.e. whether {f[0],f[1],...,f[k]} != {0,...,k} for all k<n-1
// i.e. whether no proper prefix of the array is mapped to itself.
{
    if ( n<=1 )  return true;
    ulong m = 0;  // maximum
    for (ulong k=0; k<n-1; ++k)  // for all proper prefixes
    {
        const ulong fk = f[k];
        if ( fk>m )  m = fk;
        if ( m<=k )  return false;
    }
    return true;
}
// -------------------------


bool
is_updown_permutation(const ulong *f, ulong n)
// Return whether f is an up-down condition,
// i.e. whether f[0] < f[1] > f[2] < f[3] > ...
{
    if ( n<2 )  return true;

    for (ulong k=1; k<n; k+=2)  { if ( f[k]<=f[k-1] ) return false; }
    for (ulong k=2; k<n; k+=2)  { if ( f[k]>=f[k-1] ) return false; }

    return true;
}
// -------------------------


bool
is_cyclic(const ulong *f, ulong n)
// Return whether permutation is exactly one cycle.
{
    if ( n<=1 )  return true;
    ulong k = 0,  e = 0;
    do  { e=f[e]; ++k; }  while ( e!=0 );
    return  (k==n);
}
// -------------------------


bool
is_valid_permutation(const ulong *f, ulong n, bitarray *bp/*=0*/)
// Return whether all values 0...n-1 appear exactly once,
// i.e. whether f represents a permutation of [0,1,...,n-1].
{
    // check whether any element is out of range:
    for (ulong k=0; k<n; ++k)  if ( f[k]>=n )  return false;

    // check whether values are unique:
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    ulong k;
    for (k=0; k<n; ++k)  if ( tp->test_set(f[k]) )  break;

    if ( 0==bp )  delete tp;

    return  (k==n);
}
// -------------------------


bool
is_involution(const ulong *f, ulong n, bool hint/*=false*/)
// Return whether max cycle length is <= 2,
// i.e. whether f * f = id.
// Set hint to true if the permutation is expected to be
// an involution
{
    if ( hint )
    {
        ulong z = 0;
        for (ulong k=0; k<n; ++k)  z |= (f[f[k]] ^ k);
        return  (0==z);
    }
    else
    {
        for (ulong k=0; k<n; ++k)  if ( f[f[k]] != k )  return false;
        return true;
    }
}
// -------------------------


bool
is_inverse(const ulong *f, const ulong *g, ulong n, bool hint/*=false*/)
// Return whether f[] is the inverse of g[].
// Set hint to true if the permutations are expected to be
// mutual inverses.
{
    if ( hint )
    {
        ulong z = 0;
        for (ulong k=0; k<n; ++k)  z |= (f[g[k]] ^ k);
        return  (0==z);
    }
    else
    {
        for (ulong k=0; k<n; ++k)  if ( f[g[k]] != k )  return false;
        return true;
    }
}
// -------------------------


bool
is_square(const ulong *f, const ulong *g, ulong n)
// Return whether f * f == g  as a permutation
{
    for (ulong k=0; k<n; ++k)  if ( g[k] != f[f[k]] )  return false;
    return true;
}
// -------------------------

ulong
get_index(const ulong *f, ulong n)
// Return index of permutation.
{
    ulong i = 0;
    for (ulong k=1; k<n; ++k)  if ( f[k-1]>f[k] )  i += k;
    return i;
}
// -------------------------


ulong
count_transpositions(const ulong *f, ulong n, bitarray *bp/*=0*/)
// Return minimal number of transpositions required for the permutation.
// The lowest bit of the return value is the parity of the permutation.
{
    bitarray *tp = bp;
    if ( 0==bp )  tp = new bitarray(n);  // tags
    tp->clear_all();

    ulong nt = 0;  // minimal number of transpositions
    for (ulong k=0; k<n; ++k)
    {
        if ( tp->test(k) )  continue;  // already processed

        // Follow a cycle:
        ulong len = 0;
        ulong i = k;
        while ( 0==(tp->test_set(i)) )
        {
            i = f[i];
            ++len;
        }
        nt += (len - 1);  // length-len cycle needs len-1 transpositions
    }

    if ( 0==bp )  delete tp;
    return nt;
}
// -------------------------

ulong
count_cycles(const ulong *f, ulong n, bitarray *bp/*=0*/)
{
    return  n - count_transpositions(f, n, bp);
}
// -------------------------

ulong
major_index(const ulong *f, ulong n)
{
    if ( n<=1 )  return 0;
    ulong s = 0;
    --n;
    for (ulong j=0; j<n; ++j)
        if ( f[j] > f[j+1] )  s += (j+1);
    return s;
}
// -------------------------

//ulong
//get_periods(const ulong *f, ulong n, ulong *p, bitarray *bp/*=0*/)
//// Write to p[k] the period of element f[k]
//// (period := length of cycle containing f[k])
//// Return minimal number of transpositions required for the permutation.
////
//// Example (n=11):
////   k:   f[k]  p[k]
////   0:    3     2
////   1:    7     3
////   2:    9     5
////   3:    0     2
////   4:    2     5
////   5:    1     3
////   6:   10     5
////   7:    5     3
////   8:    8     1
////   9:    6     5
////  10:    4     5
//// return nt=7
//{
//    bitarray *tp = bp;
//    if ( 0==bp )  tp = new bitarray(n);  // tags
//    tp->clear_all();
//
//    ulong nt = 0;  // minimal number of transpositions
//    for (ulong k=0; k<n; ++k)
//    {
//        if ( tp->test_clear(k) )  continue;  // already processed
//
//        // Follow a cycle:
//        ulong len = 0;
//        ulong i = k;
//        while ( 0==(tp->test_set(i)) )
//        {
//            i = f[i];
//            ++len;
//        }
//        nt += (len - 1);  // length-len cycle needs len-1 transpositions
//
//        i = k;
//        do
//        {
//            p[i] = len;
//            i = f[i];
//        }
//        while ( i!=k );
//    }
//
//    if ( 0==bp )  delete tp;
//    return nt;
//}
//// -------------------------



bool
is_simple(const ulong *f, ulong n)
// Return whether permutation is simple.
// A permutation is simple if the only intervals that are mapped to an
//  interval of the same length is the full permutation and the singletons.
// Cf. OEIS sequence A111111.
// Complexity is O(n^2).
{
    if ( n <= 2 )  return true;

    for (ulong j=0; j < n-1; ++j)  // start of range
    {
        ulong mi = f[j];  // min of images in range
        ulong ma = f[j];  // max of images in range
        for (ulong k=j+1;  k < n - (j==0);  ++k)  // end of range
        {
            const ulong fk = f[k];
            if ( fk < mi )  mi = fk;
            if ( fk > ma )  ma = fk;

            if ( ma - mi == k - j )  return false;
        }
    }

    return true;
}
// -------------------------
