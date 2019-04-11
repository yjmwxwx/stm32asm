// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/composition-nz-minc.h"

#include "fxtio.h"
#include "fxttypes.h"


void
composition_nz_minc::print_unit_partition(const char *bla, bool dfz/*=false*/)  const
// Print corresponding partition of c into n+1 powers of 1/f.
// If the first part (c=a[1]) equals 1 the printed sequence gives the
//   number of terminal nodes at the levels of the Huffman tree.
{
    if ( bla )  cout << bla;

    if ( m_ == 0 )
    {
        cout << "[ 1 ]";
        return;
    }

    cout << "[";
    cout << " " << ( dfz ? '.' : '0' );

    ulong e1 = a_[1];
    ulong j = 2;
    while( j<=m_ )
    {
        e1 *= f_;
        ulong e2 = a_[j];
        ulong d =  e1 - e2;
        if ( d!=0 )  cout << " " << d;
        else         cout << " " << ( dfz ? '.' : '0' );
        e1 = e2;
        ++j;
    }

    e1 *= f_;
    cout << " " << e1;

    while( j<=n_ )
    {
        cout << " " << ( dfz ? '.' : '0' );
        ++j;
    }

    cout << " ]";
}
// -------------------------

