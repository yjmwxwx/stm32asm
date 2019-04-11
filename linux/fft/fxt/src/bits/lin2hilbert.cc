// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "bits/bitzip.h"  // bit_unzip2()
#include "bits/graycode.h"


//static inline ulong high_bit(ulong x)  { return  x>>(BITS_PER_LONG-1); }

static const ulong htab[] = {
#define HT(xi, yi, c0, c1) ((xi<<3)+(yi<<2)+(c0<<1)+(c1))
    // index == HT(c0, c1, ai, bi)
    HT( 0, 0,  1, 0 ),
    HT( 0, 1,  0, 0 ),
    HT( 1, 1,  0, 0 ),
    HT( 1, 0,  0, 1 ),
    HT( 1, 1,  1, 1 ),
    HT( 0, 1,  0, 1 ),
    HT( 0, 0,  0, 1 ),
    HT( 1, 0,  0, 0 ),
    HT( 0, 0,  0, 0 ),
    HT( 1, 0,  1, 0 ),
    HT( 1, 1,  1, 0 ),
    HT( 0, 1,  1, 1 ),
    HT( 1, 1,  0, 1 ),
    HT( 1, 0,  1, 1 ),
    HT( 0, 0,  1, 1 ),
    HT( 0, 1,  1, 0 )
#undef HT
};
// -------------------------

//__attribute__((const))
void
lin2hilbert(ulong t, ulong &x, ulong &y)
// Transform linear coordinate t to Hilbert x and y
{
    ulong xv = 0, yv = 0;
#if 1  // table driven version (preferred)
    ulong c01 = (0<<2);  // (2<<2) for transposed output (swapped x, y)
    for (ulong i=0; i<(BITS_PER_LONG/2); ++i)
    {
        ulong abi = t >> (BITS_PER_LONG-2);
        t <<= 2;

        ulong st = htab[ (c01<<2) | abi ];
        c01 = st & 3;

        yv <<= 1;
        yv |= ((st>>2) & 1);
        xv <<= 1;
        xv |= (st>>3);
    }

#else

    ulong c[2] = {0, 0};  // {1, 0} for transposed output (swapped x, y)
    ulong m = 1UL << (BITS_PER_LONG/2 - 1);
    for (ulong i=0; i<(BITS_PER_LONG/2); ++i)
    {
        ulong ai = high_bit(t);  // see top of file
        t <<= 1;
        ulong bi = high_bit(t);
        t <<= 1;

        ulong xi = ai ^ c[1-bi];
        if ( xi )  xv |= m;
        ulong yi = xi ^ bi;
        if ( yi )  yv |= m;
        m >>= 1;

        c[0] ^= 1 - (ai | bi);  // == (1-ai) & (1-bi);
        c[1] ^= ai & bi;
    }
#endif
    x = xv;  y = yv;
}
// -------------------------


static const ulong ihtab[] = {
#define IHT(ai, bi, c0, c1) ((ai<<3)+(bi<<2)+(c0<<1)+(c1))
    // index == HT(c0, c1, xi, yi)
    IHT( 0, 0,  1, 0 ),
    IHT( 0, 1,  0, 0 ),
    IHT( 1, 1,  0, 1 ),
    IHT( 1, 0,  0, 0 ),
    IHT( 1, 0,  0, 1 ),
    IHT( 0, 1,  0, 1 ),
    IHT( 1, 1,  0, 0 ),
    IHT( 0, 0,  1, 1 ),
    IHT( 0, 0,  0, 0 ),
    IHT( 1, 1,  1, 1 ),
    IHT( 0, 1,  1, 0 ),
    IHT( 1, 0,  1, 0 ),
    IHT( 1, 0,  1, 1 ),
    IHT( 1, 1,  1, 0 ),
    IHT( 0, 1,  1, 1 ),
    IHT( 0, 0,  0, 1 )
#undef IHT
};
// -------------------------

//__attribute__((const))
ulong
hilbert2lin(ulong x, ulong y)
// Transform Hilbert x and y to linear coordinate t
{
    ulong t = 0;
    ulong c01 = 0;
    for (ulong i=0; i<(BITS_PER_LONG/2); ++i)
    {
        t <<= 2;
        ulong xi = x >> (BITS_PER_LONG/2-1);
        xi &= 1;
        ulong yi = y >> (BITS_PER_LONG/2-1);
        yi &= 1;
        ulong xyi = (xi<<1) | yi;
        x <<= 1;
        y <<= 1;

        ulong st = ihtab[ (c01<<2) | xyi ];
        c01 = st & 3;

        t |= (st>>2);
    }

    return t;
}
// -------------------------



// The lin2hilbert routine is based on the following hakmem entry:

