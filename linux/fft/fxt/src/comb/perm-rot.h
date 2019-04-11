#if !defined HAVE_PERM_ROT_H__
#define      HAVE_PERM_ROT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "perm/rotate.h"
#include "perm/reverse.h"
#include "perm/permcomplement.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_rot
// All permutations, by rotations (cyclic shifts).
// Algorithm of G. G. Langdon Jr., as given by Knuth.
// Array x[] unused here (commented out)!
{
public:
    ulong *a_;  // permutation of n elements
    ulong n_;   // Number of elements
//    ulong *x_;  // unused here

private:  // have pointer data
    perm_rot(const perm_rot&);  // forbidden
    perm_rot & operator = (const perm_rot&);  // forbidden

public:
    explicit perm_rot(ulong n)
        : n_(n)
    {
//        x_ = new ulong[n_];
        a_ = new ulong[n_];
        first();
    }

    ~perm_rot()
    {
//        delete [] x_;
        delete [] a_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = k;
//        for (ulong k=0; k<n_; ++k)  x_[k] = k;
    }

    bool next()
    {
        ulong k = n_;
        do
        {
            ulong a0 = a_[0];
            ulong k1 = k - 1;
            for (ulong j=0; j<k1; ++j)  a_[j] = a_[j+1];
            a_[k1] = a0;

//            if ( a_[k1] != x_[k1] )  break;
            if ( a_[k1] != k1 )  break;
        }
        while ( 0 != --k );

        return  ( k!=0 );
    }


    const ulong * data()  const  { return a_; }

    void goto_ffact(const ulong *d)
    // Goto permutation corresponding to d[] (i.e. unrank d[]).
    // d[] must be a valid (falling) factorial mixed radix string.
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = k;
        for (ulong k=n_-1, j=2;  k!=0;  --k, ++j)  rotate_right(a_+k-1, j, d[k-1]);
        reverse(a_, n_);
        make_complement(a_, a_, n_);
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_ROT_H__
