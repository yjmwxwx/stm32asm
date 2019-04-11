#if !defined HAVE_MIXEDRADIX_SUBSET_LEX_H__
#define      HAVE_MIXEDRADIX_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_subset_lex
// Mixed radix numbers in subset-lex order.
// Successive numbers differ in at most three digits.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong n_;    // Number of digits (n kinds of elements in multiset)
    ulong tr_;   // aux: current track
    ulong *a_;   // digits of mixed radix number (multiplicity of kind k in subset).
    ulong *m1_;  // nines (radix minus one) for each digit (multiplicity of kind k in superset).

private:  // have pointer data
    mixedradix_subset_lex(const mixedradix_subset_lex&);  // forbidden
    mixedradix_subset_lex & operator = (const mixedradix_subset_lex&);  // forbidden

public:
    explicit mixedradix_subset_lex(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_+2];  // two sentinels, one left, one right
        a_[0] = 1;  a_[n_+1] = 1;
        ++a_;  // nota bene
        m1_ = new ulong[n_+2];
        m1_[0] = 0;  m1_[n_+1] = 0;  // sentinel with n==0
        ++m1_;  // nota bene

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_subset_lex()
    {
        --a_;
        delete [] a_;
        --m1_;
        delete [] m1_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        tr_ = 0;  // start by looking at leftmost (zero) digit
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        ulong n1 = ( n_ ? n_ - 1 : 0 );
        a_[n1] = m1_[n1];
        tr_ = n1;
    }

    bool next()
    // Generate next.
    // Return false if current was last.
    {
        ulong j = tr_;
        if ( a_[j] < m1_[j] )  // easy case 1: increment
        {
            a_[j] += 1;
            return true;
        }

        // here a_[j] == m1_[j]
        if ( j+1 < n_ )  // easy case 2: append (move track to the right)
        {
            ++j;
            a_[j] = 1;
            tr_ = j;
            return true;
        }

        a_[j] = 0;

        // find first nonzero digit to the left:
        --j;
        while ( a_[j] == 0 )  { --j; }  // may read sentinel a_[-1]

        if ( (long)j < 0 )  return false;  // current is last

        a_[j] -= 1;  // decrement digit to the left
        ++j;
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
        if ( a_[j] > 1 )  // easy case 1: decrement
        {
            a_[j] -= 1;
            return true;
        }
        else
        {
            if ( tr_ == 0 )
            {
                if ( a_[0] == 0 )  return false;  // current is first
                a_[0] = 0;  // now word is first (all zero)
                return true;
            }

            a_[j] = 0;

            --j;  // now looking at next track to the left
            if ( a_[j] == m1_[j] )  // easy case 2: move track to left
            {
                tr_ = j;  // move track one left
            }
            else
            {
                a_[j] += 1;  // increment digit to the left
                j = n_ - 1;
                a_[j] = m1_[j];  // set rightmost digit = nine
                tr_ = j;  // move to rightmost track
            }
            return true;
        }
    }

    ulong card()  const
    // Cardinality of current subset (sum of digits).
    {
        ulong s = 0;
        for (ulong j=0; j<n_; ++j)  s += a_[j];
        return s;
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


#endif  // !defined HAVE_MIXEDRADIX_SUBSET_LEX_H__
