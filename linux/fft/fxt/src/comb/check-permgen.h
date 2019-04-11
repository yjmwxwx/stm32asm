#if !defined  HAVE_CHECK_PERMGEN_H__
#define       HAVE_CHECK_PERMGEN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/num2perm.h" // perm2num_swp()
#include "ds/bitarray.h"
#include "aux0/factorial.h"

#include "fxttypes.h"

class check_permgen : bitarray
// Checking validity of list of permutations.
{
public:
    const ulong *x_;
    ulong n_;
    ulong *r_;  // for reversed permutations

private:  // have pointer data
    check_permgen(const check_permgen&);  // forbidden
    check_permgen & operator = (const check_permgen&);  // forbidden

public:
    explicit check_permgen(ulong n)
        : bitarray( factorial(n) )
    {
        x_ = 0;
        n_ = n;
        r_ = new ulong[n_];
    }

    ~check_permgen()
    {
        delete [] r_;
    }

    void first(const ulong *x)
    {
        bitarray::clear_all();
        x_ = x;
    }

    bool is_repeat()
    // Mark permutation as seen.
    // Return true if permutation is a repeat.
    {
        ulong w = perm2num_swp(x_, n_);
        bool q = bitarray::test_set(w);
        return q;
    }

    bool is_repeat_rev()
    // Mark reversed permutation as seen.
    // Return true if reversed permutation is a repeat.
    {
        for (ulong k=0, j=n_-1;  k<n_;  ++k, --j)  r_[k] = x_[j];
        ulong w = perm2num_swp(r_, n_);
        bool q = bitarray::test_set(w);
        return q;
    }
};
// -------------------------


#endif  // !defined HAVE_CHECK_PERMGEN_H__
