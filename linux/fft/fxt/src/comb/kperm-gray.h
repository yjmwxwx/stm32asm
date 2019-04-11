#if !defined  HAVE_KPERM_GRAY_H__
#define       HAVE_KPERM_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class kperm_gray
// Gray code for k-permutations of n elements.
// Same as: k-prefixes of permutations of n elements.
// Same as: arrangements of k out of n elements.
// CAT algorithm based on mixed radix Gray code
//   for the factorial number system (falling base).
{
public:
    ulong *d_;  // mixed radix digits with radix = [n-1, n-2, ..., 2]
    ulong *i_;  // directions
    ulong *ix_; // permutation (inverse perms in Trotter's order)
    ulong *x_;  // inverse permutation (perms in Trotter's order)
    ulong n_;   // total of n elements
    ulong k_;   // permutations of k elements
    ulong sw1_, sw2_;  // indices of elements swapped most recently

private:  // have pointer data
    kperm_gray(const kperm_gray&);  // forbidden
    kperm_gray & operator = (const kperm_gray&);  // forbidden

public:
    explicit kperm_gray(ulong n)
    {
        n_ = n;
        k_ = n;
        d_ = new ulong[n_];
        d_[n-1] = -1UL;  // sentinel
        i_ = new ulong[n_];
        x_ = new ulong[n_];
        ix_ = new ulong[n_];
        i_[n_-1] = 0;
        first(n_);
    }

    ~kperm_gray()
    {
        delete [] i_;
        delete [] d_;
        delete [] x_;
        delete [] ix_;
    }

    const ulong * data()  const  { return ix_; }
    const ulong * invdata()  const  { return x_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }


    void first(ulong k)
    {
        k_ = k;
        for (ulong j=0; j<n_-1; ++j)  d_[j] = 0;
        for (ulong j=0; j<n_-1; ++j)  i_[j] = +1;
        for (ulong j=0; j<n_; ++j)  x_[j] = ix_[j] = j;
        sw1_=n_-1;  sw2_=n_-2;
    }

//    void last(ulong k)
//    {
//        first(k);  // k_ is set with call
//        d_[n_-2] = 1;
//        swap2(x_[n_-1], x_[n_-2]);
//        swap2(ix_[n_-1], ix_[n_-2]);
//        for (ulong j=0; j<n_-2; ++j)  i_[j] = -1UL;
//        i_[n_-2] = +1;
//    }

private:
    void swap(ulong j, ulong im)
    {
        const ulong x1 = j;        // element j
        const ulong i1 = ix_[x1];  // position of j
        const ulong i2 = i1 + im;  // neighbor
        const ulong x2 = x_[i2];   // position of neighbor
        x_[i1] = x2;   x_[i2] = x1;   // swap2(x_[i1], x_[i2]);
        ix_[x1] = i2;  ix_[x2] = i1;  // swap2(ix_[x1], ix_[x2]);
        sw1_=i1;  sw2_=i2;
    }

public:
    bool next()
    {
        ulong j = 0;
        ulong m1 = n_ - 1;  // nine in falling factorial base
        ulong ij;
        while ( (ij=i_[j]) )
        {
            ulong im = i_[j];
            ulong dj = d_[j] + im;
            if ( dj>m1 )  // =^= if ( (dj>m1) || ((long)dj<0) )
            {
                i_[j] = -ij;
            }
            else
            {
                d_[j] = dj;
                swap(j, im);
                return true;
            }

            --m1;
            ++j;
            if ( j>=k_ )  return false;
        }
        return false;
    }

//    bool prev()
//    {
//        ulong j = 0;
//        ulong m1 = n_ - 1;
//        ulong ij;
//        while ( (ij=i_[j]) )
//        {
//            ulong im = -i_[j];
//            ulong dj = d_[j] + im;
//            if ( dj>m1 )  // =^= if ( (dj>m1) || ((long)dj<0) )
//            {
//                i_[j] = -ij;
//            }
//            else
//            {
//                d_[j] = dj;
//                swap(j, im);
//                return true;
//            }
//
//            --m1;
//            ++j;
//            if ( j>=k_ )  return false;
//        }
//        return false;
//    }

public:
    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), k_, dfz); }

//    void print_inv(const char *bla, bool dfz=false)  const
//    // If dfz is true then Dots are printed For Zeros.
//    { print_perm(bla, invdata(), n_, dfz); }
};
// -------------------------

#endif  // !defined HAVE_KPERM_GRAY_H__
