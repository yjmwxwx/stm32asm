#if !defined HAVE_PARTITION_GEN_H__
#define      HAVE_PARTITION_GEN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


class partition_gen
// Integer partitions into parts pv[0], pv[1], ..., pv[n-1].
// pv[] defaults to [1, 2, 3, ...] (all positive parts).
{
public:
    ulong ct_;  // Number of partitions found so far
    ulong n_;   // Number of values
    ulong i_;   // level in iterative search

    ulong *pv_;  // values into which to partition
    ulong *pc_;  // multipliers for values
    ulong pci_;  // temporary for pc_[i_]
    ulong *r_;   // rest
    ulong ri_;   // temporary for r_[i_]
    ulong x_;    // value to partition

private:  // have pointer data
    partition_gen(const partition_gen&);  // forbidden
    partition_gen & operator = (const partition_gen&);  // forbidden

public:
    explicit partition_gen(ulong x, ulong n=0, const ulong *pv=0)
    {
        if ( 0==n )  n = x;
        n_ = n;
        pv_ = new ulong[n_+1];
        if ( pv )  for (ulong j=0; j<n_; ++j)  pv_[j] = pv[j];
        else       for (ulong j=0; j<n_; ++j)  pv_[j] = j + 1;
        pc_ = new ulong[n_+1];
        r_  = new ulong[n_+1];
        first(x);
    }

    void first(ulong x)
    {
        x_ = x;
        ct_ = 0;
        for (ulong k=0; k<n_; ++k)  pc_[k] = 0;
        for (ulong k=0; k<n_; ++k)  r_[k] = 0;
        r_[n_-1] = x_;
        r_[n_] = x_;
        i_ = n_ - 1;
        pci_ = 0;
        ri_ = x_;
    }

    ~partition_gen()
    {
        delete [] pv_;
        delete [] pc_;
        delete [] r_;
    }

    ulong next();  // generate next partition
    ulong next_func(ulong i);  // aux

    ulong count(ulong x);  // count number of partitions
    ulong count_func(ulong i);  // aux

    void print()  const;
    void print2()  const;
    bool check(ulong i=0)  const;
};
// -------------------------


#endif  // !defined HAVE_PARTITION_GEN_H__
