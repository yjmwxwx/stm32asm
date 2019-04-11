#if !defined HAVE_NUM_COMPOSITIONS_H__
#define      HAVE_NUM_COMPOSITIONS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
//#include "jjassert.h"


class num_compositions
// Table of number of compositions: nc[n-1][k-1] = binomial(n+k-1, n).
// Used by class composition_rank.
{
public:
    ulong **nc_;  // nc[n-1][k-1] = binomial(n+k-1, n)
    ulong n_;  // max n
    ulong k_;  // max k
    ulong *cc_;  // data (binomial coefficients)

private:  // have pointer data
    num_compositions(const num_compositions&);  // forbidden
    num_compositions & operator = (const num_compositions&);  // forbidden

public:
    explicit num_compositions(ulong n, ulong k)
        : n_(n), k_(k)
    {
        nc_ = new ulong*[n_];
        cc_ = new ulong[ n_ * k_ ];
        nc_[0] = cc_;
        for (ulong j=1; j<n_; ++j)  nc_[j] = nc_[j-1] + k_;
        init();
    }

    void init()
    // nc[0] =   1    2    3    4    5  ... k+1
    // nc[1] =   1    3    6   10   15
    // nc[2] =   1    4   10   20   35
    // nc[3] =   1    5   15   35   70
    // nc[4] =   1    6   21   56  126
    // nc[n-1][k-1] = binomial(n+k-1, n)
    {
        for (ulong k=0; k<k_; ++k)  nc_[0][k] = k+1;
        for (ulong n=1; n<n_; ++n)
        {
            ulong *p0 = nc_[n],  *p1 = nc_[n-1];
            p0[0] = 1;
            for (ulong k=1; k<k_; ++k)  p0[k] = p1[k] + p0[k-1];
        }
    }

    ~num_compositions()
    {
        delete [] nc_;
        delete [] cc_;
    }

    ulong num_comp(ulong n, ulong k)  const
    // Return binomial(n+k-1, n), the number of
    //   k-compositions of n (via table lookup)
    // Must have:  n<=n_  and  k<=k_
    {
        if ( 0==n )  return 1;
        if ( 0==k )  return 0;
//        jjassert( n <= n_ );
//        jjassert( k <= k_ );
        ulong nc = nc_[n-1][k-1];
        return nc;
    }
};
// -------------------------


#endif  // !defined HAVE_NUM_COMPOSITIONS_H__
