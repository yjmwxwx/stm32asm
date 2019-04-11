#if !defined  HAVE_PERM_COLEX_H__
#define       HAVE_PERM_COLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


#define PERM_COLEX_FIXARRAYS  // use arrays instead of pointers (speedup)

class perm_colex
// Permutations in co-lexicographic (colex) order.
// Generation via rising factorial numbers.
{
public:
#ifndef PERM_COLEX_FIXARRAYS
    ulong *d_;  // mixed radix digits with radix = [2, 3, 4, ...]
    ulong *x_;  // permutation
#else
    ulong d_[32];
    ulong x_[32];
#endif
    ulong n_;   // permutations of n elements

private:  // have pointer data
    perm_colex(const perm_colex&);  // forbidden
    perm_colex & operator = (const perm_colex&);  // forbidden

public:
    explicit perm_colex(ulong n)
    // Must have n>=2
    {
        n_ = n;
#ifndef PERM_COLEX_FIXARRAYS
        d_ = new ulong[n_];
        x_ = new ulong[n_];
#endif
        d_[n-1] = 0;  // sentinel
        first();
    }

    ~perm_colex()
    {
#ifndef PERM_COLEX_FIXARRAYS
        delete [] d_;
        delete [] x_;
#endif
    }

    const ulong * data()  const  { return x_; }


    void first()
    {
//        for (ulong k=0; k<n_; ++k)  x_[k] = k;  // ==> reversed order
        for (ulong k=0; k<n_; ++k)  x_[k] = n_-1-k;
        for (ulong k=0; k<n_-1; ++k)  d_[k] = 0;
    }

    bool next()
    {
        if ( d_[0]==0 )  // easy case
        {
            d_[0] = 1;
            swap2(x_[0], x_[1]);
            return true;
        }
        else
        {
            d_[0] = 0;
            ulong j = 1;
            ulong m1 = 2;  // nine in rising factorial base
            while ( d_[j]==m1 )
            {
                d_[j] = 0;
                ++m1;
                ++j;
            }

            if ( j==n_-1 )  return false;  // current permutation is last

            const ulong dj = d_[j];
            d_[j] = dj + 1;

            swap2( x_[dj], x_[j+1] );  // swap positions dj and j+1

            {  // reverse range [0...j]:
                ulong a = 0,  b = j;
                do
                {
                    swap2(x_[a], x_[b]);
                    ++a;
                    --b;
                }
                while ( a < b );
            }

            return true;
        }
    }

public:
    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------

//#undef PERM_COLEX_FIXARRAYS


#endif  // !defined HAVE_PERM_COLEX_H__
