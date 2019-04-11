#if !defined HAVE_CATALAN_STEP_RGS_COLEX_H__
#define      HAVE_CATALAN_STEP_RGS_COLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-catalan-step-rgs.h"
#include "comb/print-catalan-step-rgs-aa.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


class catalan_step_rgs_colex
// Catalan step RGS (restricted growth strings), co-lexicographic order.
// RGS are a[] such that a[k] >= a[k-1] (weakly ascending) and a[k]<=k.
// The RGS describe lattice paths from (0,0) to (n,n) with steps
// (+1,0) and (+1,+1) that do not go below the diagonal.
// Cf. OEIS sequence A000108.
{
public:
    ulong *a_;  // RGS
    ulong n_;   // length of the RGS.
    ulong tr_;  // current track (position of first non-zero element)
    // tr == n-1 for the all-zero word

private:  // have pointer data
    catalan_step_rgs_colex(const catalan_step_rgs_colex&);  // forbidden
    catalan_step_rgs_colex & operator = (const catalan_step_rgs_colex&);  // forbidden

public:
    explicit catalan_step_rgs_colex(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+2+(n_==0)];
        a_[n_] = n_;  // unchanged
        a_[1] = 0;    // sentinel for n==0
        a_[n_+1] = 0; // sentinel for n!=0
        a_[0] = 0;    // read-only
        // layout of a[]:
        // [ 0, 1, 2, 3, ..., n-1, n, n+1 ]  index
        // [ 0, *, *, *, ...,  *,  n,  0  ]  value

        first();
    }

    ~catalan_step_rgs_colex()
    { delete [] a_; }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=1; k<n_; ++k)  a_[k] = 0;
        tr_ = (n_ ? n_ : 1);
    }

    void last()
    {
        for (ulong k=1; k<n_; ++k)  a_[k] = k;
        tr_ = 1;
    }

    ulong next()
    // Return position of *rightmost* change (1,...,n-1).
    // Return zero if current RGS is last.
    {
#if 1  // easy case: can prepend 1 (very frequent, great speedup)
        --tr_;
        if ( tr_ != 0 )
        {
            a_[tr_] = 1;
            return tr_;
        }
#endif
        ulong j = 1;
        while ( a_[j] == j )
        {
            a_[j] = 0;
            ++j;
        }
        if ( j >= n_ )  return 0;  // current is last

        const ulong w = a_[j];

        while ( a_[j] == w )
        {
            a_[j] = 0;
            ++j;
        }
        --j;

        a_[j] = w + 1;
        tr_ = j;

        return tr_;
    }

    ulong prev()
    // Return position of *leftmost* change (1,...,n-1).
    // Return zero if current RGS is last.
    {
#if 1  // easy case: can remove 1 (very frequent, great speedup)
        ulong z = a_[tr_];
        if ( z==1 )
        {
            a_[tr_] = 0;
            if ( tr_+1 < n_ )  ++tr_;
            return tr_;
        }
#endif

        if ( z==0 )  return 0;  // current is first

        --z;
        ulong j = tr_;
        // write digits z:
        do  { a_[j] = z; }  while ( --j > z );

        // write digits j:
        while ( j )  { a_[j] = j;  --j; }

        tr_ = 1;
        return tr_;
    }

    void print(const char *bla, bool dfz)  const
    { print_vec(bla, a_, n_, dfz); }

    void print_aa()  const  // ASCII art
    { catalan_step_rgs_print_aa(data(), n_); }

    bool OK()  const
    {  return is_catalan_step_rgs(data(), n_); }

};
// -------------------------


#endif  // !defined HAVE_CATALAN_STEP_RGS_COLEX_H__
