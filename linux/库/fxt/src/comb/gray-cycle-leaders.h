#if !defined  HAVE_GRAY_CYCLE_LEADERS_H__
#define       HAVE_GRAY_CYCLE_LEADERS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bit2pow.h"
#include "bits/bitsubset.h"
#include "fxttypes.h"
//#include "bits/bitsperlong.h"

class gray_cycle_leaders
// Generate cycle leaders for Gray permutation
// where highest bit is at position ldn.
{
public:
    bit_subset B_;
    ulong za_;  // mask for cycle maxima
    ulong zi_;  // mask for cycle minima
    ulong len_;  // cycle length
    ulong num_;  // number of cycles

public:
    explicit gray_cycle_leaders(ulong ldn)  // 0<=ldn<BITS_PER_LONG
        : B_(0)
    { init(ldn); }

    ~gray_cycle_leaders() {;}

    void init(ulong ldn)
    {
        za_ = 1;
        ulong cz = 0;   // ~z
        len_ = 1;
        num_ = 1;
        for (ulong ldm=1; ldm<=ldn; ++ldm)
        {
            za_ <<= 1;
            cz <<= 1;
            if ( is_pow_of_2(ldm) )
            {
                ++za_;
                len_ <<= 1;
            }
            else
            {
                ++cz;
                num_ <<= 1;
            }
        }

        zi_ = 1UL << ldn;

        B_.first(cz);
    }

    ulong current_max()  const  { return B_.current() | za_; }
    ulong current_min()  const  { return B_.current() | zi_; }

    bool next()  { return ( 0 != B_.next() ); }

    ulong num_cycles()  const  { return num_; }
    ulong cycle_length()  const  { return len_; }
};
// -------------------------


#endif  // !defined HAVE_GRAY_CYCLE_LEADERS_H__
