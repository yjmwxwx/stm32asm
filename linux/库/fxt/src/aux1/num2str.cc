
// This file is part of the FXT library.
// Copyright (C) 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"  // swap2()
#include "fxttypes.h"  // ulong
//#include "jjassert.h"


void
num2str(ulong x, ulong rd, char *str)
// Write radix-rd representation of x to str[].
// Must have rd <= 36.
{
    static const char dd[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    //    jjassert( rd <= ( sizeof(dd)/sizeof(dd[0])) );

    if ( x==0 )  // zero is a special case
    {
        str[0] = dd[0];
        str[1] = '\0';
        return;
    }

    ulong ct = 0;
    while ( x!=0 )
    {
        str[ct] = dd[x % rd];
        x /= rd;
        ++ct;
    }

    // reverse str[]:
    for (ulong i=0, j=ct-1;  i<j;  ++i, --j)  swap2(str[i], str[j]);

    str[ct] = '\0';
}
// -------------------------

