#if !defined  HAVE_BITSUBSET_GRAY_H__
#define       HAVE_BITSUBSET_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitsubset.h"
#include "bits/bithigh.h"
#include "fxttypes.h"

#define BITSUBSET_GRAY_METHOD1  // un/define to choose method (default:=defined)


class bit_subset_gray
// Generate all all subsets of bits of  a given word,
// in Gray code (minimal-change) order.
//
// E.g., for the word ('.' printed for unset bits)
//   ...11.1.
// these words are produced by subsequent next()-calls:
//   ......1.
//   ....1.1.
//   ....1...
//   ...11...
//   ...11.1.
//   ...1..1.
//   ...1....
//   ........
{
protected:
    bit_subset S;
    ulong G;  // subsets in Gray code order
    ulong H;  // highest bit in S.V;  needed for the prev() method

public:
    explicit bit_subset_gray(ulong v)
       : S(v), G(0), H(highest_one(v))
    { ; }

    ~bit_subset_gray()  { ; }

    ulong current()  const { return G; }
    ulong full_set()  const { return S.full_set(); }

    ulong next()
    {
        ulong U0 = S.current();
        if ( U0 == S.full_set() )  return first();
        ulong U1 = S.next();
#ifdef BITSUBSET_GRAY_METHOD1
        ulong X = ~U0 & U1;
#else
        ulong X = (U0 ^ U1) & U1;
#endif
        G ^= X;
        return G;
    }

    ulong first(ulong v)
    {
        S.first(v);
        H=highest_one(v);
        G=0;
        return G;
    }

    ulong first()
    {
        S.first();
        G=0;
        return G;
    }

    ulong prev()
    {
        ulong U1 = S.current();
        if ( U1 == 0 )  return last();
        ulong U0 = S.prev();
#ifdef BITSUBSET_GRAY_METHOD1
        ulong X = ~U0 & U1;
#else
        ulong X = (U0 ^ U1) & U1;
#endif
        G ^= X;
        return G;
    }

    ulong last(ulong v)
    {
        S.last(v);
        H = highest_one(v);
        G = H;
        return G;
    }

    ulong last()
    {
        S.last();
        G = H;
        return G;
    }
};
// -------------------------


#endif // !defined HAVE_BITSUBSET_GRAY_H__
