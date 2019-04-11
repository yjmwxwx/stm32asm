#if !defined  HAVE_CAYLEY_DICKSON_MULT_H__
#define       HAVE_CAYLEY_DICKSON_MULT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "bits/bithigh.h"  // highest_one()
#include "fxttypes.h"

inline int CD_sign_rec(ulong r, ulong c, ulong n)
// Signs in the multiplication table for the
//   algebra of n-ions (where n is a power of 2)
//   that is obtained by the Cayley-Dickson construction:
// If component r is multiplied with component c, then the
//   result is CD_sign_rec(r,c,n) * (r XOR c).
// Multiplication rule is
//   (a,b) * (A,b) = (a*A - B*conj(b),  conj(a)*B + A*b)
//   where conj(a,b) := (conj(a), -b) and conj(x):=x for x real
// [ Transposed rule/table is obtained if rule is changed to
//    (a,b) * (A,b) = (a*A - conj(B)*b,  b*conj(A) + B*a)  ]
// Must have: r < n  and  c < n.
// We have ex * e0 = e0 * ex = ex,  and ex * ex = -1 for x != 0,
//   and ex * ey == -ey * ex for x != y, x != 0, y != 0
// Example (octionions, n==8):
// (er*ec) e0   e1   e2   e3    e4   e5   e6   e7
//   e0:  +e0  +e1  +e2  +e3   +e4  +e5  +e6  +e7
//   e1:  +e1  -e0  -e3  +e2   -e5  +e4  +e7  -e6
//   e2:  +e2  +e3  -e0  -e1   -e6  -e7  +e4  +e5
//   e3:  +e3  -e2  +e1  -e0   -e7  +e6  -e5  +e4
//
//   e4:  +e4  +e5  +e6  +e7   -e0  -e1  -e2  -e3
//   e5:  +e5  -e4  +e7  -e6   +e1  -e0  +e3  -e2
//   e6:  +e6  -e7  -e4  +e5   +e2  -e3  -e0  +e1
//   e7:  +e7  +e6  -e5  -e4   +e3  +e2  -e1  -e0
// Signs at row r, column c equal CD_sign_rec(r,c,8):
//   + + + + + + + +
//   + - - + - + + -
//   + + - - - - + +
//   + - + - - + - +
//   + + + + - - - -
//   + - + - + - + -
//   + - - + + - - +
//   + + - - + + - -
// This is a (8 x 8) Hadamard matrix.
// The second row is the (signed) Thue-Morse sequence,
// see OEIS sequences A118685, A010060, and A106400.

{
    if ( (r==0) || (c==0) )  return +1;

#ifdef USE_REC_OPT
    if ( n <= 8 )
    {
        unsigned long long t = 0xcc66aaf05a3c9600ULL;
        t >>= (r*8 + c);
        t &= 1ULL;
        t *= 2;
        return  1 - (int)t;
    }
#endif  // USE_REC_OPT

    if ( c >= r )
    {
        if ( c > r )   return  -CD_sign_rec(c, r, n);
        else           return  -1;  // r==c
    }
    // here r>c (triangle below diagonal)

    ulong h = n >> 1;
    if ( c >= h )  // right
    {
        // (upper right not reached)
        return   CD_sign_rec(c-h, r-h, h);  // lower right
    }
    else  // left
    {
        if ( r >= h )  return  +CD_sign_rec(c, r-h, h);  // lower left
        else           return  +CD_sign_rec(r, c,   h);  // upper left
    }
}
// -------------------------

//void gen_table()
//// Create 64-bit table for octonions.
//// Output is 0xcc66aaf05a3c9600ULL
//{
//    unsigned long long t = 0;
//    for (ulong r=0; r<8; ++r)
//    {
//        for (ulong c=0; c<8; ++c)
//        {
//            int s = CD_sign_rec(r, c, 8);
//            if ( s==-1 )  t |= (1ULL << (r*8 + c));
//        }
//    }
//    cout << "unsigned long long t = 0x" << hex << t << dec << "ULL;" << endl;
//    // unsigned long long t = 0xcc66aaf05a3c9600ULL;
//}
//// -------------------------


#define cp2(a, b, u, v)  CD_aux_cp2(a, b, u, v)  // keep namespace clean
inline void cp2(ulong a, ulong b, ulong &u, ulong &v)  { u=a; v=b; }
//
inline int CD_sign_it(ulong r, ulong c, ulong n)
// iterative version of CD_sign_rec()
{
    int s = +1;
    while ( true )
    {
        if ( (r==0) || (c==0) )  return s;
        if ( c==r )  return -s;
        if ( c > r )   { swap2(r, c);  s = -s; }
        n >>= 1;
        if ( c >= n )       cp2(c-n, r-n,  r, c);
        else if ( r >= n )  cp2(c,   r-n,  r, c);
    }
}
// -------------------------
#undef cp2


inline bool CD_zerodiv_q(ulong r, ulong c)
// Return whether (r+c) where r and c are units
// is a zero divisor in the Cayley-Dickson algebra.
{
 start:
    if ( (r < 8) && (c < 8) )  return false;
    if ( c > r )  swap2(r, c);
    // Here  r >= c
    const ulong h = highest_one(r);
    if ( (r^c) & h )  // lower left or upper right
    {
        r &= ~h;
        if ( r==c )  return  false;
        if ( c==0 )  return  false;
        if ( r==0 )  return  false;
        return true;
    }
    // move to upper left:
    r &= ~h;
    c &= ~h;
    goto start;
}
// -------------------------


#endif  // !defined HAVE_CAYLEY_DICKSON_MULT_H__
