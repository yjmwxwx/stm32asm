#if !defined HAVE_SKEW_BINARY_H__
#define      HAVE_SKEW_BINARY_H__
// This file is part of the FXT library.
// Copyright (C) 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"

#include "fxtio.h" // xxx

class skew_binary
// Skew binary numbers.
// See http://en.wikipedia.org/wiki/Skew_binary_number_system
// Cf. OEIS sequence A169683.
{
public:
    ulong n_;    // Number of digits
    ulong tr_;   // aux: current track
    ulong *a_;   // digits

private:  // have pointer data
    skew_binary(const skew_binary&);  // forbidden
    skew_binary & operator = (const skew_binary&);  // forbidden

public:
    explicit skew_binary(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1];  // a[0] is a sentinel
        a_[0] = 0;
        first();
    }

    ~skew_binary()
    {
        delete [] a_;
    }

    const ulong * data()  const  { return a_ + 1; }


    void first()
    {
        for (ulong k=0; k<=n_; ++k)  a_[k] = 0;
        tr_ = n_;
    }

//    void last()
//    {
//        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
//        a_[1_] = 2;
//        tr_ = 1;
//    }

    ulong next()
    // Generate next.
    // Loopless algorithm.
    // Return leftmost position of change + 1,
    // return zero with last number.
    {
        ulong z = a_[tr_];
        if ( z <= 1 )  // easy case: just increment
        {
            a_[tr_] = z + 1;
            return  tr_;
        }
        else  // z == 2
        {
            a_[tr_] = 0;
            tr_ -= 1;
            ulong j = tr_;
//            cout << " :: j = " << j << " ";
            ulong y = a_[tr_] + 1;
            a_[tr_] = y;
            if ( y == 1 )  tr_ = n_;  // change track
            return  j;  // return zero with last number
        }
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, data(), n_, dfz); }

    bool OK()  const
    {
        bool s2 = false;  // whether digit 2 has been seen
        bool s1 = false;  // whether any nonzero digit has been seen
        for (ulong j=n_; j!=0; --j)
        {
            ulong z = a_[j];
            if ( z == 0 )  continue;
            if ( z > 2 )  return false;
            if ( z==2 )
            {
                if ( s2 )  return false;  // max one digit 2
                if ( s1 )  return false;  // no digit 1 right of digit 2
                s2 = true;
            }
            s1 = true;
        }
        return true;
    }
};
// -------------------------

#endif  // !defined HAVE_SKEW_BINARY_H__
