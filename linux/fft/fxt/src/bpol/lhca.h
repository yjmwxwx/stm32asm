#if !defined  HAVE_LHCA_H__
#define       HAVE_LHCA_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// bpol/lhcarule-minweight.cc:
extern const ulong minweight_lhca_rule[];


inline ulong lhca_next(ulong x, ulong r, ulong m)
// LHCA := (1-dim) Linear Hybrid Cellular Automaton.
// Return next state (after x) of the LHCA with
// rule (defined by) r:
//   Rule 150 is applied for cells where r is one, rule 90 else.
//   Rule 150 :=  next(x) = x + leftbit(x) + rightbit(x)
//   Rule 90  :=  next(x) = leftbit(x) + rightbit(x)
// Length defined by m:
//   m has to be a burst of the n lowest bits (n: length of automaton)
{
    r &= x;
    ulong t = (x>>1) ^ (x<<1);
    t ^= r;
    t &= m;
    return  t;
}
// -------------------------


inline ulong lhca2poly(ulong r, ulong n)
// Return binary polynomial p that corresponds to the length-n LHCA rule r.
// The returned polynomial p has degree n.
//
// If r gives maximal period then p is primitive.
//
// Algorithm:
//  Let r=[r(n-1),...,r(2),r(1),r(0)]
//  Initialize: p2=0, p1=1
//  Iterate for k=0...n-1: {p1, p2} = { (x+r)*p1+p2 ,p1}
{
    ulong p2 = 0,  p1 = 1;
    while ( n-- )
    {
        ulong m = r & 1;
        r >>= 1;
        ulong p = (p1<<1) ^ p2;
        if ( m )  p ^= p1;
        p2 = p1;  p1 = p;
    }
    return  p1;
}
// -------------------------

// bpol/bitpol2lhca.cc:
ulong poly2lhca(ulong p);



#endif  // !defined HAVE_LHCA_H__
