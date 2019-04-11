#if !defined  HAVE_RGS_MAXINCR_H__
#define       HAVE_RGS_MAXINCR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"


class rgs_maxincr
// Restricted growth strings (RGS) s[0,...,n-1] so that
//  s[k] <= max( j < k, s[j] + i ).
// Lexicographic order
// OEIS sequences:
// i=1 ==> Bell numbers, A000110
// i=2 ==> A080337, see also A080107
// i=3 ==> A189845
{
public:
    ulong *s_;  // restricted growth string
    ulong *m_;  // m_[k-1] == max value for s_[j], j<k
    ulong n_;   // Length of strings
    ulong i_;   // s[k] <= max_{j<k}(s[j]+i)
    // i==1 ==> RGS for set partitions

private:  // have pointer data
    rgs_maxincr(const rgs_maxincr&);  // forbidden
    rgs_maxincr & operator = (const rgs_maxincr&);  // forbidden

public:
    explicit rgs_maxincr(ulong n, ulong i=1)
    {
        n_ = n;
        m_ = new ulong[n_];
        s_ = new ulong[n_];
        i_ = i;
        first();
    }

    ~rgs_maxincr()
    {
        delete [] m_;
        delete [] s_;
    }

    void first()
    {
        ulong n = n_;
        for (ulong k=0; k<n; ++k)  s_[k] = 0;
        for (ulong k=0; k<n; ++k)  m_[k] = 0;
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
        ulong m1 = m_[k-1];
        if ( sk > m1+i_ )  // "carry"
        {
            s_[k] = 0;
            goto start;
        }

        s_[k] = sk;

//        if ( sk==m1 )  m1 += i_;  // gives different strings
        if ( sk>m1 )  m1 = sk;

        for (ulong j=k; j<n_; ++j )  m_[j] = m1;

        return k;
    }

    const ulong* data()  const  { return s_; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_RGS_MAXINCR_H__
