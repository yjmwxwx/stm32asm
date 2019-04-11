#if !defined  HAVE_MOTZKIN_NONFLAT_RGS_LEX_H__
#define       HAVE_MOTZKIN_NONFLAT_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-catalan-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

//#include <cmath>


// whether to use arrays instead of pointers:
//#define MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS  // default is off


class motzkin_nonflat_rgs_lex
// Motzkin (nonflat) restricted growth strings (RGS), lexicographic order.
// Same as: Catalan RGS without flat steps.
// Cf. OEIS sequences A086246 and A001006.
// The number of length-n RGS is
//  1, 1, 1, 2, 4, 9, 21, 51, 127, 323, 835, 2188, 5798, 15511, 41835, ...
// G.f. is (1+x-sqrt(1-2*x-3*x^2))/(2*x)
{
public:
#ifndef MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1, a[k] != a_[k-1]
#else
    ulong a_[64];
#endif
    ulong n_;   // Number of digits
    ulong n1_;  // n-1 if n!=0, otherwise 0

private:  // have pointer data
    motzkin_nonflat_rgs_lex(const motzkin_nonflat_rgs_lex&);  // forbidden
    motzkin_nonflat_rgs_lex & operator = (const motzkin_nonflat_rgs_lex&);  // forbidden

public:
    explicit motzkin_nonflat_rgs_lex(ulong n)
    {
        n_ = n;
        n1_ = (n_ ? n_-1 : 0);
#ifndef MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS
        a_ = new ulong[n_+(n_==0)+1];
#endif
        a_[0] = 0;  // for n==0
        a_[n_] = 0;  // for prev()
        first();
    }

    ~motzkin_nonflat_rgs_lex()
    {
#ifndef MOTZKIN_NONFLAT_RGS_LEX_FIXARRAYS
        delete [] a_;
#endif
    }

    void first()
    { for (ulong k=0; k<n_; ++k)  a_[k] = k & 1UL; }

    void last()
    { for (ulong k=0; k<n_; ++k)  a_[k] = k; }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        if ( a_[n1_] >= n1_ )  return 0;  // current is last

        ulong j = n1_;
        while ( a_[j] > a_[j-1] )
        {
            a_[j] = 0;
            --j;
        }

        ulong a0 = a_[j] + 1;
        ulong a1 = a_[j-1];
        a0 += (a0==a1);
        a_[j] = a0;

        // append 0, 1, 0, 1, 0, 1, ... :
        for (ulong i=j+2; i<n_; i+=2)  a_[i] = 1;

        return j;
    }


    ulong prev()
    // Return position of leftmost change, zero with first.
    {
        ulong j = n1_;
        while ( a_[j] <= 1 )
        {
            if ( j==0 )  return 0;  // current is first
            --j;
        }

        j += a_[j+1];  // can read a[n]==0
        ulong a0 = a_[j] - 1;
        a0 -= (a_[j-1]==a0);
        a_[j] = a0;
        // append a0+1, a0+2, a0+3, ... :
        for (ulong i=j+1; i<n_; ++i)  a_[i] = ++a0;

        return j;
    }


    const ulong *data()  const  { return a_; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        if ( n_==0 )  return true;

        const ulong *a = data();

        if ( ! is_catalan_rgs(a, n_) )  return false;

        for (ulong k=2; k<n_; ++k)  // no flat steps ?
            if ( a[k] == a[k-1])  return false;

        return true;
    }

};
// -------------------------


#endif  // !defined HAVE_MOTZKIN_NONFLAT_RGS_LEX_H__
