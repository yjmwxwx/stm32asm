// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/catalan.h"

#include "fxtio.h"
#include "fxttypes.h"


bool
catalan::next_rec(ulong k)
{
    if ( k<1 )  return false;  // current is last

    int d = d_[k];
    int as = as_[k] + d;

//    bool ovq = ( (d>0) ? (as>as_[k-1]+1) : (as<0) );
    bool ovq = ((uint)as > (uint)as_[k-1]+1);  // same, optimized

    if ( ovq )  // have to recurse
    {
        ulong ns1 = next_rec(k-1);
        if ( 0==ns1 )  return false;

        d = ( xdr_ ? -d : dr0_ );
        d_[k] = d;

        as = ( (d>0) ? 0 : as_[k-1]+1 );
    }
    as_[k] = as;

    return true;
}
// -------------------------


void
catalan::print_internal()  const
{
    cout << "[ ";
    for (ulong j=0; j<n_; ++j)  cout << as_[j] << " ";
    cout << "]";
    cout << "    ";
    cout << "[ ";
    for (ulong j=0; j<n_; ++j)  cout << (d_[j]>0 ? '+' : '-') << " ";
    cout << "]";
}
// -------------------------

