// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/cayley-perm.h"

#include "fxtio.h"
#include "fxttypes.h"

void
cayley_perm::print_arrangement(const char *bla)  const
{
    if ( bla )  cout << bla;

    for (ulong v=0; v <= m_; ++v)  // for all sets
    {
        cout << "{ ";
        bool q = false;  // element v seen yet?
        for (ulong j=0; j<n_; ++j)
        {
            if ( a_[j] == v )  // j belongs to current set
            {
                if ( q )  cout << ", ";
                cout << j;
                q = true;
            }
        }
        cout << " }";
        if ( v != m_ )  cout << " < ";
    }
}
// -------------------------
