#if !defined HAVE_MIXEDRADIX_SUBSET_LEXREV_H__
#define      HAVE_MIXEDRADIX_SUBSET_LEXREV_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"

#define MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS  // default on

class mixedradix_subset_lexrev
// Mixed radix numbers in subset-lexrev order.
// Successive numbers differ in at most three digits.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong n_;   // Number of digits (n kinds of elements in multiset)
    ulong tr_;  // aux: current track
#ifndef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
    ulong *a_;  // digits of mixed radix number (multiplicity of kind k in subset).
    ulong *m1_;  // nines (radix minus one) for each digit (multiplicity of kind k in superset).
#else
    ulong a_[64];
    ulong m1_[64];
#endif

private:  // have pointer data
    mixedradix_subset_lexrev(const mixedradix_subset_lexrev&);  // forbidden
    mixedradix_subset_lexrev & operator = (const mixedradix_subset_lexrev&);  // forbidden

public:
    explicit mixedradix_subset_lexrev(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        bool z = ( n_ == 0 );
#ifndef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
        a_ = new ulong[n_ + 1 + z];
        m1_ = new ulong[n_ + z];
#endif
        a_[n_] = 1;  // sentinel to stop scan to the right

        if ( z )  // n==0 treated as 1-digit number with radix 1
        {
            a_[0] = 0;
            a_[1] = 1;  // !=0
            m1_[0] = 0;  // <= a[0]
        }
        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_subset_lexrev()
    {
#ifndef MIXEDRADIX_SUBSET_LEXREV_FIXARRAYS
        delete [] a_;
        delete [] m1_;
#endif
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = (n_ ? n_-1 : 0);
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        a_[0] = m1_[0];
        tr_ = 0;
    }

    bool next()
    // Generate next.
    // Return false if current was last.
    {
        ulong j = tr_;
        if ( a_[j] < m1_[j] )  // easy case: can increment
        {
            a_[j] += 1;
            return true;
        }

        // here a_[j] == m1_[j]
        if ( j != 0 )  // semi-easy case: move track to the left
        {
            --j;
            a_[j] = 1;
            tr_ = j;
            return true;
        }

        a_[j] = 0;

        // find first nonzero digit to the right:
        ++j;
        while ( a_[j] == 0 )  { ++j; }  // may read sentinel a[n]

        if ( j >= n_ )  return false;  // current is last

        a_[j] -= 1;  // decrement digit to the right
        --j;
        a_[j] = 1;
        tr_ = j;
        return true;
    }

    bool prev()
    // Generate previous.
    // Return false if current was first.
    // Loopless algorithm.
    {
        ulong j = tr_;
        if ( a_[j] > 1 )  // easy case: just decrement
        {
            a_[j] -= 1;
            return true;
        }

        a_[j] = 0;
        ++j;  // now looking at next track to the right

        if ( j >= n_ )  // was on rightmost track (last two steps)
        {
            bool q = ( a_[j] != 0 );
            a_[j] = 0;
            return q;
        }

        if ( a_[j] == m1_[j] )  // semi-easy case: move track to left
        {
            tr_ = j;  // move track one right
            return true;
        }
        else
        {
            a_[j] += 1;  // increment digit to the right
            j = 0;
            a_[j] = m1_[j];  // set leftmost digit = nine
            tr_ = j;  // move to leftmost track
            return true;
        }
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_SUBSET_LEXREV_H__