//       Beeler, M., Gosper, R.W., and Schroeppel, R. HAKMEM. MIT AI Memo 239,
//       Feb. 29, 1972. Retyped and converted to html ('Web browser format) by
//       [1]Henry Baker, April, 1995.
//
//    TOPOLOGY
//
//      ITEM 115 (Gosper):
//
//       A spacefilling curve is a continuous map T -> X(T),Y(T), usually from
//       the unit interval onto the unit square, often presented as the limit
//       of a sequence of curves made by iteratively quadrisecting the unit
//       square. Each member of the sequence is then 4 copies of its
//       predecessor, connected in the shape of an inverted V, with the first
//       member being a V which connects 0,0 to 1,0. The limiting map, X(T) and
//       Y(T), can be computed instead by a simple, finite-state machine having
//       4 inputs (digits of T base 4), 4 outputs (one bit of X and one bit of
//       Y), and 4 states (2 bits) of memory (the number modulo 2 of 0's and
//       3's seen in T).
//
//       Let T, X, and Y be written in binary as:
//    T=.A B A B A B ...   X=.X X X X X X ...   Y=.Y Y Y Y Y Y ...
//        1 1 2 2 3 3          1 2 3 4 5 6          1 2 3 4 5 6
//
//       ALGORITHM S:
//            C  <- 0                          ;# of 0's mod 4
//             0
//
//            C  <- 0                          ;# of 3's mod 4
//             1
//
//    S1:     X  <- A  XOR C                   ;Ith bit of X
//             I     I      NOT B
//                               I
//
//            Y  <- X  XOR B                   ;Ith bit of Y
//             I     I      I
//
//            C  <- C  XOR (NOT A  AND NOT B ) ;count 00's
//             0     0           I          I
//
//            C  <- C  XOR (A  AND B )         ;count 11's
//             1     1       I      I
//
//            GO S1
//
//
//    OLD                  NEW
//    C  C   A  B   X  Y   C  C
//     0  1   I  I   I  I   0  1
//
//    0  0   0  0   0  0   1  0
//    0  0   0  1   0  1   0  0
//    0  0   1  0   1  1   0  0
//    0  0   1  1   1  0   0  1
//    0  1   0  0   1  1   1  1
//    0  1   0  1   0  1   0  1    This is the complete
//    0  1   1  0   0  0   0  1    state transition table.
//    0  1   1  1   1  0   0  0
//    1  0   0  0   0  0   0  0
//    1  0   0  1   1  0   1  0
//    1  0   1  0   1  1   1  0
//    1  0   1  1   0  1   1  1
//    1  1   0  0   1  1   0  1
//    1  1   0  1   1  0   1  1
//    1  1   1  0   0  0   1  1
//    1  1   1  1   0  1   1  0
//
//       To carry out either the forward or reverse map, label a set of columns
//       as in the table above. Fill in whichever you know of AB or XY, with
//       consecutive rows corresponding to consecutive 1's. Put 0 0 in the top
//       position of the OLD CC column. Exactly one row of the above table will
//       match the row you have written so far. Fill in the rest of the row.
//       Copy the NEW CC entry to the OLD CC column in the next row. Again,
//       only one row of the state table will match, and so forth. For example,
//       the map 5/6 -> (1/2,1/2) (really .11010101... -> (.1000...
//       ,.0111...)):
//    OLD                  NEW
//    C  C   A  B   X  Y   C  C
//     0  1   I  I   I  I   0  1
//
//    0  0   1  1   1  0   0  1
//    0  1   0  1   0  1   0  1
//    0  1   0  1   0  1   0  1
//    0  1   0  1   0  1   0  1
//    .  .   .  .   .  .   .  .
//    .  .   .  .   .  .   .  .
//        =  5/6  1/2  1/2
//
//       We note that since this is a one-to-one map on bit strings, it is not
//       a one-to-one map on real numbers. For instance, there are 2 ways to
//       write 1/2, .1000... and .0111..., and thus 4 ways to write (1/2,1/2),
//       giving 3 distinct inverses, 1/6, 1/2, and 5/6. Since the algorithm is
//       finite state, X and Y are rational iff T is, e.g., 898/4369 ->
//       (1/5,1/3). The [5]parity number, (see [6]SERIES section) and 1-(parity
//       number) are the only reals satisfying X(T)=T, Y(T)=1. This is related
//       to the fact that they have no 0's and 3's base 4, and along with 0,
//       1/2, and 1=.111..., are the only numbers preserved by the deletion of
//       their even numbered bit positions.
//



//__attribute__((const))
ulong
hilbert_gray_code(ulong t)
// A Gray code based on the function lin2hilbert().
// Equivalent to the following sequence of statements:
//  { lin2hilbert(t, x, y);
//    x=gray_code(x);  y=gray_code(y);
//    return bitzip2(x, y); }
{
    ulong g = 0;
    ulong c01 = 2;  // 0 for transposed output (swapped x, y)
    for (ulong i=0; i<(BITS_PER_LONG/2); ++i)
    {
        ulong abi = t >> (BITS_PER_LONG-2);
        t <<= 2;

        ulong st = htab[ (c01<<2) | abi ];
        c01 = st & 3;

        g <<= 2;
        g |= (st>>2);
    }
#if  ( BITS_PER_LONG <= 32 )
    g ^= ( (g & 0x55555555UL) >> 2 );
    g ^= ( (g & 0xaaaaaaaaUL) >> 2 );
#else
    g ^= ( (g & 0x5555555555555555UL) >> 2 );
    g ^= ( (g & 0xaaaaaaaaaaaaaaaaUL) >> 2 );
#endif
    return g;
}
// -------------------------

//__attribute__((const))
ulong
inverse_hilbert_gray_code(ulong g)
// Inverse of hilbert_gray_code()
{
    ulong x, y;
    bit_unzip2(g, x, y);
    x = inverse_gray_code(x);
    y = inverse_gray_code(y);
    ulong t = hilbert2lin(x, y);
    return  t;
}
// -------------------------

