#if !defined  HAVE_BINARY_DEBRUIJN_H__
#define       HAVE_BINARY_DEBRUIJN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "comb/binary-necklace.h"


class binary_debruijn : public binary_necklace
// Lexicographically minimal binary De Bruijn sequence.
{
public:
    ulong i_;   // position of current digit in current string

public:
    explicit binary_debruijn(ulong n)
        : binary_necklace(n)
    { first_string(); }

    ~binary_debruijn()  { ; }

    ulong first_string()
    {
        binary_necklace::first();
        i_ = 1;
        return j_;
    }

    ulong next_string()  // make new string, return length
    {
        binary_necklace::next();
        i_ = (j_ != 0);
        return j_;
    }

    ulong next_digit()
    // Return current digit and move to next digit.
    // Return 2 if previous was last.
    {
        if ( i_ == 0 )  return 2;
        ulong d = a_[ i_ ];
        if ( i_ == j_ )  next_string();
        else  ++i_;
        return d;
    }

    ulong first_digit()
    {
        first_string();
        return next_digit();
    }
};
// -------------------------


#endif  // !defined HAVE_BINARY_DEBRUIJN_H__
