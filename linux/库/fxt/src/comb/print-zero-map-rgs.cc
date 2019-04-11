// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "fxtio.h"

void
print_zero_map_rgs_as_zero_dist_rgs(const char *bla,
                                    const ulong *a, ulong n,
                                    bool dfz/*=true*/)
// Print corresponding zero-dist RGS,
// all zeros are replaced by fixed points.
{
    if ( bla )  cout << bla;
    cout << "[";
    for (ulong j=0; j<n; ++j)
    {
        ulong v = a[j];
        if ( v==0 )  cout << " " << ( dfz ? '.' : '0' );
        else         cout << " " << j + 1 - v;
    }
    cout << " ]";
}
// -------------------------


void
print_zero_map_rgs_as_fp_rgs(const char *bla,
                             const ulong *a, ulong n,
                             bool dfz/*=true*/,
                             bool zb/*=true*/)
// Print corresponding fixed-point RGS,
// all zeros are replaced by fixed points.
// zb determines whether printed elements are zero based.
{
    if ( bla )  cout << bla;
    cout << "[";
    for (ulong j=0; j<n; ++j)
    {
        ulong v = a[j];
        if ( v==0 )  v = j + 1;
        v -= zb;
        if ( dfz )
        {
            if ( v==0 )  cout << " " << '.';
            else         cout << " " << v;
        }
        else
            cout << " " << v;
    }
    cout << " ]";
}
// -------------------------

void
print_zero_map_rgs_as_fp_dist_rgs(const char *bla,
                                  const ulong *a, ulong n,
                                  bool dfz/*=true*/,
                                  bool zb/*=true*/)
// Print corresponding fixed-point-dist RGS,
// all zeros are replaced by fixed points.
{
    if ( bla )  cout << bla;
    zb = ! zb;
    cout << "[";
    for (ulong j=0; j<n; ++j)
    {
        ulong v = a[j];
        if ( v == 0 )
        {
            v = j + zb;
            if ( v==0 )  cout << " " << ( dfz ? '.' : '0' );
            else         cout << " " << v;
        }
        else           cout << " " << j + 1 - v;
    }
    cout << " ]";
}
// -------------------------


void
print_zero_map_rgs_setpart(const char *bla,
                           const ulong *a, ulong n,
                           bool zb/*=false*/,
                           bool iq/*=false*/)
// Print set partition corresponding to RGS.
// zb determines whether the output is zero-based.
// Set iq to use '()', not '{}', (use to print involutions).
{
    if ( bla )  cout << bla;

    ulong ns = 0;  // number of sets
    for (ulong j=0; j<n; ++j)
        ns += (a[j]==0);
//    cout << " :: ns=" << ns << "   ";

    for (ulong j=0; j<n; ++j)
    {
        if ( a[j]==0 )
        {
            cout << ( iq ? '(' : '{' );
            cout << j + 1 - zb;
            for (ulong k=j+1; k<n; ++k)
            {
                if ( a[k] == j+1 )
                {
                    cout << ", ";
                    cout << k + 1 - zb;
                }
            }
            cout << ( iq ? ')' : '}' );
            if ( --ns )  cout << ", ";
        }
    }
}
// -------------------------
