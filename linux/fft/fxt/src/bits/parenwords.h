#if !defined  HAVE_PARENWORDS_H__
#define       HAVE_PARENWORDS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitcombcolex.h"  // first_comb()
#include "bits/bitlow.h"  // lowest_one(), lowest_block()

// For Knuth's version of next_parenword():
#include "bits/bitcount.h"  // bit_count()


static inline bool is_parenword(ulong x)
// Return whether x is a valid paren word.
//
// Binary words < 16, those that are valid
//  'paren words' are marked with 'P':
//  .... P   [empty string]
//  ...1 P   ()
//  ..1.
//  ..11 P   (())
//  .1..
//  .1.1 P   ()()
//  .11.
//  .111 P   ((()))
//  1...
//  1..1
//  1.1.
//  1.11 P   (()())
//  11..
//  11.1 P   ()(())
//  111.
//  1111 P   (((())))
{
    long s = 0;
    for (ulong j=0; x!=0; ++j)
    {
        s += ( x&1 ? +1 : -1 );
        if ( s < 0 )  return false;  // invalid word
        x >>= 1;
    }
    return  true;
}
// -------------------------


static inline void parenword2str(ulong x, char *str)
// Fill paren string corresponding to x into str.
//
// Binary words < 32 that are valid
//  'paren words' together with paren-string:
//  .....   [empty string]
//  ....1   ()
//  ...11   (())
//  ..1.1   ()()
//  ..111   ((()))
//  .1.11   (()())
//  .11.1   ()(())
//  .1111   (((())))
//  1..11   (())()
//  1.1.1   ()()()
//  1.111   ((()()))
//  11.11   (()(()))
//  111.1   ()((()))
//  11111   ((((()))))
// Note 1: lower bits in word (right end) correspond
//         to the begin of string (left end).
// Note 2: Word is extended with zeros (to the left) when necessary,
//         so the length of str must be >= 1 + 2*(number of set bits)
{
    int s = 0;
    ulong j = 0;
    for (j=0; x!=0; ++j)
    {
        s += ( x&1 ? +1 : -1 );
        // if ( s<0 )  {"Invalid word"}
        str[j] = ")("[x&1];
        x >>= 1;
    }
    while ( s-- > 0 )  str[j++] = ')';  // finish string
    str[j] = 0;  // terminate string
}
// -------------------------


static inline ulong first_parenword(ulong n)
// Return least binary word corresponding to n pairs of parens.
// Example, n=5:  .....11111   ((((()))))
{
    return first_comb(n);
}
// -------------------------


static inline ulong last_parenword(ulong n)
// Return biggest binary word corresponding to n pairs of parens.
// Must have: 1 <= n <= BITS_PER_LONG/2.
// Example, n=5:  .1.1.1.1.1   ()()()()()
{
#if BITS_PER_LONG == 64
    return  0x5555555555555555UL >> (BITS_PER_LONG-2*n);
#else
    return  0x55555555UL >> (BITS_PER_LONG-2*n);
#endif

//    ulong x = 1UL << (2*n-2),  s = 2;
//    do
//    {
//        x |= (x>>s);  s <<= 1;
//        x |= (x>>s);  s <<= 1;
//        x |= (x>>s);  s <<= 1;
//    }
//    while ( s != BITS_PER_LONG );
//    return x;

//    ulong x = 0,  s = 1;
//    while ( n-- ) { x |= s; s<<=2; }
//    return x;
}
// -------------------------


static inline ulong next_parenword(ulong x)
// Next (colex order) binary word that is a paren word.
// With n=4 and starting with first_parenword(n)
//  one gets the following sequence:
//  .....1111   (((())))
//  ....1.111   ((()()))
//  ....11.11   (()(()))
//  ....111.1   ()((()))
//  ...1..111   ((())())
//  ...1.1.11   (()()())
//  ...1.11.1   ()(()())
//  ...11..11   (())(())
//  ...11.1.1   ()()(())
//  ..1...111   ((()))()
//  ..1..1.11   (()())()
//  ..1..11.1   ()(())()
//  ..1.1..11   (())()()
//  ..1.1.1.1   ()()()()
//  .........    [zero]
{
// could test  HAVE_AMD64_POPCNT  to select version
#if 1  // bit-scan version (default):

    if ( x & 2 )  // Easy case, move highest bit of lowest block to the left:
    {
        ulong b = lowest_zero(x);
        x ^= b;
        x ^= (b>>1);
        return x;
    }
    else  // Gather all low "01"s and split lowest nontrivial block:
    {
        if ( 0==(x & (x>>1)) )  return 0;
        ulong w = 0;  // word where the bits are assembled
        ulong s = 0;  // shift for lowest block
        ulong i = 1;  // == lowest_one(x)
        do  // collect low "01"s:
        {
            x ^= i;
            w <<= 1;
            w |= 1;
            ++s;
            i <<= 2;  // == lowest_one(x);
        }
        while ( 0==(x&(i<<1)) );

        ulong z = x ^ (x+i);  // lowest block
        x ^= z;
        z &= (z>>1);
        z &= (z>>1);
        w ^= (z>>s);
        x |= w;
        return x;
    }

#else  // version given by Knuth, easy case treated extra for speedup:

    if ( x & 2 )  // Easy case, move highest bit of lowest block to the left:
    {
        ulong b = lowest_zero(x);
        x ^= b;
        x ^= (b>>1);
        return x;
    }
    else
    {
        const ulong m0 = -1UL/3;
        ulong t = x ^ m0;               // XOR t, x, m0;
        if ( (t&x)==0 )  return 0;      // current is last
        ulong u = (t-1) ^ t;            // SUBU u, t, 1;  XOR u, t, u;
        ulong v = x | u;                // OR v, x, u;
        ulong y = bit_count( u & m0 );  // SADD y, u, m0;
        ulong w = v + 1;                // ADDU w, v, 1;
        t = v & ~w;                     // ANDN t, v, w;
        y = t >> y;                     // SRU y, t, y;
        y += w;                         // ADDU y, w, y;
        return y;
    }
#endif
}
// -------------------------



#endif  // !defined HAVE_PARENWORDS_H__
