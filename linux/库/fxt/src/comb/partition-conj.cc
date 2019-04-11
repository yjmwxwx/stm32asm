// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


ulong
partition_asc_conj(const ulong *a, ulong m, ulong *b)
// Write conjugate partition of a[]
// (a weakly ascending list with m parts) into b[].
// Return number of parts in b[].
// The first element in both arrays is at index 0.
{
    if ( m==0 ) return 0;

    // number of parts in a[] is largest part in b[]:
    ulong p = m;

    // largest part in a[] is number of parts in b[]:
    ulong w = a[m-1];  // write position

    ulong v = 0;  // last value
    ulong r = 0;  // read position
    do
    {
        ulong d = (a[r++] - v);  // d >= 0
        if ( d != 0 )  // new value
        {
            v += d;  // update value
            do  // write d times the part p
            {
                b[--w] = p;
                --d;
            }
            while ( d );
        }
        --p;
    }
    while ( p );

    return  a[m-1];
}
// -------------------------


bool
partition_asc_is_conj(const ulong *a, ulong ma, const ulong *b=0, ulong mb=0)
// Return whether a[] (ma parts) and b[] (mb parts) are mutually conjugate partitions.
// Both a[] and b[] must be weakly ascending lists with
// the first element at index 0.
{
    if ( b==0 )  { b=a; mb=ma; }

    if ( ma==0 )  return (mb==0);

    if ( ma != b[mb-1] )  return false;
    if ( mb != a[ma-1] )  return false;

//    if ( a[0]==0 ) return 0;

    // number of parts in a[] is largest part in b[]:
    ulong p = ma;

    // largest part in a[] is number of parts in b[]:
    ulong w = a[ma-1];  // position in b

    ulong v = 0;  // last value
    ulong r = 0;  // read position
    do
    {
        ulong d = (a[r++] - v);  // d >= 0
        if ( d != 0 )  // new value
        {
            v += d;  // update value
            do  // need d times the part p
            {
                if ( b[--w] != p )  return false;
                --d;
            }
            while ( d );
        }
        --p;
    }
    while ( p );

    return  true;
}
// -------------------------


bool
partition_asc_is_self_conj(const ulong *a, ulong m)
// Return whether the partition in a[] (m parts) is self-conjugate.
{
    return  partition_asc_is_conj(a, m, a, m);
}
// -------------------------



ulong
partition_desc_conj(const ulong *a, ulong m, ulong *b)
// Write conjugate partition of a[]
// (a weakly descending list with m parts) into b[].
// Return number of parts in b[].
// The first element in both arrays is at index 0.
{
    if ( m==0 ) return 0;

    // number of parts in a[] is largest part in b[]:
    ulong p = m;

    // largest part in a[] is number of parts in b[]:
    ulong w = 0;  // write position

    ulong v = 0;  // last value
    ulong r = m-1;  // read position
    do
    {
        ulong d = (a[r--] - v);  // d >= 0
        if ( d != 0 )  // new value
        {
            v += d;  // update value
            do  // write d times the part p
            {
                b[w++] = p;
                --d;
            }
            while ( d );
        }
        --p;
    }
    while ( p );

    return  a[0];
}
// -------------------------


bool
partition_desc_is_conj(const ulong *a, ulong ma, const ulong *b=0, ulong mb=0)
// Return whether a[] (ma parts) and b[] (mb parts) are mutually conjugate partitions.
// Both a[] and b[] must be weakly descending lists with
// the first element at index 0.
{
    if ( b==0 )  { b=a; mb=ma; }

    if ( ma==0 )  return (mb==0);

    if ( ma != b[0] )  return false;
    if ( mb != a[0] )  return false;

    // number of parts in a[] is largest part in b[]:
    ulong p = ma;

    // largest part in a[] is number of parts in b[]:
    ulong w = 0;  // write position

    ulong v = 0;  // last value
    ulong r = ma-1;  // read position
    do
    {
        ulong d = (a[r--] - v);  // d >= 0
        if ( d != 0 )  // new value
        {
            v += d;  // update value
            do  // write d times the part p
            {
                if ( b[w++] != p )  return false;
                --d;
            }
            while ( d );
        }
        --p;
    }
    while ( p );

    return  true;
}
// -------------------------


bool
partition_desc_is_self_conj(const ulong *a, ulong m)
// Return whether the partition in a[] (m parts) is self-conjugate.
{
    return  partition_desc_is_conj(a, m, a, m);
}
// -------------------------
