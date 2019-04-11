// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/composition-rank.h"

#include "fxtio.h"
#include "fxttypes.h"


void
composition_rank::print(const char *bla, const ulong *x, ulong k)  const
{
    if ( bla )  cout << bla;
    cout << "[ ";
    for (ulong j=0; j<k; ++j)
    {
        ulong xj = x[j];
        if ( xj )  cout << xj;  else cout << '.';
        cout << " ";
    }
    cout << "]";
}
// -------------------------

void
composition_rank::print_deltaset(const char *bla, const ulong *x, ulong k)  const
{
    if ( bla )  cout << bla;
    cout << "[ ";
    for (ulong j=0; j<k; ++j)
    {
        ulong xj = x[j];
        while ( xj-- )  cout << "1 ";
        if ( j<k-1 )  cout << ". ";
    }
    cout << "]";
}
// -------------------------

void
composition_rank::print_deltaset_num(const char *bla, const ulong *x, ulong k)  const
{
//    const char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if ( bla )  cout << bla;
    cout << "[ ";
    for (ulong j=0, z=0;  j<k;  ++j)
    {
        ulong xj = x[j];
        while ( xj-- )  cout << (z++) << " ";
//        while ( xj-- )  cout << str[(z++)] << " ";
        if ( j<k-1 )  cout << ". ";
    }
    cout << "]";
}
// -------------------------

