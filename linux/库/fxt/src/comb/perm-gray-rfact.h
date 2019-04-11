#if !defined HAVE_PERM_GRAY_RFACT_H__
#define      HAVE_PERM_GRAY_RFACT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
//#include "comb/mixedradix-gray2.h"
#include "comb/mixedradix-gray.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

//#include "jjassert.h"

// whether to create successors via inverse permutations:
#define PGRF_SUCC_BY_INV  // default on (more efficient)


class perm_gray_rfact
// Gray code for permutations.
// CAT algorithm based on mixed radix Gray code for rising factorial base.
{
public:
    mixedradix_gray *M_;
    ulong n_;   // number of elements to permute
    ulong *x_;  // current permutation (of {0, 1, ..., n-1})
    ulong *ix_;  // inverse permutation
    ulong sw1_, sw2_;  // indices of elements swapped most recently

private:  // have pointer data
    perm_gray_rfact(const perm_gray_rfact&);  // forbidden
    perm_gray_rfact & operator = (const perm_gray_rfact&);  // forbidden

public:
    explicit perm_gray_rfact(ulong n)
    {
        n_ = n;
        x_ = new ulong[n_];
        ix_ = new ulong[n_];
        M_ = new mixedradix_gray(n_-1, 1);  // rising factorial base

        first();
    }

    ~perm_gray_rfact()
    {
        delete [] x_;
        delete [] ix_;
        delete M_;
    }

    void first()
    {
        M_->first();
        for (ulong k=0; k<n_; ++k)  x_[k] = ix_[k] = k;
        sw1_=n_-1;  sw2_=n_-2;
    }

    bool next()
    {
        // Compute next mixed radix number in Gray code order:
        if ( false == M_->next() )  { first(); return false; }
        ulong j = M_->pos();  // position of changed digit

        if ( j<=1 )  // easy cases: swap == (0,j+1)
        {
            const ulong i2 = j+1;  // i1 == 0
            const ulong x1 = x_[0],  x2 = x_[i2];
            x_[0] = x2;    x_[i2] = x1;  // swap2(x_[i1], x_[i2]);
            ix_[x1] = i2;  ix_[x2] = 0;  // swap2(ix_[x1], ix_[x2]);
            sw1_=0;  sw2_=i2;
            return true;
        }
        else
        {
            const ulong i1 = j+1,  x1 = x_[i1];
            ulong  i2 = i1,  x2;
            const int d = M_->dir();    // direction of change

#ifdef PGRF_SUCC_BY_INV
            if ( d>0 )  // in the inverse permutation search first smaller element left:
            {
                for (x2=x1-1;  ; --x2)  if ( (i2=ix_[x2]) < i1 )  break;
                // jjassert( x2 == x1-1 );  // not true: first failure for transition 59/60
                // jjassert( (long)x2 >= (long)x1-2 );  // not true: 197/198
            }
            else  // in the inverse permutation search first smaller element right:
            {
                for (x2=x1+1;  ; ++x2)  if ( (i2=ix_[x2]) < i1 )  break;
                // jjassert( x2 == x1+1 );  // not true: first failure for transition 41/42
                // jjassert( (long)x2 <= (long)x1+2 );  // not true: 281/282
            }

#else  //  PGRF_SUCC_BY_INV
            if ( d>0 )
            {
                x2 = 0;
                for (ulong t=0; t<i1; ++t)  // search maximal smaller element left
                {
                    ulong xt = x_[t];
                    if ( (xt < x1) && (xt >= x2) )  { i2=t; x2=xt; }
                }
            }
            else
            {
                x2 = n_;
                for (ulong t=0; t<i1; ++t)  // search minimal greater element
                {
                    ulong xt = x_[t];
                    if ( (xt > x1) && (xt <= x2) )  { i2=t; x2=xt; }
                }
            }
#endif  //  PGRF_SUCC_BY_INV

//            jjassert( i2+1 > 0 );
//            jjassert( i2<i1 );

            x_[i1] = x2;    x_[i2] = x1;  // swap2(x_[i1], x_[i2]);
            ix_[x1] = i2;  ix_[x2] = i1;  // swap2(ix_[x1], ix_[x2]);

            sw1_=i2;  sw2_=i1;

            return true;
        }
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

//#undef PGRF_SUCC_BY_INV  // leave defined

#endif  // !defined HAVE_PERM_GRAY_RFACT_H__

