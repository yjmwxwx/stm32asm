#if !defined  HAVE_PERM_GRAY_ROT1_H__
#define       HAVE_PERM_GRAY_ROT1_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/mixedradix-gray.h"

#include "aux0/swap.h"
#include "fxttypes.h"

//#include "jjassert.h"


class perm_gray_rot1
// Gray code for permutations.
// Let e be the largest even number not greater than n:
// the e first elements in the last permutation are a cyclic shift
// to the left by one position of the first e elements.
// For example, e==6 with n==6 and n==7:
//             first                last
//  n=6:   [ 0 1 2 3 4 5 ]    [ 1 2 3 4 5 0 ]
//  n=7:   [ 0 1 2 3 4 5 6 ]  [ 1 2 3 4 5 0 6 ]
//
// CAT algorithm based on mixed radix Gray code for rising factorial base
// with last two nines swapped for odd n.
{
public:
    mixedradix_gray *M_;  // Gray code for factorial numbers
    ulong n_;   // number of elements to permute
    ulong *x_;  // current permutation (of {0, 1, ..., n-1})
    ulong *ix_;  // inverse permutation
    ulong sw1_, sw2_;  // indices of elements swapped most recently

private:  // have pointer data
    perm_gray_rot1(const perm_gray_rot1&);  // forbidden
    perm_gray_rot1 & operator = (const perm_gray_rot1&);  // forbidden

public:
    explicit perm_gray_rot1(ulong n)
    // Must have: n>=1
    {
        n_ = (n ? n : 1);  // at least one
        x_ = new ulong[n_];
        ix_ = new ulong[n_];

        M_ = new mixedradix_gray(n_-1, 1);  // rising factorial base

        // apply permutation of radix vector with mixed radix number:
        if ( (n_ >= 3) && (n & 1) )  // odd n>=3
        {
            ulong *m1 = M_->m1_;
            swap2(m1[n_-2], m1[n_-3]);  // swap last two factorial nines
//            for (ulong k=1; k<n_-1; k+=2)  swap2(m1[k-1], m1[k]);  // swap all pairs
        }

        first();
    }

    ~perm_gray_rot1()
    {
        delete [] x_;
        delete [] ix_;
        delete M_;
    }

    void first()
    {
        M_->first();
        for (ulong k=0; k<n_; ++k)  x_[k] = ix_[k] = k;
        sw1_=0;  sw2_=0;
    }

    bool next()
    {
        // Compute next mixed radix number in Gray code order:
        if ( false == M_->next() )  { first();  return false; }

        const ulong j = M_->pos();  // position of changed digit
        const ulong i1 = M_->m1_[j];  // valid for any permutation of factorial radices

        const ulong x1 = x_[i1];
        ulong  i2 = i1,  x2;
        const int d = M_->dir();    // direction of change

        if ( d>0 )  // in the inverse permutation search first smaller element left:
        {
            for (x2=x1-1;  ; --x2)  if ( (i2=ix_[x2]) < i1 )  break;
        }
        else  // in the inverse permutation search first smaller element right:
        {
            for (x2=x1+1;  ; ++x2)  if ( (i2=ix_[x2]) < i1 )  break;
        }

//        jjassert( i2+1 > 0 );
//        jjassert( i2<i1 );

        x_[i1] = x2;    x_[i2] = x1;  // swap2(x_[i1], x_[i2]);
        ix_[x1] = i2;  ix_[x2] = i1;  // swap2(ix_[x1], ix_[x2]);

        sw1_=i2;  sw2_=i1;

        return true;
    }

    const ulong * data()  const  { return x_; }
    const ulong * invdata()  const  { return ix_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_GRAY_ROT1_H__
