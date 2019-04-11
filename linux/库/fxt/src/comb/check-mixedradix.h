#if !defined  HAVE_CHECK_MIXEDRADIX_H__
#define       HAVE_CHECK_MIXEDRADIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/mixedradix.h"  // product()

#include "ds/bitarray.h"
#include "fxttypes.h"


class check_mixedradix : public bitarray
// Checking validity of list of mixed radix numbers.
{
public:
    const ulong *m1_;
    const ulong *x_;
    ulong n_;

private:  // have pointer data (read-only, however)
    check_mixedradix(const check_mixedradix&);  // forbidden
    check_mixedradix & operator = (const check_mixedradix&);  // forbidden

public:
    explicit check_mixedradix(const ulong *m1, ulong n)
        : bitarray( product_p1(m1, n) )
    {
        n_ = n;
        m1_ = m1;
        x_ = 0;
    }

    ~check_mixedradix()  {;}

    void first(const ulong *x)
    {
        bitarray::clear_all();
        x_ = x;
    }

    bool is_repeat()
    // Mark number as seen.
    // Return true if permutation is a repeat.
    {
        ulong w = mixedradix2num(x_, m1_, n_);
        bool q = bitarray::test_set(w);
        return q;
    }

    bool all_seen()  const
    // Return whether all numbers have been seen.
    {
        return  bitarray::all_set_q();
    }
};
// -------------------------


#endif  // !defined HAVE_CHECK_MIXEDRADIX_H__
