// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxtio.h"

//#include "fxtalloca.h"
#include "fxttypes.h"

// Enable heuristic check like asserting that
// a symbol appears at most 10000 times
// (which usually indicates an error like an under-run):
#define HEURISTIC_ASSERTS
#ifdef HEURISTIC_ASSERTS
#include "jjassert.h"
#endif


//: With delta sets: default is to print zeros as dots.
static const char n01[] = {'.', '1'};
//static const char n01[] = {'0', '1'};

void
print_set(const char *bla, const ulong *x, ulong n, ulong off/*=0*/)
// Print x[0,..,n-1] as set, n is the number of elements in the set.
// Example:  x[]=[0,1,3,4,8]  ==> "{0,1,3,4,8}"
{
    if ( bla )  cout << bla;

#ifdef HEURISTIC_ASSERTS
    jjassert( n <= 10000  );
#endif
    cout << "{ ";
    for (ulong k=0; k<n; ++k)
    {
        cout << x[k]-off;
        if ( k<n-1 )  cout << ", ";
    }
    cout << " }";
}
// -------------------------


void
print_set_as_deltaset(const char *bla, const ulong *x, ulong n, ulong N, const char *c01/*=0*/)
// Print x[0,..,n-1], a subset of {0,1,...,N-1} as delta set,
// n is the number of elements in the set.
// Example:  x[]=[0,1,3,4,8]  ==> "11.11...1"
{
    if ( bla )  cout << bla;

    const char *d = ( 0==c01 ?  n01 : c01 );

    ulong j = 0;
    for (ulong k=0; k<n; ++k)
    {
#ifdef HEURISTIC_ASSERTS
        jjassert( x[k] <= 10000 );  // this is usually an error (some under-run)
#endif
        for (  ; j<x[k]; ++j)  cout << d[0];
        cout << d[1];
        ++j;
    }

    while ( j++ < N )  cout << d[0];
}
// -------------------------

void
print_set1_as_deltaset(const char *bla, const ulong *x, ulong n, ulong N, const char *c01/*=0*/)
// Print x[0,..,n-1], a subset of {1,...,N} as delta set,
// n is the number of elements in the set.
// Example:  x[]=[1,2,4,5,9]  ==> "11.11...1"
{
    if ( bla )  cout << bla;

    const char *d = ( 0==c01 ?  n01 : c01 );
    ulong j = 0;
    for (ulong k=0; k<n; ++k)
    {
#ifdef HEURISTIC_ASSERTS
        jjassert( x[k] <= 10000  );
#endif
        for (  ; j<x[k]-1; ++j)  cout << d[0];

        cout << d[1];
        ++j;
    }

    while ( j++ < N )  cout << d[0];
}
// -------------------------



ulong
print_deltaset_as_set(const char *bla, const ulong *x, ulong n, int eq/*=0*/)
// Print delta set x[0,..,n-1] as set.
// Example:  x[]=[0,0,1,0,1,1] ==> "{2,4,5}"
// if eq!=0 then print spaces for empty positions:
// With example above:  "{ , , 2, , 4, 5}"
// Return number of elements (3 in example).
{
    if ( bla )  cout << bla;

    cout << "{ ";
    ulong k = 0;
    ulong num = 0;

    if ( 0==eq )  // skip leading empty buckets
    {
        while ( k<n-1 && 0==x[k])  { ++k; }
    }

    if ( x[k] )  { cout << k;  ++num; }
    else if ( 0!=eq )   cout << " ";

    for (++k; k<n; ++k)
    {
        if ( x[k] )
        {
            cout << ", " << k;
            ++num;
        }
        else if ( 0!=eq )   cout << ",  ";
    }
    cout << " }";

    return  num;
}
// -------------------------

ulong
print_deltaset_as_set1(const char *bla, const ulong *x, ulong n, int eq/*=0*/)
// Print delta set x[0,..,n-1] as set, lowest element one.
// Example:  x[]=[0,0,1,0,1,1] ==> "{3,5,6}"
// if eq!=0 then print spaces for empty positions:
// With example above:  "{ , , 3, , 5, 6}"
// Return number of elements (3 in example).
{
    if ( bla )  cout << bla;

    cout << "{ ";
    ulong k = 0;
    ulong num = 0;

    if ( 0==eq )  // skip leading empty buckets
    {
        while ( k<n-1 && 0==x[k])  { ++k; }
    }

    if ( x[k] )  { cout << k+1;  ++num; }
    else if ( 0!=eq )   cout << " ";

    for (++k; k<n; ++k)
    {
        if ( x[k] )
        {
            cout << ", " << k+1;
            ++num;
        }
        else if ( 0!=eq )   cout << ",  ";
    }
    cout << " }";

    return  num;
}
// -------------------------


void
print_deltaset(const char *bla, const ulong *x, ulong n, const char *c01/*=0*/)
// Print the delta set x[0,..,n-1]
// n is the number of elements in the set.
// Example:  x[]=[1,0,1,1,0,0,0,1]  ==> "11.11...1"
{
    if ( bla )  cout << bla;

    const char *d = ( 0==c01 ?  n01 : c01 );

    for (ulong k=0; k<n; ++k)
    {
        if ( 0==x[k] )  cout << d[0];
        else            cout << d[1];
    }
}
// -------------------------

