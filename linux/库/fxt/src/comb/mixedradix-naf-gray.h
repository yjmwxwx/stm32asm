#if !defined HAVE_MIXEDRADIX_NAF_GRAY_H__
#define      HAVE_MIXEDRADIX_NAF_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"
//#include "perm/reverse.h"

#include "fxttypes.h"


// If defined, an array is used instead of a pointer:
//#define MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN 128  // default off


class mixedradix_naf_gray
// Gray code for mixed radix non-adjacent forms (NAF).
{
public:
#ifndef MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN
    ulong *a_;  // digits
    ulong *d_;  // directions, or zero for track fixed at zero
    ulong *m1_;  // nines (radix minus one) for each digit
#else
    ulong a_[MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN+3];
    ulong d_[MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN+2];
    ulong m1_[MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN+2];
#endif
    ulong n_;   // Number of digits
    ulong j_;   // position of last change
    int dm_;    // direction of last change

private:  // have pointer data
    mixedradix_naf_gray(const mixedradix_naf_gray&);  // forbidden
    mixedradix_naf_gray & operator = (const mixedradix_naf_gray&);  // forbidden

public:
    explicit mixedradix_naf_gray(ulong n, ulong mm, const ulong *m=0)
    // Must have: n>=1
    {
        n_ = n;

#ifndef MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN
        a_ = new ulong[n_+3];
        d_ = new ulong[n_+2];
        m1_ = new ulong[n_+2];
#endif
        set_sentinels();

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_naf_gray()
    {
#ifndef MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN
        delete [] a_;
        delete [] d_;
        delete [] m1_;
#endif
    }

    const ulong * data()  const  { return a_; }

private:
    void set_sentinels()
    {
        a_[n_] = 0;  // ==0 to keep highest track unblocked
        m1_[n_] = 0;  // unused
        d_[n_] = 0;  // track skipped by both can_incr_q() and can_decr_q()

        // here both next() and prev() shall stop scannning
        a_[n_+1] = 1;  // != 0  for prev()
        m1_[n_+1] = 2;  // > a[n+1] for next() (can_incr_q())
        d_[n_+1] = +1;  // can both incr. and decr. here

        // for look-ahead in can_incr_q() and can_decr_q():
        a_[n_+2] = 0;  // == 0
    }

    bool can_incr_q(ulong j)  const
    // Return whether digit a[j] can be incremented.
    {
        if ( d_[j] == 0 )  return false;  // zero belonging to next lower track
        if ( a_[j] + d_[j] > m1_[j] )  return false;  // digit maxed out
        if ( a_[j+1] == 0 )  return true;  // next track free
        if ( a_[j] != 0 )  return true;  // already nonzero (and !=nine)
        return false;
    }

    bool can_decr_q(ulong j)  const
    // Return whether digit a[j] can be decremented.
    {
        if ( d_[j] == 0 )  return false;
        if ( a_[j] - d_[j] > m1_[j] )  return false;  // negated wrt. to can_incr_q()
        if ( a_[j+1] == 0 )  return true;
        if ( a_[j] != 0 )  return true;
        return false;
    }

    bool is_odd(ulong x)  const  { return (x & 1) != 0; }

    void init_vals(ulong dd)
    // Must have: n>=1
    {
        ulong d = dd;  // direction of track
        ulong k = n_ - 1;
        do
        {
            const ulong ak = (d==+1 ? 0 : m1_[k]);
            a_[k] = ak;
            d_[k] = d;

            // skip one track at nonzero values:
            if ( ak != 0 )
            {
                --k;
                if ( (long)k >= 0 )
                {
                    a_[k] = 0;
                    d_[k] = ( is_odd(ak) ? -1UL : +1 );
                }
            }
            --k;

            // reverse direction at zero and at odd values:
            if ( ( (ak==0 ) || is_odd(ak) ) )  d = -d;
        }
        while ( (long)k >= 0 );

        for (ulong j=0; j<n_; ++j)  if ( a_[j]!=0 )  d_[j+1] = 0;
        if ( dd==-1UL ) for (ulong j=0; j<n_; ++j)  d_[j] = -d_[j];

        j_ = n_;
        dm_ = 0;
    }

public:
    void first()  { init_vals(+1); }
    void last()  { init_vals(-1UL); }


    bool next()  // increment
    {
        ulong j = 0;
        while ( ! can_incr_q(j)  )  // can read sentinels
        {
            d_[j] = -d_[j];
            ++j;
        }
        j_ = j;
        dm_ = (int)d_[j];

        if ( j>=n_ )  // current is last
        {
            set_sentinels();  // restore sentinels
            return false;
        }

        const ulong aj = a_[j] + d_[j];
        a_[j] = aj;
        if ( aj != 0 )  { d_[j+1] = 0; }
        else  d_[j+1] = -d_[j];

        return true;
    }


    bool prev()  // decrement
    {
        ulong j = 0;
        while ( ! can_decr_q(j)  )  // can read sentinels
        {
            d_[j] = -d_[j];
            ++j;
        }
        j_ = j;
        dm_ =  -(int)d_[j];  // negated wrt. next()

        if ( j>=n_ )  // current is first
        {
            set_sentinels();  // restore sentinels
            return false;
        }

        const ulong aj = a_[j] - d_[j];  // negated wrt. next()
        a_[j] = aj;
        if ( aj != 0 )  { d_[j+1] = 0; }
        else  d_[j+1] = -d_[j];

        return true;
    }

    ulong pos()  const  { return j_; }  // position of last change
    int dir()  const  { return dm_; }  // direction of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    ulong to_num()  const
    // Return (integer) value of mixed radix number.
    { return mixedradix2num(a_, m1_, n_); }


    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;

        for (ulong j=1; j<n_; ++j)
            if ( (a_[j-1]!=0) && (a_[j]!=0) )  return false;

        return true;
    }
};
// -------------------------

//#undef MIXEDRADIX_NAF_GRAY_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_MIXEDRADIX_NAF_GRAY_H__
