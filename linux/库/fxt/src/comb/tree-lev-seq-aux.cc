// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/tree-lev-seq-aux.h"

#include "fxtio.h"
#include "fxtalloca.h"
#include "fxttypes.h"


void
tree_lev_seq_aux::print_aa(const char *bla, const ulong *a, ulong n)  const
{
    cout << bla;
    cout << "O";  // root
    ulong t = 0;  // prior level
    for (ulong j=1; j<n; ++j)
    {
        const ulong d = a[j];
        if ( d > t )
        {
            cout << "--o";
        }
        else
        {
            cout << endl;
            for (ulong i=1; i<d; ++i)  cout << "   ";
            cout << ".--o";
        }
        t = d;
    }
}
// -------------------------


void
tree_lev_seq_aux::print_branching_numbers(const char *bla,
                                          const ulong *a, ulong n,
                                          bool dfz/*=true*/)  const
{
    // note: use all_branching_numbers() to make cost linear
    cout << bla;
    cout << "[ ";
    for (ulong j=0; j<n; ++j)
    {
        const ulong b = branching_number(a, n, j);
        if ( b==0 )
            cout << ( dfz ? '.' : '0' ) << " ";
        else
            cout << b << " ";
    }
    cout << "]";
}
// -------------------------


void
tree_lev_seq_aux::print_base_seq(const char *bla,
                                 const ulong *a, ulong n,
                                 bool dfz/*=true*/)  const
// Print sequence of indices where the nodes are attached.
{
    cout << bla;
    cout << "[ ";
    for (ulong j=0; j<n; ++j)
    {
        ulong b = j;
        if ( b != 0 )
        {
            const ulong bv = a[j] - 1;
            do  { --b; }  while ( a[b] != bv );
        }
//        b = j - b;  // distance
        if ( b==0 )
            cout << ( dfz ? '.' : '0' ) << " ";
        else
            cout << (long)b << " ";
    }
    cout << "]";
}
// -------------------------


void
tree_lev_seq_aux::print_paren_word(const char *bla,
                                   const ulong *a, ulong n,
                                   const char * s/*="()"*/)  const
{
    cout << bla;
    if ( n == 0 )  return;

    cout << s[0];  // opening paren
    for (ulong j=1; j<n; ++j)
    {
        if ( a[j] <= a[j-1] )
        {
            ulong d = a[j-1] - a[j];  // >= 0
            do  { cout << s[1]; }  while ( d-- );  // closing parens
        }
        cout << s[0];  // opening paren
    }
    ulong d = a[n-1];
    do  { cout << s[1]; }  while ( d-- );  // closing parens
}
// -------------------------


#include "jjassert.h"

void
tree_lev_seq_aux::print_balanced_composition(const char *bla,
                                             const ulong *a, ulong n)  const
// for balanced trees only!
{
    ulong s = 0;  // sum
    cout << bla;
    cout << "[ ";
    if ( n <= 1 )
    {
        if ( n==1 )  cout << "1 ";
    }
    else
    {
        for (ulong j=1; j<n-1; ++j)
        {
            ulong h = a[j];
            ulong p = 1;  // part of the composition
            while ( a[j+1] == h + 1 )
            {
                p += 1;
                if ( j + 1 == n )  break;
                h = a[j+1];
                ++j;
            }
            cout << p << " ";

            s += p;
        }

        if ( a[n-2] + 1 != a[n-1] )
        {
            cout << 1 << " ";
            s += 1;
        }
    }
    cout << "]";

    jjassert( s == n - 1 );
}
// -------------------------
