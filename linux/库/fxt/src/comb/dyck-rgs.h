#if !defined  HAVE_DYCK_RGS_H__
#define       HAVE_DYCK_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-dyck-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// Whether to use arrays instead of pointers:
//#define DYCK_RGS_FIXARRAYS  // small speedup


class dyck_rgs
// Restricted growth strings (RGS) corresponding to k-ary Dyck words (i=k-1):
// strings s[0,...,n-1] such that s[j] <= s[j-1] + i
// Lexicographic order.
// Number of RGS is binomial(i*n,n)/((i-1)*n+1), (Catalan numbers for i=1).
{
public:
#ifndef DYCK_RGS_FIXARRAYS
    ulong *s_;  // restricted growth string
#else
    ulong s_[128];  // restricted growth string
#endif
    ulong n_;   // Length of strings
    ulong i_;   // s[k] <= s[k-1]+i
    // OEIS sequences:
    // i=1 ==> A000108 = binomial(2n,n)/(n+1) (Catalan numbers)
    // i=2 ==> A001764 = binomial(3n,n)/(2n+1)
    // i=3 ==> A002293 = binomial(4n,n)/(3n+1)
    // i=4 ==> A002294 = binomial(5n,n)/(4n+1)
    // i=x ==> binomial(x*n,n)/((x-1)*n+1)

private:  // have pointer data
    dyck_rgs(const dyck_rgs&);  // forbidden
    dyck_rgs & operator = (const dyck_rgs&);  // forbidden

public:
    explicit dyck_rgs(ulong n, ulong i=1)
    {
        n_ = (n > 0 ? n : 1 );  // do not fail for n==0
        i_ = i;
#ifndef DYCK_RGS_FIXARRAYS
        s_ = new ulong[n_];
#endif
        first();
    }

    ~dyck_rgs()
    {
#ifndef DYCK_RGS_FIXARRAYS
        delete [] s_;
#endif
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = i_ * k;
    }

    ulong next()
    // Return index of first changed element in s[],
    // return zero if current string is the last.
    {
#if 1
        ulong k = n_;

    start:
        --k;
        if ( k==0 )  return 0;

        ulong sk = s_[k] + 1;
        ulong mp = s_[k-1] + i_;
        if ( sk > mp )  // "carry"
        {
            s_[k] = 0;
            goto start;
        }

        s_[k] = sk;
        return k;

#else  // same speed:
        ulong k = n_;
        while ( --k )
        {
            ulong sk = s_[k] + 1;
            ulong mp = s_[k-1] + i_;
            if ( sk <= mp )  // can we increment?
            {
                s_[k] = sk;
                return k;
            }
            s_[k] = 0;
        }
        return 0;
#endif
    }

    ulong prev()
    // Return index of first changed element in s[],
    // return zero if current string is the first.
    {
        ulong k = n_;
        while ( --k )
        {
            if ( s_[k] != 0 )  // can we decrement?
            {
                --s_[k];
                for (ulong j=k+1; j<n_; ++j)  s_[j] = s_[j-1] + i_;
                return k;
            }
            s_[k] = 0;
        }
        return 0;
    }


    const ulong* data()  const  { return s_; }

    void print(const char *bla=0, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    { return is_dyck_rgs( data(), n_, i_ ); }
};
// -------------------------


#endif  // !defined HAVE_DYCK_RGS_H__
