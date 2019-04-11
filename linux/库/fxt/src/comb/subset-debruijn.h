#if !defined  HAVE_SUBSET_DEBRUIJN_H__
#define       HAVE_SUBSET_DEBRUIJN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "comb/binary-debruijn.h"
//#include "aux1/shift.h"


class subset_debruijn : public binary_debruijn
// Subsets of the set {0,1,2,...,n-1} in an order
// determined by a De Bruijn sequence.
// Note: work per subset is proportional to n.
{
protected:
    ulong *x;   // subset as delta set
    ulong el_;  // new element to be shifted in
    ulong num_;  // number of elements in subset

private:  // have pointer data
    subset_debruijn(const subset_debruijn&);  // forbidden
    subset_debruijn & operator = (const subset_debruijn&);  // forbidden

public:
    explicit subset_debruijn(ulong n)
        : binary_debruijn(n)
    {
        x = new ulong[n_];
        first();
    }

    ~subset_debruijn()  { delete [] x; }


    void first()
    {
        for (ulong j=0; j<n_; ++j)  x[j] = 0;

        el_ = binary_debruijn::first_digit();
        do  // make empty set the last set
        {
            el_ = binary_debruijn::next_digit();
        }
        while ( 0==el_ );
        sync_x();

        num_ = 0;
        for (ulong j=0; j<n_; ++j)  num_ += x[j];
    }


    ulong next()  // return number of elements
    {
        el_ = binary_debruijn::next_digit();
        if ( el_==2 )  el_ = binary_debruijn::first_digit();  // rewind DBS
        sync_x();
        return  num_;
    }

    const ulong * data()  const  { return x; }


protected:
    void sync_x()
    // Note: performance bottleneck
    {
        num_ -= x[n_-1];

//        shift_right(x, n_, 1);
        for (ulong k = n_ - 1; k!=0; --k)  x[k] = x[k-1];

        x[0] = el_;
        num_ += el_;
    }

private:
    int done()  const;  // forbidden (exists in base class)
};
// -------------------------



#endif  // !defined HAVE_SUBSET_DEBRUIJN_H__
