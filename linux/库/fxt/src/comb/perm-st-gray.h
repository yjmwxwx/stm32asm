#if !defined  HAVE_PERM_ST_GRAY_H__
#define       HAVE_PERM_ST_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/perm-gray-rot1.h"

//#include "perm/rotate.h"
#include "aux0/swap.h"
#include "fxttypes.h"

class perm_st_gray
// Gray code for single track permutations:
// one transposition per update with odd n,
// one extra transposition once in (n-1)! updates with even n (optimal).
{
public:
    perm_gray_rot1 *G;  // underlying permutations

    ulong *x_;   // permutation
    ulong *ix_;  // inverse permutation
    ulong n_;    // number of elements
    ulong sct_;  // count cyclic shifts

private:  // have pointer data
    perm_st_gray(const perm_st_gray&);  // forbidden
    perm_st_gray & operator = (const perm_st_gray&);  // forbidden

public:
    explicit perm_st_gray(ulong n)
    // Must have n>=2
    {
        n_ = (n>=2 ? n : 2);
        G = new perm_gray_rot1(n-1);
        x_ = new ulong[n_];
        ix_ = new ulong[n_];
        first();
    }

    ~perm_st_gray()
    {
        delete [] x_;
        delete [] ix_;
        delete G;
    }

    void first()
    {
        G->first();
        for (ulong j=0; j<n_; ++j)  ix_[j] = x_[j] = j;
        sct_ = n_;
    }

private:
    void swap_elements(ulong x1, ulong x2)
    {
        const ulong i1 = ix_[x1],  i2 = ix_[x2];
        x_[i1] = x2;   x_[i2] = x1;   // swap2(x_[i1], x_[i2]);
        ix_[x1] = i2;  ix_[x2] = i1;  // swap2(ix_[x1], ix_[x2]);
    }

    void swap_positions(ulong i1, ulong i2)
    {
        const ulong x1 = x_[i1],  x2 = x_[i2];
        x_[i1] = x2;   x_[i2] = x1;   // swap2(x_[i1], x_[i2]);
        ix_[x1] = i2;  ix_[x2] = i1;  // swap2(ix_[x1], ix_[x2]);
    }

public:
    bool next()
    {
        bool q = G->next();
        if ( q )  // normal update (in underlying permutation of n-1 elements)
        {
            ulong i1, i2;  // positions of swaps
            G->get_swap(i1, i2);

            // rotate positions according to sct:
            i1 += sct_;  if ( i1>=n_ )  i1-=n_;
            i2 += sct_;  if ( i2>=n_ )  i2-=n_;

            swap_positions(i1, i2);

            return true;
        }
        else  // goto next cyclic shift (once in (n-1)! updates, n-1 times in total)
        {
            G->first();  // restart underlying permutations
            --sct_;      // adjust cyclic shift

            swap_elements(0, n_-1);

            if ( 0==(n_&1) )  // n even
            {
                // special case with perm_gray_rot1 as underlying permutation:
                if ( n_>=4 )  swap_elements(n_-2, n_-1);  // one extra transposition

                // This will give a single track order for all underlying permutations
                //  (of n-1 elements) that start with identity:
//                for (ulong j=0; j<n_; ++j)  x_[j] = ix_[j] = j;
//                rotate_left(x_, n_, n_-sct_);
//                rotate_right(ix_, n_, n_-sct_);
            }

            return ( 0!=sct_ );
        }
    }

    const ulong * data()  const  { return x_; }
    const ulong * invdata()  const  { return ix_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_ST_GRAY_H__
