// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bit2pow.h"
#include "bits/bitcount.h"
#include "fxttypes.h"


ulong
test_gray_path(const ulong *f, ulong n)
// Test whether the sequence f[] is a Gray path.
// If so, return zero, else return the index of the second element
//   of the first pair whose difference is not one bit.
{
    ulong v = f[0];
    for (ulong k=1; k<n; ++k)
    {
        ulong vk = f[k];
        ulong d = v ^ vk;
        v = vk;
        if ( 0==one_bit_q(d) )  return k;
    }
    return 0;
}
// -------------------------

bool
is_gray_path(const ulong *f, ulong n)
// Return true if f[] is a Gray path,
//  else return false.
{
    return  ( 0==test_gray_path(f, n) );
}
// -------------------------

ulong
test_canonical_gray(const ulong *f, ulong n)
// Test whether the sequence f[] is canonical.
// If so, return zero, else return the index of the second element
//   of the first pair whose difference is the on wrong track.
// Does NOT check that the sequence is a Gray path.
{
    ulong m = 1;  // next allowed track
    ulong v = f[0];
    for (ulong k=1; k<n; ++k)
    {
        ulong vk = f[k];
        ulong d = v ^ vk;
        v = vk;
        if ( d>=m )
        {
            if ( d>m )  return k;  //  not allowed
            // here: d==m
            m <<= 1;
            if ( (m>n) || (0==m) )  return 0;  // nothing more to test
            // clause     (0==m)  necessary for full words
        }
    }
    return 0;  // reached only if path it not a Gray path
}
// -------------------------

bool
is_canonical_gray(const ulong *f, ulong n)
// Return true if f[] is a Gray path,
//  else return false.
// Does NOT check that the sequence is a Gray path.
{
    return  ( 0==test_canonical_gray(f, n) );
}
// -------------------------


bool
is_monotonic_gray(const ulong *f, ulong n)
// Return true if f[] is a monotonic Gray path,
//  else return false.
// Does NOT check that the sequence is a Gray path.
{
    ulong mi = 0;
    ulong ma = 1;
    for (ulong k=0; k<n; ++k)
    {
        ulong v = bit_count(f[k]);
        if ( v<mi )  return  false;
        if ( v>ma )
        {
            if ( v>ma+1 )  return false;
            ++ma;
            ++mi;
        }
    }
    return  true;
}
// -------------------------


bool
is_complementary_gray(const ulong *f, ulong n)
// Return whether the sequence f[] is complementary.
// Does NOT check that the sequence is a Gray path.
{
    ulong m = n-1, nh = n/2;
    for (ulong k=0; k<nh; ++k)
    {
        if ( m!=(f[k]^f[nh+k]) )  return false;
    }
    return  true;
}
// -------------------------
