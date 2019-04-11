// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/binary-huffman.h"

#include "fxtio.h"

#include "fxttypes.h"



void
binary_huffman::print_unit_sum(const char *bla)  const
{
    if ( bla )  cout << bla;

    for (ulong j=0; j<=m_; ++j)
    {

        if ( a_[j] != 0 )
        {
            cout << " + " << a_[j] << "/" << (1UL<<j);
        }
    }
//    cout << endl;
}
// -------------------------


