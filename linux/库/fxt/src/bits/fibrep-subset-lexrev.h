#if !defined  HAVE_FIBREP_SUBSET_LEXREV_H__
#define       HAVE_FIBREP_SUBSET_LEXREV_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

static inline ulong next_subset_lexrev_fib(ulong x)
// Return next Fibonacci word in subset-lex order.
// Start with a one-bit word at position n-1 to
// generate all Fibonacci words of length n
// E.g., for n==6 the words (and subsets) are
//       word     subset of {0,1,2,3,4,5}
//   1:  1.....  =  { 0 }
//   2:  1.1...  =  { 0, 2 }
//   3:  1.1.1.  =  { 0, 2, 4 }
//   4:  1.1..1  =  { 0, 2, 5 }
//   5:  1..1..  =  { 0, 3 }
//   6:  1..1.1  =  { 0, 3, 5 }
//   7:  1...1.  =  { 0, 4 }
//   8:  1....1  =  { 0, 5 }
//   9:  .1....  =  { 1 }
//  10:  .1.1..  =  { 1, 3 }
//  11:  .1.1.1  =  { 1, 3, 5 }
//  12:  .1..1.  =  { 1, 4 }
//  13:  .1...1  =  { 1, 5 }
//  14:  ..1...  =  { 2 }
//  15:  ..1.1.  =  { 2, 4 }
//  16:  ..1..1  =  { 2, 5 }
//  17:  ...1..  =  { 3 }
//  18:  ...1.1  =  { 3, 5 }
//  19:  ....1.  =  { 4 }
//  20:  .....1  =  { 5 }
//  21:  ......  =  { }
//
// Note (1): the first element of the subset corresponds
// to the highest set bit.
// Note (2): the lex order for the delta sets would simply
// be the counting order.
{
    ulong x0 = x & -x;  // lowest bit
    ulong xs = x0 >> 2;
    if ( xs != 0 )  // easy case: set bit right of lowest bit
    {
        x |= xs;
        return  x;
    }
    else  // lowest bit at index 0 or 1
    {
        if ( x0 == 2 )  // at index 1
        {
            x -= 1;
            return x;
        }

        // Same as next_lexrev():
        x ^= x0;  // clear lowest bit
        x0 = x & -x;  // new lowest bit ...
        x0 >>= 1;  x -= x0;  // ... is moved one to the right
        return  x;
    }
}
// -------------------------


static inline ulong prev_subset_lexrev_fib(ulong x)
// Return previous Fibonacci word in subset-lex order.
// Start with zero to generate all words of length n.
// E.g., for n==6:
//       word     subset of {0,1,2,3,4,5}
//   0:  ......  =   { }
//   1:  .....1  =   { 5 }
//   2:  ....1.  =   { 4 }
//   3:  ...1.1  =   { 3, 5 }
//   4:  ...1..  =   { 3 }
//   5:  ..1..1  =   { 2, 5 }
//   6:  ..1.1.  =   { 2, 4 }
//   7:  ..1...  =   { 2 }
//   8:  .1...1  =   { 1, 5 }
//   9:  .1..1.  =   { 1, 4 }
//  10:  .1.1.1  =   { 1, 3, 5 }
//  11:  .1.1..  =   { 1, 3 }
//  12:  .1....  =   { 1 }
//  13:  1....1  =   { 0, 5 }
//  14:  1...1.  =   { 0, 4 }
//  15:  1..1.1  =   { 0, 3, 5 }
//  16:  1..1..  =   { 0, 3 }
//  17:  1.1..1  =   { 0, 2, 5 }
//  18:  1.1.1.  =   { 0, 2, 4 }
//  19:  1.1...  =   { 0, 2 }
//  20:  1.....  =   { 0 }
//
{
    ulong x0 = x & -x;  // lowest bit
    if ( x & (x0<<2) )  // easy case: next higher bit is set
    {
        x ^= x0;  // clear lowest bit
        return x;
    }
    else
    {
        x += x0;       // move lowest bit to the left and
        x |= (x0!=1);  // set rightmost bit unless blocked by next bit
        return x;
    }
}
// -------------------------



#endif  // !defined HAVE_FIBREP_SUBSET_LEXREV_H__
