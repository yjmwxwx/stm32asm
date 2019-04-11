#if !defined  HAVE_BITCOMBSHIFTS_H__
#define       HAVE_BITCOMBSHIFTS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitlow.h"  // low_ones()
#include "bits/bithigh.h"  // highest_one_idx()
#include "bits/bitcombcolex.h"  // first_comb(), last_comb()
#include "fxttypes.h"  // ulong

//const char *cc = 0;

class bit_comb_shifts
// Bit combinations in shifts-order.
{
public:
    ulong x_;  // the combination
    ulong s_;  // how far shifted to the right
    ulong n_, k_;  // combinations (n choose k)
    ulong last_;   // last combination

public:
    explicit bit_comb_shifts(ulong n, ulong k)
    {
        n_ = n;  k_ = k;
        first();
    }

    ~bit_comb_shifts()  { ; }


    ulong first(ulong n, ulong k)
    {
        s_ = 0;
        x_ =  last_comb(k, n);

        if ( k>1 )  last_ = first_comb(k-1) | (1UL<<(n_-1));  // [10000111]
        else        last_ = k;  //  [000001] or [000000]

        return x_;
    }

    ulong first()  { return first(n_, k_); }

    ulong next()
    {
        if ( 0==(x_&1) )  // easy case:
        {
            ++s_;
            x_ >>= 1;
//            cc = 0;
            return  x_;
        }
        else  // splitting cases:
        {
            if ( x_ == last_ )  return 0;  // combination was last

            x_ <<= s_;  s_ = 0;  // shift back to the left
            ulong b = x_ & -x_;  // lowest bit


            if ( b!=1UL )  // simple split
            {
                x_ -= (b>>1);  // move rightmost bit to the right
//                cc = "  < S";
                return x_;
            }
            else  // split second block and attach first
            {
                ulong t = low_ones(x_);  //  block of ones at lower end
                x_ ^= t;  // remove block
                ulong b2 = x_ & -x_;  // (second) lowest bit

                b2 >>= 1;
                x_ -= b2;  // move bit to the right

#if 1  // default
                // attach block:
                do  { t<<=1; }  while ( 0==(t&x_) );
                x_ |= (t>>1);
#else
                // attach block (with bit-scan):
                x_ |= ( t << (highest_one_idx(b2)-highest_one_idx(t)-1) );
#endif
//                cc = "  < S-2";
                return x_;
            }
        }
    }
};
// -------------------------


#endif  // !defined HAVE_BITCOMBSHIFTS_H__
