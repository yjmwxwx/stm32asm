// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/partition-gen.h"

#include "fxtio.h"

#include "fxttypes.h"

bool
partition_gen::check(ulong i/*=0*/)  const
{
    ulong xx = 0;
    for (ulong k=i;  k<n_; ++k)  xx += pc_[k]*pv_[k];
    return  (xx==x_);
}
// -------------------------


void
partition_gen::print()  const
// Print in the form (6 ==)
//   1 + 1 + 4
{
//    cout << setw(4) << x_ << " == ";
    bool fq = 1;
    for (ulong k=0; k<n_; ++k)
    {
        ulong c = pc_[k];
        ulong v = pv_[k];
        for (ulong j=0; j<c; ++j)
        {
            if ( fq )  fq = 0;
            else       cout << " +";
            cout << setw(2) << v;
        }
    }
}
// -------------------------


void
partition_gen::print2()  const
// Print in the form (6 ==)
//  2* 1 + 0    + 0    + 1* 4 + 0    + 0
{
//    cout.width(4);  cout << x_;  cout << " == ";
    bool fq = 1;
    for (ulong k=0; k<n_; ++k)
    {
        if ( fq )  fq = 0;
        else       cout << " +";
        cout << setw(2) << pc_[k];
        if ( 0!=pc_[k] )  { cout << "*" << setw(2) << pv_[k]; }
        else              cout << "   ";
    }
}
// -------------------------


ulong
partition_gen::next()
// Generate next partition
{
    if ( i_>=n_ )  return  n_;

    r_[i_] = ri_;
    pc_[i_] = pci_;
    i_ = next_func(i_);

    for (ulong j=0; j<i_; ++j)  pc_[j] = r_[j] = 0;

    ++i_;
    ri_ = r_[i_] - pv_[i_];
    pci_ = pc_[i_] + 1;

    return  i_ - 1;  // >=0
}
// -------------------------

ulong
partition_gen::next_func(ulong i)
{
 start:
    if ( 0!=i )
    {
        while ( (long)r_[i] > 0 )  // jjcast
        {
            pc_[i-1] = 0;
            r_[i-1] = r_[i];
            --i;  goto start;   // iteration
        }
    }
    else  // iteration end
    {
        if ( 0!=r_[i] )
        {
            ulong d = r_[i] / pv_[i];
            r_[i] -= d * pv_[i];
            pc_[i] = d;
        }
    }

    if ( 0==r_[i] )  // valid partition found
    {
        ++ct_;
        return i;
    }

    ++i;
    if ( i>=n_ )  return n_;  // search finished

    r_[i] -= pv_[i];
    ++pc_[i];

    goto start;  // iteration
}
// -------------------------


ulong
partition_gen::count(ulong x)
// count number of partitions
{
    first(x);
    count_func(n_-1);
    return ct_;
}
// -------------------------

ulong
partition_gen::count_func(ulong i)
{
    if ( 0!=i )
    {
        while ( r_[i]>0 )
        {
            pc_[i-1] = 0;
            r_[i-1] = r_[i];
            count_func(i-1);  // recursion
            r_[i] -= pv_[i];
            ++pc_[i];
        }
    }
    else  // recursion end
    {
        if ( 0!=r_[i] )
        {
            ulong d = r_[i] / pv_[i];
            r_[i] -= d * pv_[i];
            pc_[i] = d;
        }
    }

    if ( 0==r_[i] )  // valid partition found
    {
        // if ( whatever )  ++ct_;  // restricted count
        ++ct_;
        return 1;
    }
    else  return 0;
}
// -------------------------
