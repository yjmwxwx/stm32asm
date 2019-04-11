#if !defined  HAVE_ARRANGEMENT_LEX_H__
#define       HAVE_ARRANGEMENT_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/perm-lex-inv.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class arrangement_lex
// Arrangements (all permutations of all subsets).
// Lexicographic order.
// Cf. OEIS sequence A000522.
{
private:
    perm_lex_inv P;
    ulong e_;  // length of current arrangement

public:
    arrangement_lex(ulong n)
    // OK for n==0.
        : P(n)
    {
        first();
    }

    const ulong *data()  const  { return P.data(); }
    ulong num()  const  { return e_; }

    void first()
    {
        e_ = 0;  // initial arrangement is the empty list
    }

    ulong next()
    {
        e_ += 1;
        if ( e_ <= P.n_ )  return e_;  // easy case: just extend

        if ( P.next() )
        {
            e_ = P.pos() + 1;
            return e_;
        }

        return 0;  // current is last
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), e_, dfz); }
};
// -------------------------


#endif // !defined HAVE_ARRANGEMENT_LEX_H__
