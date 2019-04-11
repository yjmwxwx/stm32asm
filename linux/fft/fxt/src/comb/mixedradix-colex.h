#if !defined HAVE_MIXEDRADIX_COLEX_H__
#define      HAVE_MIXEDRADIX_COLEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


// If defined, an array is used instead of a pointer, this gives a small slowdown:
//#define MIXEDRADIX_COLEX_MAX_ARRAY_LEN 64  // default off


class mixedradix_colex
// Mixed radix counting.
{
public:
#ifndef MIXEDRADIX_COLEX_MAX_ARRAY_LEN
    ulong *a_;  // digits
    ulong *m1_;  // nines (radix minus one) for each digit
#else
    ulong a_[MIXEDRADIX_COLEX_MAX_ARRAY_LEN+2];  // keep alignment
    ulong m1_[MIXEDRADIX_COLEX_MAX_ARRAY_LEN+2];
#endif
    ulong n_;   // Number of digits
    ulong j_;   // leftmost position of last change

private:  // have pointer data
    mixedradix_colex(const mixedradix_colex&);  // forbidden
    mixedradix_colex & operator = (const mixedradix_colex&);  // forbidden

public:
    explicit mixedradix_colex(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;

#ifndef MIXEDRADIX_COLEX_MAX_ARRAY_LEN
        a_ = new ulong[n_+1+(n_==0)];
        m1_ = new ulong[n_+1+(n_==0)];
#endif

        a_[0] = 1;   // sentinel: !=0, and !=m1[n]
        m1_[0] = 2;  // sentinel

        mixedradix_init(n_, mm, m, m1_+1);

        first();
    }

    ~mixedradix_colex()
    {
#ifndef MIXEDRADIX_COLEX_MAX_ARRAY_LEN
        delete [] m1_;
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        j_ = 0;
    }

    void last()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = m1_[k];
        j_ = 0;
    }


    bool next()  // increment
    {
        ulong j = n_;
        while ( a_[j]==m1_[j] )  { a_[j]=0;  --j; }  // can read sentinels
        j_ = j;

        if ( j==0 )  return false;  // current is last

        ++a_[j];
        return true;
    }

    bool prev()  // decrement
    {
        ulong j = n_;
        while ( a_[j]==0 )  { a_[j]=m1_[j];  --j; }  // can read sentinels
        j_ = j;

        if ( j==0 )  return false;  // current is first

        --a_[j];
        return true;
    }

    ulong pos()  const  { return j_; }  // position of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, data(), n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_+1, n_, false); }

    ulong to_num()  const
    // Return (integer) value of mixed radix number.
    { return mixedradix2num(data(), m1_, n_); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(data(), n_, m1_) )  return false;
        return true;
    }
};
// -------------------------

//#undef MIXEDRADIX_COLEX_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_MIXEDRADIX_COLEX_H__
