#if !defined HAVE_REVBINPERMUTE_H__
#define      HAVE_REVBINPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/shortrevbinpermute.h"
#include "bits/revbin-upd.h"
#include "bits/revbin.h"
#include "bits/bit2pow.h"
#include "aux0/swap.h"
#include "fxttypes.h"


// Tuning parameters:
#define  RBP_SYMM  4  // amount of symmetry used: 1, 2, 4 (default is 4)
#define  FAST_REVBIN  // define if using revbin(x, ldn) is faster than updating

#define  idx_swap(k, r)  { ulong kx=(k), rx=(r);  swap2(f[kx], f[rx]); }

template <typename Type>
void revbin_permute(Type *f, ulong n)
{
    if ( n<=64 )
    {
        revbin_permute_leq_64(f, n);
        return;
    }

#ifdef FAST_REVBIN
    const ulong ldn = ld(n);
#endif

    const ulong nh = (n>>1);

#if  ( RBP_SYMM >= 2 )
    const ulong n1  = n - 1;    // = 11111111
#if  ( RBP_SYMM >= 4 )
    const ulong nx1 = nh - 2;   // = 01111110
    const ulong nx2 = n1 - nx1;  // = 10111101
#endif  //  ( RBP_SYMM >= 4 )
#endif  //  ( RBP_SYMM >= 2 )

    ulong k = 0,  r = 0;
    while ( k < (n/RBP_SYMM)  )  // n>=16, n/2>=8, n/4>=4
    {
        // ----- k%4 == 0:
        if ( r>k )
        {
            idx_swap(k, r);  // <nh, <nh 11
#if  ( RBP_SYMM >= 2 )
            idx_swap(n1^k, n1^r);  // >nh, >nh 00
#if  ( RBP_SYMM >= 4 )
            idx_swap(nx1^k, nx1^r);  // <nh, <nh 11
            idx_swap(nx2^k, nx2^r);  // >nh, >nh 00
#endif  //  ( RBP_SYMM >= 4 )
#endif  //  ( RBP_SYMM >= 2 )
        }

        ++k;
        r ^= nh;

        // ----- k%4 == 1:
        if ( r>k )
        {
            idx_swap(k, r);  // <nh, >nh 10
#if  ( RBP_SYMM >= 4 )
            idx_swap(n1^k, n1^r);  // >nh, <nh 01
#endif  //  ( RBP_SYMM >= 4 )
        }

        ++k;
#ifdef FAST_REVBIN
        r = revbin(k, ldn);
#else
        r = revbin_upd(r, nh);
#endif

        // ----- k%4 == 2:
        if ( r>k )
        {
            idx_swap(k, r);  // <nh, <nh 11
#if  ( RBP_SYMM >= 2 )
            idx_swap(n1^k, n1^r);  // >nh, >nh 00
#endif  //  ( RBP_SYMM >= 2 )
        }

        ++k;
        r ^= nh;

        // ----- k%4 == 3:
        if ( r>k )
        {
            idx_swap(k, r);    // <nh, >nh 10
#if  ( RBP_SYMM >= 4 )
            idx_swap(nx1^k, nx1^r);   // <nh, >nh 10
#endif  //  ( RBP_SYMM >= 4 )
        }

        ++k;
#ifdef FAST_REVBIN
        r = revbin(k, ldn);
#else
        r = revbin_upd(r, nh);
#endif
    }
}
// -------------------------

#undef  idx_swap
#undef  RBP_SYMM
#undef  FAST_REVBIN


#endif  // !defined HAVE_REVBINPERMUTE_H__
