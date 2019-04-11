#if !defined HAVE_MIXEDRADIX_RFACT_H__
#define      HAVE_MIXEDRADIX_RFACT_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


// If defined, an array is used instead of a pointer, this gives a speedup:
#define MIXEDRADIX_RFACT_MAX_ARRAY_LEN 31  // default on


class mixedradix_rfact
// Counting in rising factorial base,
// special case of mixed radix counting.
{
public:
#ifndef MIXEDRADIX_RFACT_MAX_ARRAY_LEN
    ulong *a_;  // digits
#else
    ulong a_[MIXEDRADIX_RFACT_MAX_ARRAY_LEN+1];
#endif
    ulong n_;   // Number of digits
    ulong j_;   // position of last change

private:  // have pointer data
    mixedradix_rfact(const mixedradix_rfact&);  // forbidden
    mixedradix_rfact & operator = (const mixedradix_rfact&);  // forbidden

public:
    explicit mixedradix_rfact(ulong n)
    {
        n_ = n;

#ifndef MIXEDRADIX_RFACT_MAX_ARRAY_LEN
        a_ = new ulong[n_+1];
#endif
        a_[0] = 0;  // init a[0] (for n==0)
        a_[n_] = n_ + 2;  // sentinel: !=0 and !=n+1
        first();
    }

    ~mixedradix_rfact()
    {
#ifndef MIXEDRADIX_RFACT_MAX_ARRAY_LEN
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        j_ = (n_ ? n_-1 : 0);
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = k+1;
        j_ = (n_ ? n_-1 : 0);
    }


    ulong next()
    // Return position of rightmost change,
    // return n with last word.
    {
        ulong j = 0;
        while ( a_[j]==j+1 )  { a_[j]=0;  ++j; }  // can read sentinel a[n]
        j_ = j;
        ++a_[j];  // will write to sentinel a[n] with last word
        return j_;
    }

    ulong prev()
    // Return position of rightmost change,
    // return n with last word.
    {
        ulong j = 0;
        while ( a_[j]==0 )  { a_[j] = j+1;  ++j; }  // can read sentinel a[n]
        j_ = j;
        --a_[j];  // will write to sentinel a[n] with last word
        return j_;
    }

    ulong pos()  const  { return j_; }  // position of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_vec(bla, a_, n_, dfz); }
};
// -------------------------

//#undef MIXEDRADIX_RFACT_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_MIXEDRADIX_RFACT_H__
