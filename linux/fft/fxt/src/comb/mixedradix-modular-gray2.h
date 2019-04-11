#if !defined HAVE_MIXEDRADIX_MODULAR_GRAY2_H__
#define      HAVE_MIXEDRADIX_MODULAR_GRAY2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/mixedradix.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_modular_gray2
// Modular Gray code for mixed radix numbers.
// Constant amortized time (CAT) algorithm.
{
public:
    ulong *a_;  // digits
    ulong *m1_;  // radix minus one ('nines')
    ulong *x_;  // count changes of digit
    ulong n_;   // number of digits
    ulong j_;   // position of last change

private:  // have pointer data
    mixedradix_modular_gray2(const mixedradix_modular_gray2&);  // forbidden
    mixedradix_modular_gray2 & operator = (const mixedradix_modular_gray2&);  // forbidden

public:
    explicit mixedradix_modular_gray2(ulong n, ulong mm, const ulong *m=0)
    {
        n_ = n;
        a_ = new ulong[n_];
        m1_ = new ulong[n_+1];  // incl. sentinel at m1[n]
        m1_[n_] = 0;  // sentinel
        x_ = new ulong[n_+1];   // incl. sentinel at x[n] (!= m1[n])
        // sentinel x[n] written in first() and last().

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_modular_gray2()
    {
        delete [] a_;
        delete [] m1_;
        delete [] x_;
    }

    const ulong * data()  const  { return a_; }


    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  x_[k] = 0;
        x_[n_] = 1UL;  // sentinel
        j_ = n_;
    }

    bool next()
    {
        ulong j = 0;
        while ( x_[j] == m1_[j] )  // can read sentinels
        {
            x_[j] = 0;
            ++j;
        }
        ++x_[j];

        if ( j==n_ )  return false;  // current is last

        j_ = j;  // save position of change

        // increment:
#if 1  // default, faster
        ulong aj = a_[j] + 1;
        if ( aj>m1_[j] )  aj = 0;
        a_[j] = aj;
#else
        ulong aj = a_[j];
        if ( aj==m1_[j] )  a_[j] = 0;
        else               a_[j] = aj + 1;
#endif

        return true;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  x_[k] = 0;
        x_[n_] = 1UL;  // sentinel

        ulong j = n_;  // track j
        ulong tt = 1;  // total of transitions to right of track j
        ulong p = 1;   // product of all radices at and to the right of track j
        while ( j-- )
        {
            ulong r = m1_[j] + 1;  // radix at track
            p *= r;  // update product
            ulong t = p - tt;  // this many transitions
            tt += t;  // update total of transitions
            ulong a = t % r;  // digit here (value after t transitions)
            a_[j] = a;
        }
    }

    bool prev()
    {
        ulong j = 0;
        while ( x_[j] == m1_[j] )  // can read sentinels
        {
            x_[j] = 0;
            ++j;
        }
        ++x_[j];

        if ( j==n_ )  return false;  // current is last

        j_ = j;  // save position of change

        // decrement:
        ulong aj = a_[j];
        if ( aj==0 )  a_[j] = m1_[j];
        else          a_[j] = aj - 1;

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


#endif  // !defined HAVE_MIXEDRADIX_MODULAR_GRAY2_H__
