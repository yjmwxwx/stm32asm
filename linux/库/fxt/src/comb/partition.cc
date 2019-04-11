// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/partition.h"

#include "fxtio.h"
#include "fxttypes.h"


void
partition::print()  const
// Print in the form (6 ==)
//   1 + 1 + 4
{
    bool fq = 1;
    for (ulong k=1; k<=n_; ++k)
    {
        ulong c = c_[k];
        ulong v = k;
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
partition::print_falling()  const
// Print in the form (6 ==)
//   4 + 1 + 1
{
    bool fq = 1;
    for (ulong k=n_; k!=0; --k)
    {
        ulong c = c_[k];
        ulong v = k;
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
partition::print_long(bool szq)  const
// Print in the form (6 ==)
//  2* 1 + 0    + 0    + 1* 4 + 0    + 0
// If szq==true, the zeros are skipped.
{
    if ( szq )  // skip zeros
    {
        bool fq = 1;
        for (ulong k=1; k<=n_; ++k)
        {
            if ( c_[k] != 0 )
            {
                if ( fq )  fq = 0;
                else       cout << " +";

                cout << setw(2) << c_[k];

                if ( 0!=c_[k] )  { cout << "*" << setw(2) << k; }
                else              cout << "   ";
            }
        }
    }
    else
    {
        bool fq = 1;
        for (ulong k=1; k<=n_; ++k)
        {
            if ( fq )  fq = 0;
            else       cout << " +";

            cout << setw(2) << c_[k];

            if ( 0!=c_[k] )  { cout << "*" << setw(2) << k; }
            else              cout << "   ";
        }
    }
}
// -------------------------
