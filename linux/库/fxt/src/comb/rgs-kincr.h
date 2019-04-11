#if !defined  HAVE_RGS_KINCR_H__
#define       HAVE_RGS_KINCR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"


class rgs_kincr
// Restricted growth strings (RGS) s[0,...,n-1] so that s[k] <= s[k-1]+k
// Lexicographic order.
// Cf. OEIS sequence A107877.
{
public:
    ulong *s_;  // restricted growth string
    ulong n_;   // Length of strings

private:  // have pointer data
    rgs_kincr(const rgs_kincr&);  // forbidden
    rgs_kincr & operator = (const rgs_kincr&);  // forbidden

public:
    explicit rgs_kincr(ulong n)
    {
        n_ = n;
        s_ = new ulong[n_];
        first();
    }

    ~rgs_kincr()
    { delete [] s_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
    }

    ulong next()
    // Return index of first changed element in s[],
    // Return zero if current string is the last.
    {
        ulong k = n_;

    start:
        --k;
        if ( k==0 )  return 0;

        ulong sk = s_[k] + 1;
        ulong mp = s_[k-1] + k;  // A107877
        if ( sk > mp )  // "carry"
        {
            s_[k] = 0;
            goto start;
        }

        s_[k] = sk;
        return k;
    }

    const ulong* data()  const  { return s_; }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_RGS_KINCR_H__
