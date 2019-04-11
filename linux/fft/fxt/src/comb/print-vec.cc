// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxtio.h"

#include "array-len.h"

//#include "fxtalloca.h"
#include "fxttypes.h"


void
print_vec(const char *bla, const ulong *x, ulong n, bool dfz/*=false*/)
// Print x[0,..,n-1] as vector, n is the number of elements in the set.
// If dfz is true then Dots are printed For Zeros.
{
    if ( bla )  cout << bla;

    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        ulong t = x[k];
        if ( t!=0 )  cout << t;
        else         cout << (dfz?'.':'0');
        if ( k<n-1 )  cout << " ";
    }
    cout << " ]";
}
// -------------------------

void
print_vec1(const char *bla, const ulong *x, ulong n)
// Print x[0,..,n-1] as vector, each element incremented by one,
// n is the number of elements in the set.
{
    if ( bla )  cout << bla;

    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        cout << x[k] + 1;
        if ( k<n-1 )  cout << " ";
    }
    cout << " ]";
}
// -------------------------


void
print_vec_rev(const char *bla, const ulong *x, ulong n, bool dfz/*=false*/)
// Print x[0,..,n-1] as vector in reversed order, n is the number of elements in the set.
// If dfz is true then Dots are printed For Zeros.
{
    if ( bla )  cout << bla;

    cout << "[ ";
    ulong k = n;
    do
    {
        --k;
        ulong t = x[k];
        if ( t!=0 )  cout << t;
        else         cout << (dfz?'.':'0');
        if ( k!=0 )  cout << " ";
    }
    while ( k != 0 );
    cout << " ]";
}
// -------------------------



void
print_sign_vec(const char *bla, const ulong *x, ulong n)
// Print x[0,..,n-1] as vector of signs
{
    if ( bla )  cout << bla;

    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        if ( x[k]==1 )  cout << '+';
        else if ( -x[k]==1 )  cout << '-';
        else  cout << x[k];

        if ( k<n-1 )  cout << " ";
    }
    cout << " ]";
}
// -------------------------


static const char sym[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!";
static const ulong mi = ARRAY_LEN(sym) - 2;

void
print_sym_vec(const char *bla, const ulong *x, ulong n)
// Print x[0,..,n-1] as vector of symbols where
// symbols are 0,1,..,9, A,B...,Z, a,b,...,z
{
    if ( bla )  cout << bla;

//    cout << "[" << mi << "]";
    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        ulong v = x[k];
//        cout << "[" << v << "]";
        if ( v >= mi )  v = mi;
        cout << sym[v];
        if ( k<n-1 )  cout << " ";
    }
    cout << " ]";
}
// -------------------------

