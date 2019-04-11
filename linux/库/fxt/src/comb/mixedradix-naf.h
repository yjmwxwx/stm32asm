#if !defined HAVE_MIXEDRADIX_NAF_H__
#define      HAVE_MIXEDRADIX_NAF_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


// If defined, an array is used instead of a pointer:
//#define MIXEDRADIX_NAF_MAX_ARRAY_LEN 128  // default off


class mixedradix_naf
// Mixed radix non-adjacent forms (NAF), counting order.
{
public:
#ifndef MIXEDRADIX_NAF_MAX_ARRAY_LEN
    ulong *a_;  // digits
    ulong *m1_;  // nines (radix minus one) for each digit
#else
    ulong a_[MIXEDRADIX_NAF_MAX_ARRAY_LEN+3];
    ulong m1_[MIXEDRADIX_NAF_MAX_ARRAY_LEN+3];
#endif
    ulong n_;   // Number of digits
    ulong j_;   // position of last change

private:  // have pointer data
    mixedradix_naf(const mixedradix_naf&);  // forbidden
    mixedradix_naf & operator = (const mixedradix_naf&);  // forbidden

private:
    void set_sentinels()
    {
        a_[n_] = 0;  // ==0 to keep highest track unblocked
        m1_[n_] = 0;  // immaterial

        // here both next() and prev() shall stop scannning
        a_[n_+1] = 1;  // != 0  for prev()
        m1_[n_+1] = 2;  // > a[n+1] for next() (can_incr_q())

        a_[n_+2] = 0;  // == 0  // for look-ahead in can_incr_q()
        m1_[n_+2] = 1;  // (unused)
    }

    bool can_incr_q(ulong j)  const
    // Return whether digit a[j] can be incremented.
    {
        if ( a_[j] == m1_[j] )  return false;  // digit maxed out
        if ( a_[j+1] == 0 )  return true;  // next track free
        if ( a_[j] != 0 )  return true;  // already nonzero (and !=nine)
        return false;
    }

public:
    explicit mixedradix_naf(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;

#ifndef MIXEDRADIX_NAF_MAX_ARRAY_LEN
        a_ = new ulong[n_+3];
        m1_ = new ulong[n_+3];
#endif
        set_sentinels();
        mixedradix_init(n_, mm, m, m1_);
        first();
    }

    ~mixedradix_naf()
    {
#ifndef MIXEDRADIX_NAF_MAX_ARRAY_LEN
        delete [] m1_;
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        j_ = n_;
    }

    void last()
    {
        ulong k = n_ - 1;
        while ( (long)k>=0 )
        {
            a_[k] = m1_[k];
            k -= 2;
        }
        j_ = n_;
    }


    bool next()  // increment
    {
        ulong j = 0;
        while ( ! can_incr_q(j) )  // can read sentinels
        {
            a_[j] = 0;
            ++j;
        }
        j_ = j;

        if ( j>=n_ )
        {
            set_sentinels();  // restore sentinels
            return false;  // current is last
        }

        ++a_[j];
        return true;
    }


    bool prev()  // decrement
    {
        ulong j = 0;
        while ( a_[j]==0 )  { ++j; }  // can read sentinels a[n] and a[n+1]
        j_ = j;

        if ( j>=n_ )  return false;  // current is last

        --a_[j];

        // If a[j]==0, prepend ...090909, otherwise prepend ...909090:
        j -= ( a_[j] != 0 );
        --j;

        while ( (long)j >= 0 )
        {
            a_[j] = m1_[j];
            j -= 2;
        }

        return true;
    }

    ulong pos()  const  { return j_; }  // position of last change

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

//#undef MIXEDRADIX_NAF_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_MIXEDRADIX_NAF_H__
