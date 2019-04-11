#if !defined HAVE_SMOOTH_RFACT_RGS_H__
#define      HAVE_SMOOTH_RFACT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "comb/is-smooth.h"

#include "fxttypes.h"

class smooth_rfact_rgs
// Restricted growth strings (RGS) [d(0), d(1), d(2), ..., d(n-1)] where
//  0 <= d(k) <= k and abs(d(k)-d(k-1)) <= 1 (smooth factorial numbers).
// Lexicographic order.
// Cf. OEIS sequence A005773.
{
public:
    ulong *a_;   // digits
    ulong n_;    // number of digits
    ulong j_;    // position of last change


private:  // have pointer data
    smooth_rfact_rgs(const smooth_rfact_rgs&);  // forbidden
    smooth_rfact_rgs & operator = (const smooth_rfact_rgs&);  // forbidden

public:
    explicit smooth_rfact_rgs(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_ + 1];
        a_[0] = -1UL;  // sentinel
        ++a_;  // nota bene

        first();
    }

    ~smooth_rfact_rgs()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_; }

    void first( )
    { for (ulong j=0; j<n_; ++j)  a_[j] = 0; }


    bool next()
    {
        ulong j = n_ - 1;
        // can read sentinel for n==0:
        if ( a_[j] == j )  return false;  // current is last

        while ( a_[j] - a_[j-1] == 1 )
        {
            a_[j] = 0;
            --j;
        }

        j_ = j;
        ulong v = a_[j] + 1;
        do
        {
            a_[j] = v;
            ++j;
            --v;
        }
        while ( v && (j<n_) );

        return true;
    }


    ulong pos()  const  { return j_; }  // position of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }


    bool OK()  const
    { return  is_smooth(data(), n_) ; }
};
// -------------------------



#endif  // !defined HAVE_SMOOTH_RFACT_RGS_H__
