#if !defined  HAVE_DEBRUIJN_H__
#define       HAVE_DEBRUIJN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "comb/necklace.h"


class debruijn : public necklace
// Lexicographic minimal De Bruijn sequence.
{
public:
    ulong i_;   // position of current digit in current string

public:
    explicit debruijn(ulong m, ulong n)
        : necklace(m, n)
    { first_string(); }

    ~debruijn()  { ; }

    ulong first_string()
    {
        necklace::first();
        i_ = 1;
        return j_;
    }

    ulong next_string()  // make new string, return its length
    {
        necklace::next();
        i_ = (j_ != 0);
        return j_;
    }

    ulong next_digit()
    // Return current digit and move to next digit.
    // Return m if previous was last.
    {
        if ( i_ == 0 )  return necklace::m1_ + 1;
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


#endif  // !defined HAVE_DEBRUIJN_H__
