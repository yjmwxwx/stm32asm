// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/ordered-tree-branches.h"

#include "fxttypes.h"
#include "fxtio.h"


void
ordered_tree_branches::print_level_seq(const char *bla)  const
{
    cout << bla;
    cout << "[ 0";
    for (ulong j=1; j<=num_branches(); ++j)
        for (ulong k=b_[j]+1; k<=a_[j]+b_[j]; ++k)
            cout << " " << k;
    cout << " ]";
}
// -------------------------


void
ordered_tree_branches::print_aa()  const
{
    cout << "O";  // root
    for (ulong j=1; j<=num_branches(); ++j)
    {
        for (ulong k=0; k<b_[j]; ++k)  cout << "   ";
        if ( j==1 )  cout << "--o";
        else         cout << ".--o";
        for (ulong k=1; k<a_[j]; ++k)  cout << "--o";
        cout << endl;
    }
}
// -------------------------
