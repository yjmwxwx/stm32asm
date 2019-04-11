// This file is part of the FXT library.
// Copyright (C) 2010, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsperlong.h"
#include "fxttypes.h"
#include "bits/zerobyte.h"


ulong
long_strlen(const char *str)
// Return length of string starting at str.
{
    ulong x;
    const char *p = str;

    // alignment: scan bytes up to word boundary:
    while ( (ulong)p % BYTES_PER_LONG )
    {
        if ( 0 == *p )  return  (ulong)(p-str);
        ++p;
    }

    x = *(ulong *)p;  // jjcast
    while ( ! contains_zero_byte(x) )
    {
        p += BYTES_PER_LONG;
        x = *(ulong *)p;  // jjcast
    }

    // now a zero byte is somewhere in x:
//    while ( x & 0xff )  { ++p;  x >>= 8; }
    while ( 0 != *p )  { ++p; }

    return  (ulong)(p-str);
}
// -------------------------

