#if !defined HAVE_COMPOSITION_RANK_H__
#define      HAVE_COMPOSITION_RANK_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/num-compositions.h"  // class num_compositions

#include "fxttypes.h"
//#include "jjassert.h"
//#include "aux0/binomial.h"



class composition_rank : public num_compositions
// Ranking and unranking compositions in
//   lexicographic, minimal-change, or enup (two-close) order.
// The routines rank_*(x,n,k) have complexity k*k.
// The routines unrank_*(x,n,k) have complexity k * X
//   where X is the complexity of unrank_get_el();
//   X=n as given but can be reduced to log(n).
// Note: the two-close order corresponds to the enup order for combinations.
{
public:
    // no data

public:
    explicit composition_rank(ulong n, ulong k)
        : num_compositions(n, k)
    { ; }

    ~composition_rank()
    { ; }


    bool is_comp(const ulong *x, ulong n, ulong k)  const
    // Return whether x contains a k-composition of n
    {
        ulong s = 0;
        for (ulong j=0; j<k; ++j)  s += x[j];
        return  (s==n);
    }

    ulong rank_lex(const ulong *x, ulong n, ulong k)  const
    // Return rank of k-composition of n for lex order
    //  0 <= rank < binomial(n+k-1, n)
    {
        if ( 1==k )  return 0;
        ulong r = 0;
        ulong xk = x[k-1];
        for (ulong j=1; j<=xk; ++j)  r += num_comp(n+1-j, k-1);
        r += rank_lex(x, n-xk, k-1);  // recurse
        return r;
    }


    ulong rank_gray(const ulong *x, ulong n, ulong k)  const
    // Return rank of k-composition of n for minimal-change order
    //  0 <= rank < binomial(n+k-1, n)
    {
        if ( 1==k )  return 0;
        ulong r = 0;
        ulong xk = x[k-1];
        for (ulong j=1; j<=xk; ++j)  r += num_comp(n+1-j, k-1);
        // recurse:
        ulong ri = rank_gray(x, n-xk, k-1);
        if ( xk&1 )  r += num_comp(n-xk, k-1)-1 - ri;
        else         r += ri;
        return r;
    }

    ulong rank_enup_rev(const ulong *x, ulong n, ulong k)  const
    // Return rank of k-composition of n for reversed enup (two-close) order
    //  0 <= rank < binomial(n+k-1, n)
    {
        if ( 1==k )  return 0;
        ulong r = 0;
        ulong xk = x[k-1];
        for (ulong j=1; j<=xk; ++j)  r += num_comp(n+1-j, k-1);
        // recurse:
        ulong ri = rank_enup_rev(x, n-xk, k-1);
        if ( !(xk&1) )  r += num_comp(n-xk, k-1)-1 - ri;
        else            r += ri;
        return  r;
    }

    ulong rank_enup(const ulong *x, ulong n, ulong k)  const
    // Return rank of k-composition of n for enup (two-close) order
    //  0 <= rank < binomial(n+k-1, n)
    {
        return  num_comp(n, k) - 1 - rank_enup_rev(x, n, k);
    }


    ulong unrank_get_el(ulong n, ulong k, ulong &r)  const
    // Get last element of the rank-r k-composition of n
    // Rank r is modified.
    // Must have:  r < binomial(n+k-1,n)
    // Used in all unranking routines.
    // Complexity is n, could be reduced to log(n)
    //   via cumulative values and binary search.
    {
        if ( 1==k )  { r=0; return n; }
//        jjassert( r<num_comp(n, k) );  // else out of range
        for (ulong xk=0; xk<=n; ++xk)
        {
            ulong nc = num_comp(n-xk, k-1);
            if ( nc > r )   return xk;
            r -= nc;
        }

        return  0;  // not reached
    }

    void unrank_lex(ulong *x, ulong n, ulong k, ulong r)  const
    // Write the lex order rank-r k-composition of n into x[]
    // Must have:  r < binomial(n+k-1,n)
    {
        ulong j = k;
        while ( j-- )
        {
            ulong xj = unrank_get_el(n, j+1, r);  // r modified
            x[j] = xj;
            n -= xj;
        }
    }

    void unrank_gray(ulong *x, ulong n, ulong k, ulong r)  const
    // Write the minimal-change order rank-r k-composition of n into x[]
    // Must have:  r < binomial(n+k-1,n)
    {
        for (ulong j=k-1; j!=0; --j)
        {
            ulong xj = unrank_get_el(n, j+1, r);  // r modified
            if ( xj & 1 )  r = num_comp(n-xj, j) -1 -r;
            x[j] = xj;
            n -= xj;
        }
        x[0] = n;
    }

    void unrank_enup(ulong *x, ulong n, ulong k, ulong r)  const
    // Write the enup (two-close) order rank-r k-composition of n into x[]
    // Must have:  r < binomial(n+k-1,n)
    {
        r = num_comp(n, k) -1 -r;
        for (ulong j=k-1; j!=0; --j)
        {
            ulong xj = unrank_get_el(n, j+1, r);  // r modified
            if ( !(xj & 1) )  r = num_comp(n-xj, j) -1 -r;
            x[j] = xj;
            n -= xj;
        }
        x[0] = n;
    }

    void print(const char *bla, const ulong *x, ulong k)  const;
    void print_deltaset(const char *bla, const ulong *x, ulong k)  const;
    void print_deltaset_num(const char *bla, const ulong *x, ulong k)  const;
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_RANK_H__
