// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "perm/permq.h"
#include "ds/bitarray.h"
#include "fxttypes.h"

#include "fxtio.h"


void
print_cycles(const char *bla, const ulong *f, ulong n, bitarray *tb/*=0*/)
// Print cycle form of the permutation in f[].
// Examples (first permutations of 4 elements in lex order):
//       array form      cycle form
//   0:  [ 0 1 2 3 ]    (0) (1) (2) (3)
//   1:  [ 0 1 3 2 ]    (0) (1) (2, 3)
//   2:  [ 0 2 1 3 ]    (0) (1, 2) (3)
//   3:  [ 0 2 3 1 ]    (0) (1, 2, 3)
//   4:  [ 0 3 1 2 ]    (0) (1, 3, 2)
//   5:  [ 0 3 2 1 ]    (0) (1, 3) (2)
//   6:  [ 1 0 2 3 ]    (0, 1) (2) (3)
//   7:  [ 1 0 3 2 ]    (0, 1) (2, 3)
//   8:  [ 1 2 0 3 ]    (0, 1, 2) (3)
{
    if ( bla )  cout << bla;

    bitarray *b = tb;
    if ( tb==0 )  b = new bitarray(n);
    b->clear_all();

    ulong np = 3*n;  // for padding

    for (ulong k=0; k<n; ++k)
    {
        if ( b->test(k) )  continue;  // already processed

        cout << "(";  np-=1;
        ulong i = k;  // next in cycle
        do
        {
            cout << i;
            if ( f[i]!=k )  { cout << ", ";  np-=2; }
            b->set(i);
        }
        while ( (i=f[i]) != k );  // until we meet cycle leader again
        cout << ") ";  np-=2;
    }

    for (  ; np; --np)  cout << " ";  // append blanks to max len

    if ( tb==0 )  delete b;
}
// -------------------------


void
print_cycles_len(const ulong *f, ulong n, bitarray *tb/*=0*/)
// Print cycle form of the permutation in f[],
// each cycle on own line.
// For examples, with the permutation
// [ 0 2 4 6 1 3 5 7 ]
// we print:
// (0) #=1
// (1, 2, 4) #=3
// (3, 6, 5) #=3
// (7) #=1
{
    bitarray *b = tb;
    if ( tb==0 )  b = new bitarray(n);
    b->clear_all();

    for (ulong k=0; k<n; ++k)
    {
        if ( b->test(k) )  continue;  // already processed

        cout << " (";
        ulong i = k;  // next in cycle
        ulong len = 0;
        do
        {
            ++len;
            cout << i;
            if ( f[i]!=k )  cout << ", ";
            b->set(i);
        }
        while ( (i=f[i]) != k );  // until we meet cycle leader again
        cout << ")";
        cout << " #=" << len;
        cout << endl;
    }

    if ( tb==0 )  delete b;
}
// -------------------------


ulong
print_cycle(const ulong *f, ulong e0/*=0*/)
// Print the cycle that contains e0.
// Return length of the cycle.
{
    ulong e = e0;
    ulong ct = 0;
    cout << "(";
    do
    {
        ++ct;
        cout << e;
        e=f[e];
        if ( e!=e0 )  cout << ", ";
    }
    while ( e!=e0 );
    cout << ")";
    return ct;
}
// -------------------------


void
print_inv_perm_code(const char *bla, const ulong *f, ulong n, bitarray *tb/*=0*/)
// Print code for the inverse permutation in f[],
// For examples, the permutation
//  x[] = [ 0 2 4 6 1 3 5 7 ]
// maps identity to (the inverse of x[]):
//  f[] = [ 0 4 1 5 2 6 3 7 ]
// and (with bla:="foo_perm") we print:
//  template <typename Type>
//  inline void foo_perm_8(Type *f)
//  {
//    { Type t=f[1];  f[1]=f[4];  f[4]=f[2];  f[2]=t; }
//    { Type t=f[3];  f[3]=f[5];  f[5]=f[6];  f[6]=t; }
//  }
{
    bitarray *b = tb;
    if ( tb==0 )  b = new bitarray(n);
    b->clear_all();


    cout << "template <typename Type>" << endl;
    cout << "inline void " << bla << "_" << n << "(Type *f)" << endl;
    cout << "{" << endl;

    for (ulong k=0; k<n; ++k)
    {
        if ( b->test(k) )  continue;  // already processed
        if ( f[k] == k )  continue;  // skip fixed points

        cout << "  { Type t=f[" << k << "]; ";
        ulong i = k;  // next in cycle
        ulong li;
        do
        {
            b->set(i);
            li = i;
            i = f[i];
            if ( i!=k )  cout << " f[" << li << "]=f[" << i << "]; ";
        }
        while ( i != k );  // until we meet cycle leader again
        cout << " f[" << li << "]=t; ";
        cout << "}" << endl;
    }
    cout << "}" << endl;

    if ( tb==0 )  delete b;
}
// -------------------------

