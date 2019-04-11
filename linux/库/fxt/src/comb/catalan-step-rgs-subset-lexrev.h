#if !defined HAVE_CATALAN_STEP_RGS_SUBSET_LEXREV_H__
#define      HAVE_CATALAN_STEP_RGS_SUBSET_LEXREV_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-catalan-step-rgs.h"
#include "comb/print-catalan-step-rgs-aa.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

#define CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS  // default on

class catalan_step_rgs_subset_lexrev
// Catalan step RGS (restricted growth strings), subset-lexrev order.
// RGS are a[] such that a[k] >= a[k-1] (weakly ascending) and a[k]<=k.
// The RGS describe lattice paths from (0,0) to (n,n) with steps
// (+1,0) and (+1,+1) that do not go below the diagonal.
// Same as: rising factorial numbers where the digits are sorted.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
#ifndef CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS
    ulong *a_;  // RGS
#else
    ulong a_[64];
#endif
    ulong n2_;  // aux: min(n,2).
    ulong tr_;  // aux: track we are looking at
    ulong n_;   // length of RGS

private:  // have pointer data
    catalan_step_rgs_subset_lexrev(const catalan_step_rgs_subset_lexrev&);  // forbidden
    catalan_step_rgs_subset_lexrev & operator = (const catalan_step_rgs_subset_lexrev&);  // forbidden

public:
    explicit catalan_step_rgs_subset_lexrev(ulong n)
    {
        n_ = n;
        n2_ = (n>=2 ? n : 2);   // make things work with n<=1
#ifndef CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS
        a_ = new ulong[n2_+1];
#endif
        a_[0] = 0;
        a_[n2_] = n2_;  // sentinel
        // layout of a[]:
        // [0, 1, 2, 3, ..., n-1, n ]  index
        // [0, *, *, *, ...,  *,  n ]  value

        first();
    }

    ~catalan_step_rgs_subset_lexrev()
    {
#ifndef CATALAN_STEP_RGS_SUBSET_LEXREV_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=1; k<n2_; ++k)  a_[k] = 0;
        tr_ =  n2_ - 1;
        if ( n_ <= 1 )
        {
            tr_ = 1;
            a_[1] = 1;
        }
    }

//    void last()
//    {
//        for (ulong k=1; k<n2_; ++k)  a_[k] = 1;
//        tr_ =  n2_ - 1;
//        if ( n_ <= 1 )
//        {
//            tr_ = 1;
//            a_[1] = 0;
//        }
//    }

    ulong next()
    // Return position of *rightmost* change (1,...,n-1).
    // Return zero if current RGS is last.
    // Either one digit is changed, or the range T0, ..., T1 where
    // T0 is the return value of the last call to next() and
    // T1 the return value of the current call to next().
    {
        const ulong a0 = a_[tr_];

        if ( a0 < a_[tr_+1] )  // may read sentinel
        {
            if ( a0 < tr_ )  // can increment
            {
                a_[tr_] = a0 + 1;
                return tr_;
            }
        }

        if ( tr_ != 1 )  // can move left and increment (from 0 to 1)
        {
            --tr_;
            a_[tr_] = 1;
            return tr_;
        }

        // remove ones:
        ulong j = tr_;
        do  { a_[j] = 0; }  while ( a_[++j] == 1 );

        if ( j==n2_ )  return 0;  // current was last

        // decrement first value != 1:
        ulong aj = a_[j] - 1;
        a_[j] = aj;

        // move left and restore the 1:
        tr_ = j - 1;
        a_[tr_] = 1;
        return j;  // rightmost change at j==tr+1
    }

//    ulong prev()
//    {
//        const ulong a0 = a_[tr_];
//        if ( a0 == 0 )   return 0;  // current is first
//        const ulong a1 = a_[tr_+1];
//    }


    void print(const char *bla, bool dfz)  const
    { print_vec(bla, a_, n_, dfz); }

    void print_aa()  const  // ASCII art
    { catalan_step_rgs_print_aa(data(), n_); }

    bool OK()  const
    {  return is_catalan_step_rgs(data(), n_); }
};
// -------------------------


#endif  // !defined HAVE_CATALAN_STEP_RGS_SUBSET_LEXREV_H__
