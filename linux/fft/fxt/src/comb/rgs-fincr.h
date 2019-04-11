#if !defined  HAVE_RGS_FINCR_H__
#define       HAVE_RGS_FINCR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"


class rgs_fincr
// Restricted growth strings (RGS) s[0,...,n-1] so that
//  s[k] <= F[k]+i  where
//  F[0]=0, F[k+1]=( s[k+1]-s[k]==i ?  F[k]+i : F[k] )
// Lexicographic order.
// Cf. OEIS sequences
//  A000110 (i=1),  A004211 (i=2),  A004212 (i=3),
//  A004213 (i=4),  A005011 (i=5),  A005012 (i=6).
{
public:
    ulong *s_;  // restricted growth string
    ulong *f_;  // values F(k)
    ulong n_;   // Length of strings
    ulong i_;   // s[k] <= f[k] + i
    // i=1 ==> RGS for set partitions (Bell numbers), OEIS sequence A000110
    // i=2 ==> A004211,  i=3 ==> A004212,  i=4 ==> A004213
    // i=5 ==> A005011,  i=6 ==> A005012
    // i=x ==> "shifts one place left under x-th order binomial transform"
    //          a(n) = sum((x^(n-k))*stirling2(n, k)

private:  // have pointer data
    rgs_fincr(const rgs_fincr&);  // forbidden
    rgs_fincr & operator = (const rgs_fincr&);  // forbidden

public:
    explicit rgs_fincr(ulong n, ulong i=1)
    {
        n_ = n;
        f_ = new ulong[n_];
        s_ = new ulong[n_];
        i_ = i;
        first();
    }

    ~rgs_fincr()
    {
        delete [] f_;
        delete [] s_;
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  s_[k] = 0;
        for (ulong k=0; k<n_; ++k)  f_[k] = 0;
    }

    ulong next()
    // Return index of first changed element in s[],
    // Return zero if current string is the last
    {
        ulong k = n_;

    start:
        --k;
        if ( k==0 )  return 0;

        ulong sk = s_[k] + 1;
        ulong m1 = f_[k-1];
        ulong mp = m1 + i_;
        if ( sk > mp )  // "carry"
        {
            s_[k] = 0;
            goto start;
        }

        s_[k] = sk;
        if ( sk==mp )  m1 += i_;
        for (ulong j=k; j<n_; ++j )  f_[j] = m1;

        return k;
    }

    const ulong* data()  const  { return s_; }

    void print(const char *bla, bool dfz=false)  const
    {  print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_RGS_FINCR_H__
