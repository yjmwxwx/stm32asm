// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxtio.h"

#include "bits/bithigh.h"  // highest_one_idx()
#include "bits/print-bin.h"

#include "bits/bitsperlong.h"
#include "fxttypes.h"  // ulong


void
bitpol_print(const char *bla, ulong c, bool sq/*=true*/)
// print as:
//  x^7 + x^4 + x^3 + 1  if sq==true
//  x^7+x^4+x^3+1  if sq==false
{
    cout << bla;

    ulong i = BITS_PER_LONG-1;
    ulong t = 1UL<<i;
    while ( c )
    {
        ulong q = c & t;
        if ( q )
        {
            c ^= q;
            if ( i<=1 )  cout << (i ? "x" : "1");
            else
            {
                cout << "x^" << i;
            }
            if ( c )
            {
                if ( sq )  cout << " + ";
                else       cout << "+";
            }
        }
        t>>=1;
        --i;
    }
}
// -------------------------


void
bitpol_print_bin(const char *bla, ulong c)
// print as:  1..11.1
{
    ulong d = highest_one_idx(c);
    print_bin(bla, c, d+1);
}
// -------------------------


void
bitpol_print_coeff(const char *bla, ulong c)
// print as:  [7, 4, 3, 0]
{
    cout << bla;
    cout << "[";
    ulong i = BITS_PER_LONG-1;
    ulong t = 1UL<<i;
    while ( c )
    {
        ulong q = c & t;
        if ( q )
        {
            c ^= q;
            cout << i;
            if ( c )  cout << ",";
        }
        t>>=1;
        --i;
    }
    cout << "]";
}
// -------------------------

void
bitpol_print_tex(const char *bla, ulong c)
// print as:  x^{7} + x^{4} + x^{3} + 1
{
    cout << bla;
    ulong i = BITS_PER_LONG-1;
    ulong t = 1UL<<i;
    while ( c )
    {
        ulong q = c & t;
        if ( q )
        {
            c ^= q;
            if ( i<=1 )  cout << (i ? "x" : "1");
            else
            {
                cout << "x^" << "{" << i << "}";
            }
            if ( c )  cout << " + ";
        }
        t>>=1;
        --i;
    }
}
// -------------------------


void
bitpol_print_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct)
// print as:  (x+1)^5 *  (x^2+x+1)
{
    cout << bla;
    for (ulong i=0; i<fct; ++i)
    {
        cout << " (";
        bitpol_print("", f[i], false);
        cout << ")";
        if ( e[i]>1 )  cout << "^" << e[i];
        if ( i<fct-1 )  cout << " * ";
    }
}
// -------------------------

void
bitpol_print_bin_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct)
// print as:  (1.)^5 (111)
{
    cout << bla;
    for (ulong i=0; i<fct; ++i)
    {
        cout << " (";
        bitpol_print_bin("", f[i]);
        cout << ")";
        if ( e[i]>1 )  cout << "^" << e[i];
//        if ( i<fct-1 )  cout << " * ";
    }
}
// -------------------------


void
bitpol_print_coeff_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct)
// print as:  [1,0]^5 * [2,1,0]
{
    cout << bla;
    for (ulong i=0; i<fct; ++i)
    {
        bitpol_print_coeff("", f[i]);
        if ( e[i]>1 )  cout << "^" << e[i];
        if ( i<fct-1 )  cout << " * ";
    }
}
// -------------------------



void
bitpol_print_tex_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct)
// print as:  \left(x + 1\right)^{5} \cdot  \left(x^{2} + x + 1\right)
{
    cout << bla;
    for (ulong i=0; i<fct; ++i)
    {
        cout << " \\left(";
        bitpol_print_tex("", f[i]);
        cout << "\\right)";
        if ( e[i]>1 )  cout << "^{" << e[i] << "}";
        if ( i<fct-1 )  cout << " \\cdot ";
    }
}
// -------------------------

void
bitpol_print_short_factorization(const char *bla, const ulong *f, const ulong *e, ulong fct)
// print as:  [deg1 ex1] [deg2 ex2] ... [degk exk]
{
    cout << bla;
    for (ulong i=0; i<fct; ++i)
    {
        cout << " [";
        cout << highest_one_idx(f[i]);
        cout << " " << e[i];
        cout << "]";
//        if ( i<fct-1 )  cout << "  * ";
    }
}
// -------------------------

