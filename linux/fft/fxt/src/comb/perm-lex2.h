#if !defined  HAVE_PERM_LEX2_H__
#define       HAVE_PERM_LEX2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


#define PERM_LEX2_FIXARRAYS  // use arrays instead of pointers (speedup)
#define PERM_LEX2_OPT  // define to use easy case optimization (speedup)
// Note: must have n>=2 when PERM_LEX2_OPT is defined.


class perm_lex2
// Permutations in lexicographic order.
// Generation via rising factorial numbers.
{
public:
#ifndef PERM_LEX2_FIXARRAYS
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ...]
    ulong *x_;  // permutation
#else
    ulong d_[32];
    ulong x_[32];
#endif
    ulong n_;   // permutations of n elements

private:  // have pointer data
    perm_lex2(const perm_lex2&);  // forbidden
    perm_lex2 & operator = (const perm_lex2&);  // forbidden

public:
    explicit perm_lex2(ulong n)
    // Must have n>=2 when PERM_LEX2_OPT is defined, otherwise n>=1
    {
        n_ = n;
#ifndef PERM_LEX2_FIXARRAYS
        d_ = new ulong[n_];
        x_ = new ulong[n_];
#endif
        d_[n-1] = 0;  // sentinel
        first();
    }

    ~perm_lex2()
    {
#ifndef PERM_LEX2_FIXARRAYS
        delete [] d_;
        delete [] x_;
#endif
    }

    const ulong * data()  const  { return x_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  x_[k] = k;
//        for (ulong k=0; k<n_; ++k)  x_[k] = n_-1-k;  // ==> reversed order
        for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
    }

    bool next()
    {
#ifdef PERM_LEX2_OPT
        if ( d_[0]==0 )  // easy case
        {
            d_[0] = 1;
            swap2(x_[n_-1], x_[n_-2]);
            return true;
        }
        else
        {
            d_[0] = 0;
            ulong j = 1;
            ulong m1 = 2;  // nine in falling factorial base
#else  // PERM_LEX2_OPT

            ulong j = 0;
            ulong m1 = 1;  // nine in falling factorial base
#endif  // PERM_LEX2_OPT
            while ( d_[j]==m1 )
            {
                d_[j] = 0;
                ++m1;
                ++j;
            }

            if ( j==n_-1 )  return false;  // current permutation is last

            ulong dj = d_[j];
            d_[j] = dj + 1;

            swap2( x_[n_-1-dj], x_[n_-j-2] );

            {  // reverse range [n-1-j...n-1]:
                ulong a = n_-1-j,  b = n_-1;
                while ( a<b )
                {
                    swap2(x_[a], x_[b]);
                    --b;
                    ++a;
                }
            }
            return true;
#ifdef PERM_LEX2_OPT
        }
#endif
    }

    ulong num_inversions()  const
    {
        ulong ni = 0;
        for (ulong j=0; j<n_; ++j)  ni += d_[j];
        return ni;
    }

public:
    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------

//#undef PERM_LEX2_FIXARRAYS  // better leave in
//#undef PERM_LEX2_OPT  // better leave in


#endif  // !defined HAVE_PERM_LEX2_H__
