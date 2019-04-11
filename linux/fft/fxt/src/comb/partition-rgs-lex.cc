// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/partition-rgs-lex.h"

#include "fxtio.h"

#include "fxttypes.h"


void
partition_rgs_lex::print_partition(const char *bla)  const
{
    if ( bla )  cout << bla;
    cout << "[ ";
    if ( n_ != 0 )
    {
        ulong v = a_[0];
        ulong p = 1;
        for (ulong j=1; j<n_; ++j)
        {
            ulong aj = a_[j];
            if ( v != aj )
            {
                cout << p << " ";
                p = 1;
                v = aj;
            }
            else  ++p;
        }

        cout << p;
    }
    cout << " ]";
}
// -------------------------
