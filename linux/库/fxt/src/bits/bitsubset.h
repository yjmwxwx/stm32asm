#if !defined HAVE_BITSUBSET_H__
#define      HAVE_BITSUBSET_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class bit_subset
// Generate all all subsets of bits of  a given word.
//
// E.g., for the word ('.' printed for unset bits)
//   ...11.1.
// these words are produced by subsequent next()-calls:
//   ......1.
//   ....1...
//   ....1.1.
//   ...1....
//   ...1..1.
//   ...11...
//   ...11.1.
//   ........
//
{
protected:
    ulong U;  // current subset
    ulong V;  // the full set

public:
    explicit bit_subset(ulong v) : U(0), V(v)  { ; }
    ~bit_subset()  { ; }

    ulong current()  const  { return U; }
    ulong full_set()  const  { return V; }

//    ulong next()  { U = (U + 1 + ~V) & V;  return U; }
    ulong next()  { U = (U - V) & V;  return U; }
    ulong prev()  { U = (U - 1) & V;  return U; }

    ulong first(ulong v)  { V=v;  U=0;  return U; }
    ulong first()  { first(V);  return U; }

    ulong last(ulong v)  { V=v;  U=v;  return U; }
    ulong last()  { last(V);  return U; }

    void set(ulong u)  { U = u & V; }

    ulong complement()  { U ^= V;  return U; }

    ulong next_all_blocks()  { U = (U - V + ~V) & V;  return U; }
    ulong prev_all_blocks()  { U = (U + V) & V;  return U; }
    ulong negate_all_blocks()  { complement();  return next_all_blocks(); }
    ulong set_all_blocks_one()  { U = (-V + ~V) & V;  return U; }
    ulong set_right_block_borders()  { U |= ( (-V + ~V) & V );  return U; }


    ulong shift_left()  { U = ( (U << 1) + ~V ) & V;  return U; }
    ulong shift_left_fill()  { shift_left();  next();  return U; }

    ulong shift_left_blocks()  { U = ( U << 1 ) & V;  return U; }
    ulong shift_left_blocks_fill()  { shift_left_blocks();  U |= ((-V + ~V) & V);  return U; }


    ulong rev_gray_code()    { U ^= ( (U << 1) + ~V );  U &= V;  return U; }
};
// -------------------------


#endif  // !defined HAVE_BITSUBSET_H__
