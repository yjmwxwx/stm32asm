#if !defined  HAVE_COMBINATION_ENUP_H__
#define       HAVE_COMBINATION_ENUP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/endo-enup.h"
#include "fxttypes.h"

//#include "jjassert.h"


class combination_enup
// Combinations in strong minimal-change order (enup steps).
// The set (as opposed to delta set) is generated.
// Generation via enup/endo counting.
{
public:
    ulong *x_;  // combination: k elements 0<=x[j]<k in increasing order
    ulong *s_;  // aux: start of range for enup moves
    ulong *a_;  // aux: actual start position of enup moves
    ulong n_, k_;  // Combination (n choose k)

private:  // have pointer data
    combination_enup(const combination_enup&);  // forbidden
    combination_enup & operator = (const combination_enup&);  // forbidden

public:
    explicit combination_enup(ulong n, ulong k)
    {
        n_ = n;
        k_ = k;
        x_ = new ulong[k_+1];  // incl. padding x_[k]
        s_ = new ulong[k_+1];  // incl. padding s_[k]
        a_ = new ulong[k_];
        x_[k_] = n_;

        first();
    }

    ~combination_enup()
    {
        delete [] x_;
        delete [] s_;
        delete [] a_;
    }

    const ulong * data()  const  { return x_; }

    void first()
    {
        for (ulong j=0; j<k_; ++j)  x_[j] = j;
        for (ulong j=0; j<k_; ++j)  s_[j] = j;
        for (ulong j=0; j<k_; ++j)  a_[j] = x_[j];
    }

    ulong next()
    // Return position where track changed, return k with last combination
    {
        ulong j = k_;
        while ( j-- )  // loop over tracks
        {
            const ulong sj = s_[j];
//            if ( j==0 )  jjassert( sj == 0 );
//            else         jjassert( sj == x_[j-1]+1 );
            const ulong m = x_[j+1] - sj - 1;

            if ( 0 != m )  // unless range empty
            {
                ulong u = x_[j] - sj;

                // move right on even positions:
                if ( 0==(sj&1) )  u = next_enup(u, m);
                else              u = next_endo(u, m);

                u += sj;

                if ( u != a_[j] )  // next pos != start position
                {
//                    jjassert( u >= sj );
//                    jjassert( u < n_ );
                    x_[j] = u;
                    s_[j+1] = u+1;
                    return j;
                }
            }

            a_[j] = x_[j];
        }

        return  k_;  // current combination is last
    }
};
// -------------------------



#endif  // !defined HAVE_COMBINATION_ENUP_H__
