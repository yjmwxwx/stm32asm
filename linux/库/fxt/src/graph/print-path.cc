// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/print-bin.h"
#include "fxttypes.h"
#include "fxtio.h"


void
print_path(const ulong *rv, ulong ng)
// Print sequence of nodes.
// Example: the first (De Bruijn) sequence for n=8 (ng=16) is
//  0 1 2 4 9 3 6 13 10 5 11 7 15 14 12 8
{
    for (ulong k=0; k<ng; ++k)  cout << setw(2) << rv[k] << " ";
    cout << endl;
}
// -------------------------


void
print_bin_path(const ulong *rv, ulong ng, ulong ngbits)
// Print sequence of nodes both binary and decimal.
// Example: the first (De Bruijn) sequence for n=8 (ng=16) is:
// ....    0
// ...1    1
// ..1.    2
// .1..    4
// 1..1    9
// ..11    3
// .11.    6
// 11.1   13
// 1.1.   10
// .1.1    5
// 1.11   11
// .111    7
// 1111   15
// 111.   14
// 11..   12
// 1...    8
{
    cout << endl;
    for (ulong k=0; k<ng; ++k)
    {
        print_bin(" ", rv[k], ngbits);
        cout << "  " << setw(3) << rv[k];
        cout << endl;
    }
    cout << endl;
}
// -------------------------

void
print_bin_horiz_path(const ulong *rv, ulong ng, ulong ngbits, const char *c01/*=0*/)
// Horizontally print sequence of nodes in binary.
// The first line corresponds to least significant bit.
// Example: the first (De Bruijn) sequence for n=8 (ng=16) is:
//  -#--##-#-####---
//  --#--##-#-####--
//  ---#--##-#-####-
//  ----#--##-#-####
{
//    static char c0 = '-', c1 = 'X';
    static char c0 = '-', c1 = '#';
    if ( c01 ) { c0 = c01[0];  c1 = c01[1]; }
    for (ulong b=0, m=1;  b<ngbits;  ++b, m<<=1)
    {
        for (ulong k=0; k<ng; ++k)
        {
            bool v = (0!=(rv[k] & m));
            cout << (v ? c1 : c0);
        }
        cout << endl;
    }
    cout << endl;
}
// -------------------------
