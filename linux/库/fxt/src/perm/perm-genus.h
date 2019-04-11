#if !defined  HAVE_PERM_GENUS_H__
#define       HAVE_PERM_GENUS_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/bitarray.h"
#include "perm/permq.h"  // count_cycles()

#include "fxttypes.h"

//#include "jjassert.h"


inline ulong perm_genus(const ulong *p, ulong n,  // permutation and length
                        ulong *cpi,  // scratch space for rotated inverse permutation
                        bitarray *B=0)
// The genus g(P) of a permutation P of [1,2,...,n] is defined by
// g(P)=(1/2)*(n+1-Z(P)-Z(C P')), where P' is the inverse permutation of P,
// C = [2,3,4,...,n,1] = (1,2,...,n)  (cyclic shift),
// and Z(P) is the number of cycles of the permutation P.
// (taken from http://oeis.org/A177267)
{
    const ulong zp = count_cycles(p, n, B);

#if 1  // better interface: no parameter pi[]
    // rotated inverse permutation directly from permutation p[]:
    for (ulong j=0; j<n; ++j)
    {
        ulong t = p[j];
        if ( t==0 )  t = n;  // could save this with one extra element
        cpi[t-1] = j;
    }
#else  // old interface: parameter pi[] required
    // rotated inverse permutation from inverse permutation pi[]:
    for (ulong j=1; j<n; ++j)  cpi[j-1] = pi[j];
    cpi[n-1] = pi[0];
#endif

    const ulong zcpi = count_cycles(cpi, n, B);

//    jjassert( 0==( (n + 1 - zp - zcpi) & 1 )  );
    const ulong gen = (n + 1 - zp - zcpi) / 2;
//    jjassert( gen <= (n+1)/2 );

    return gen;
}
// -------------------------


inline void genus0_perm_to_paren(const ulong *p, ulong n,
                                 char *c, const char s[2]="1.")
// For a permutation p[] of genus zero, write the corresponding
// parenthesis string into c[] (which must have 2*n elements).
// Permutations of genus 0 can be identified with noncrossing set partitions.
// s[0] is used for "open paren", s[1] for "close paren".
// For example, the strings for the 4-permutations with genus-0 are
//
//   #:      perm      genus  cycles            bits      parens
//   0:    [ . 1 2 3 ]  0   (0) (1) (2) (3)   1.1.1.1.   ()()()()
//   1:    [ . 1 3 2 ]  0   (0) (1) (2, 3)    1.1.11..   ()()(())
//   2:    [ . 2 1 3 ]  0   (0) (1, 2) (3)    1.11..1.   ()(())()
//   3:    [ . 2 3 1 ]  0   (0) (1, 2, 3)     1.11.1..   ()(()())
//   4:    [ . 3 1 2 ]  1   (0) (1, 3, 2)
//   5:    [ . 3 2 1 ]  0   (0) (1, 3) (2)    1.111...   ()((()))
//   6:    [ 1 . 2 3 ]  0   (0, 1) (2) (3)    11..1.1.   (())()()
//   7:    [ 1 . 3 2 ]  0   (0, 1) (2, 3)     11..11..   (())(())
//   8:    [ 1 2 . 3 ]  0   (0, 1, 2) (3)     11.1..1.   (()())()
//   9:    [ 1 2 3 . ]  0   (0, 1, 2, 3)      11.1.1..   (()()())
//  10:    [ 1 3 . 2 ]  1   (0, 1, 3, 2)
//  11:    [ 1 3 2 . ]  0   (0, 1, 3) (2)     11.11...   (()(()))
//  12:    [ 2 . 1 3 ]  1   (0, 2, 1) (3)
//  13:    [ 2 . 3 1 ]  1   (0, 2, 3, 1)
//  14:    [ 2 1 . 3 ]  0   (0, 2) (1) (3)    111...1.   ((()))()
//  15:    [ 2 1 3 . ]  0   (0, 2, 3) (1)     111..1..   ((())())
//  16:    [ 2 3 . 1 ]  1   (0, 2) (1, 3)
//  17:    [ 2 3 1 . ]  1   (0, 2, 1, 3)
//  18:    [ 3 . 1 2 ]  1   (0, 3, 2, 1)
//  19:    [ 3 . 2 1 ]  1   (0, 3, 1) (2)
//  20:    [ 3 1 . 2 ]  1   (0, 3, 2) (1)
//  21:    [ 3 1 2 . ]  0   (0, 3) (1) (2)    111.1...   ((()()))
//  22:    [ 3 2 . 1 ]  1   (0, 3, 1, 2)
//  23:    [ 3 2 1 . ]  0   (0, 3) (1, 2)     1111....   (((())))
//
// In fact, every partition is converted to a valid parenthesis string
// (so this routine gives a projection).
{
    for (ulong j=0; j<2*n; ++j)  c[j] = s[0];  // set all to "open paren"

    ulong cpos = 0;
    for (ulong j=0; j<n; ++j)
    {
        const ulong pj = p[j];

        if ( pj <= j )  // end of a cycle here
            c[cpos+1] = s[1];
        else          // leave place for included cycle(s)
            c[cpos + 2*(pj-j)] = s[1];

        cpos += 2;
    }
}
// -------------------------



#endif  // !defined HAVE_PERM_GENUS_H__
