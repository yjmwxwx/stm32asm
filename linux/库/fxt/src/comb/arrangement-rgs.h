#if !defined  HAVE_ARRANGEMENT_RGS_H__
#define       HAVE_ARRANGEMENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-arrangement-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

// whether to use arrays instead of pointers:
#define ARRANGEMENT_RGS_FIXARRAYS  // default is on

class arrangement_rgs
// RGS for arrangements (all permutations of all subsets):
//   a digit is at most 1 + the number of nonzero digits in the prefix.
// The positions of nonzero digits determine the subset, and
//   their values (decreased by 1) are the (left) inversion table
//   (a rising factorial number) for the permutation.
// Lexicographic order.
// Cf. OEIS sequence A000522.
{
public:
#ifndef ARRANGEMENT_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS
    ulong *z_;  // 1 + number of nonzero digits in prefix
#else
    ulong a_[30];
    ulong z_[30];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    arrangement_rgs(const arrangement_rgs&);  // forbidden
    arrangement_rgs & operator = (const arrangement_rgs&);  // forbidden

public:
    explicit arrangement_rgs(ulong n)
    {
        n_ = n;
#ifndef ARRANGEMENT_RGS_FIXARRAYS
        a_ = new ulong[n_+2];
        z_ = new ulong[n_+2];
#endif
        a_[0] = 1;  // sentinel to stop scan with prev()
        z_[0] = 1;
        // a[n+1] is write-only
        // z[n+1] is write-only

        first();
    }

    ~arrangement_rgs()
    {
#ifndef ARRANGEMENT_RGS_FIXARRAYS
        delete [] a_;
        delete [] z_;
#endif
    }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        for (ulong k=1; k<=n_; ++k)  z_[k] = 1;
    }

    void last()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = k;
        for (ulong k=1; k<=n_; ++k)  z_[k] = k;
    }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_;
        while ( j != 0 )
        {
            if ( a_[j] < z_[j] )
            {
                ++a_[j];
                ulong w = z_[j] + 1;
                ulong i = j;
                do
                {
                    z_[++i] = w;   // can write z[n+1]
                }
                while ( i < n_ );
                return j;
            }
            a_[j] = 0;
            --j;
        }

        return 0;  // current is last
    }


    ulong prev()
    // Return position of leftmost change, zero with first.
    {
        ulong j = n_;
        while ( a_[j] == 0 )  { --j; }

        if ( j==0 )  return 0;  // current is first

        ulong a1 = a_[j] - 1;
        a_[j] = a1;
        ulong w = z_[j] + (a1 != 0);
//        ulong w = z_[j]; // this gives set partition RGS (cf. A000110)
        ulong i = j;
        do
        {
            ++i;
            a_[i] = z_[i] = w;  // can write z[n+1] and a[n+1]
            ++w;
        }
        while ( i < n_ );

        return j;
    }

    const ulong *data()  const  { return a_ + 1; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        ulong w = 1;
        for (ulong j=1; j<=n_; ++j)
        {
            if ( a_[j] > w )  return false;
            if ( z_[j] != w )  return false;
            w += ( a_[j] != 0 );
        }
        if ( ! is_arrangement_rgs( data(), n_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_ARRANGEMENT_RGS_H__
