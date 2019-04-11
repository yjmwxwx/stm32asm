#if !defined  HAVE_PERMRAND_CONNECTED_H__
#define       HAVE_PERMRAND_CONNECTED_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "perm/permrand.h"
#include "perm/permq.h"
#include "aux0/swap.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"

//#include "jjassert.h"
//#include "fxtio.h"

#ifndef RCP_VERSION
// The probability that is_connected(f, n) returns false
// is 2/n^RCP_VERSION:
#define RCP_VERSION 2  // 1 or 2 (2 ==> slightly faster for n<100)
#endif

inline void random_connected_permutation(ulong *f, ulong n)
// Create a random connected (indecomposable) permutation.
{
    if ( n<=3 )
    {
        for (ulong k=0; k<n; ++k)  f[k] = k;
        if ( n<2 )  return;   // [] or [0]
        swap2(f[0], f[n-1]);
        if ( n==2 )  return;  // [1,0]
        // here: [2,1,0]
        const ulong i = rand_idx(3);
        swap2(f[1], f[i]);
        // i = 0  ==>  [1,2,0]
        // i = 1  ==>  [2,1,0]
        // i = 2  ==>  [2,0,1]
        return;
    }


#if RCP_VERSION == 1

    // will repeat with probability 2/n:
    for (ulong k=0; k<n; ++k)  f[k] = k;
    do  { random_permute(f, n); }  while ( ! is_connected(f, n) );

#else  // RCP_VERSION == 2

    // will repeat with probability 2/n^2:
    do
    {
        for (ulong k=0; k<n; ++k)  f[k] = k;

        while ( 1 )
        {
            const ulong i0 = 1 + rand_idx(n-1);  // first element must move
            const ulong i1 = 1 + rand_idx(n-1);  // f[1] will be last element
            swap2( f[0], f[i0] );
            swap2( f[1], f[i1] );
            if ( f[1]==n-1 )  // undo swap and repeat (here: f[0]!=0)
            {
                swap2( f[1], f[i1] );
                swap2( f[0], f[i0] );
                continue;   // probability 1/n but work only O(1)
            }
            else  break;
        }
//        jjassert( f[0]!=0 );

        swap2(f[1], f[n-1]);  // move f[1] to last
        // here:  f[0] != 0  and  f[n-1] != n-1
        random_permute(f+1, n-2);  // permute 2nd ... 2nd last element
    }
    while ( ! is_connected(f, n) );

#endif  // RCP_VERSION
}
// -------------------------

#undef RCP_VERSION


#endif  // !defined HAVE_PERMRAND_CONNECTED_H__
