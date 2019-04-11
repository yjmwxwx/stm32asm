#if !defined  HAVE_MIXEDRADIX_ENDO_H__
#define       HAVE_MIXEDRADIX_ENDO_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/endo-enup.h"
#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_endo
// Mixed radix counting in endo order.
// (endo := "Even Numbers Down, Odd (numbers up)")
{
public:
    ulong *a_;  // digits, sentinel a[n]
    ulong *m1_;  // radix (minus one) for each digit
    ulong *le_;  // last positive digit in endo order, sentinel le[n]
    ulong n_;   // Number of digits
    ulong j_;   // position of last change

private:  // have pointer data
    mixedradix_endo(const mixedradix_endo&);  // forbidden
    mixedradix_endo & operator = (const mixedradix_endo&);  // forbidden

public:
    explicit mixedradix_endo(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        a_[n_] = 1;  // sentinel:  != 0
        m1_ = new ulong[n_];

        mixedradix_init(n_, mm, m, m1_);

        le_ = new ulong[n_+1];
        le_[n_] = 0;  // sentinel:  != a[n]
        for (ulong k=0; k<n_; ++k)  le_[k] = 2 - (m1_[k]==1);

        first();
    }

    ~mixedradix_endo()
    {
        delete [] a_;
        delete [] m1_;
        delete [] le_;
    }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        j_ = n_;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = le_[k];
        j_ = n_;
    }


    bool next()
    {
        bool ret = false;
        ulong j = 0;

        while ( a_[j]==le_[j] )  { a_[j]=0; ++j; }  // can read sentinel
        if ( j<n_ )  // only if no overflow
        {
            a_[j] = next_endo(a_[j], m1_[j]);  // increment
            ret = true;
        }

        j_ = j;
        return ret;
    }

    bool prev()
    {
        bool ret = false;
        ulong j = 0;

        while ( a_[j]==0 )  { a_[j]=le_[j]; ++j; }  // can read sentinel
        if ( j<n_ )  // only if no overflow
        {
            a_[j] = prev_endo(a_[j], m1_[j]);  // decrement
            ret = true;
        }

        j_ = j;
        return ret;
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


#endif  // !defined HAVE_MIXEDRADIX_ENDO_H__
