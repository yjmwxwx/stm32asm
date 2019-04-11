#if !defined HAVE_CATALAN_STEP_RGS_LEX_H__
#define      HAVE_CATALAN_STEP_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-catalan-step-rgs.h"
#include "comb/print-catalan-step-rgs-aa.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


class catalan_step_rgs_lex
// Catalan step RGS (restricted growth strings), lexicographic order.
// The RGS are a[] such that a[k] >= a[k-1] (weakly ascending) and a[k]<=k.
// The RGS describe lattice paths from (0,0) to (n,n) with steps
// (+1,0) and (+1,+1) that do not go below the diagonal.
// Same as: rising factorial numbers where the digits are sorted.
// Cf. OEIS sequence A000108.
{
public:
    ulong *a_;  // RGS
    ulong n_;   // length of the RGS.

private:  // have pointer data
    catalan_step_rgs_lex(const catalan_step_rgs_lex&);  // forbidden
    catalan_step_rgs_lex & operator = (const catalan_step_rgs_lex&);  // forbidden

public:
    explicit catalan_step_rgs_lex(ulong n)
    {
        n_ = (n ? n : 1);  // make things work for n==0

        a_ = new ulong[n_+3];
        a_[0] = 0;  // sentinel for scan
        ++a_;  // nota bene
        a_[0] = 0;    // never written to
        a_[n_] = n;   // never written to // note n, not n_
        // layout of a[]:
        // [  -1,       0, 1, 2, 3, ..., n-1, n ]  index
        // [sentinel=0, 0, *, *, *, ...,  *,  n ]  value

        first();
    }

    ~catalan_step_rgs_lex()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_; }

    void first()
    { for (ulong k=1; k<n_; ++k)  a_[k] = 0; }

    void last()
    { for (ulong k=1; k<n_; ++k)  a_[k] = k; }

    ulong next()
    // Return position of leftmost change (1,...,n-1).
    // Return zero if current RGS is last.
    {
        ulong j = n_ - 1;
#if 1  // easy case optimization (great speedup)
        if ( a_[j] < j )
        {
            a_[j] += 1;
            return j;
        }
#endif
        while ( a_[j] == j )  --j;  // can read sentinel

        if ( j == -1UL )  return 0;  // current is last

        const ulong a1 = a_[j] + 1;
        for (ulong i=j; i<n_; ++i)  a_[i] = a1;

        return j;
    }

    ulong prev()
    // Return position of leftmost change (1,...,n).
    // Return zero if current RGS is last.
    {
        ulong j = n_ - 1;
        ulong a0 = a_[j];
        if ( a0 == 0 )  return 0;  // current is first
        while ( a_[j-1] == a0 )
        {
            a_[j] = j;
            --j;
        }
        --a_[j];
        return j;
    }

    void print(const char *bla, bool dfz)  const
    { print_vec(bla, a_, n_, dfz); }

    void print_aa()  const  // ASCII art
    { catalan_step_rgs_print_aa(data(), n_); }

    bool OK()  const
    {  return is_catalan_step_rgs(data(), n_); }
};
// -------------------------


#endif  // !defined HAVE_CATALAN_STEP_RGS_LEX_H__
