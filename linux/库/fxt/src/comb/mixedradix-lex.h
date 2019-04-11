#if !defined HAVE_MIXEDRADIX_LEX_H__
#define      HAVE_MIXEDRADIX_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


// If defined, an array is used instead of a pointer, this gives a small speedup:
//#define MIXEDRADIX_LEX_MAX_ARRAY_LEN 64  // default off


class mixedradix_lex
// Mixed radix counting.
{
public:
#ifndef MIXEDRADIX_LEX_MAX_ARRAY_LEN
    ulong *a_;  // digits
    ulong *m1_;  // nines (radix minus one) for each digit
#else
    ulong a_[MIXEDRADIX_LEX_MAX_ARRAY_LEN+2];  // keep alignment
    ulong m1_[MIXEDRADIX_LEX_MAX_ARRAY_LEN+2];
#endif
    ulong n_;   // Number of digits
    ulong j_;   // position of last change

private:  // have pointer data
    mixedradix_lex(const mixedradix_lex&);  // forbidden
    mixedradix_lex & operator = (const mixedradix_lex&);  // forbidden

public:
    explicit mixedradix_lex(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;

#ifndef MIXEDRADIX_LEX_MAX_ARRAY_LEN
        a_ = new ulong[n_+1];
        m1_ = new ulong[n_+1];
#endif
        a_[n_] = 1;   // sentinel: !=0, and !=m1[n]
        m1_[n_] = 0;  // sentinel

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_lex()
    {
#ifndef MIXEDRADIX_LEX_MAX_ARRAY_LEN
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
        for (ulong k=0; k<n_; ++k)  a_[k] = m1_[k];
        j_ = n_;
    }


    bool next()  // increment
    {
        ulong j = 0;
        while ( a_[j]==m1_[j] )  { a_[j]=0;  ++j; }  // can read sentinels
        j_ = j;

        if ( j==n_ )  return false;  // current is last

        ++a_[j];
        return true;
    }

    bool prev()  // decrement
    {
        ulong j = 0;
        while ( a_[j]==0 )  { a_[j]=m1_[j];  ++j; }  // can read sentinels
        j_ = j;

        if ( j==n_ )  return false;  // current is first

        --a_[j];
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
        return true;
    }
};
// -------------------------

//#undef MIXEDRADIX_LEX_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_MIXEDRADIX_LEX_H__
