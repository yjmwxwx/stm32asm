#if !defined  HAVE_ASCENT_ALT_RGS_H__
#define       HAVE_ASCENT_ALT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
#define ASCENT_ALT_RGS_FIXARRAYS  // default on
// GCC 4.8.0: speedup


class ascent_alt_rgs
// Restricted growth strings (RGS) a[1,..,n], where a[k] < k and
//   no digit a[j] in prefix such that a[j] == a[k] + 1
// Lexicographic order.
// The number of length-n RGS is (OEIS sequence A022493)
//   1, 1, 2, 5, 15, 53, 217, 1014, 5335, 31240, 201608, ...
{
public:
#ifndef ASCENT_ALT_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= k
    ulong *p_;  // (prefix) stats: p[d] = number of digits d
#else
    ulong a_[36];  // > 2^98 ascent sequences
    ulong p_[36];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    ascent_alt_rgs(const ascent_alt_rgs&);  // forbidden
    ascent_alt_rgs & operator = (const ascent_alt_rgs&);  // forbidden

public:
    explicit ascent_alt_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 0);  // shall work for n==0
#ifndef ASCENT_ALT_RGS_FIXARRAYS
        a_ = new ulong[n_ + 4];
        p_ = new ulong[n_ + 4];
#endif
        a_[n_+1] = 0;  // written, but never read
        p_[n_+1] = 0;  // sentinel for next()
        p_[n_+2] = 0;  // sentinel for next()
        first();
    }

    ~ascent_alt_rgs()
    {
#ifndef ASCENT_ALT_RGS_FIXARRAYS
        delete [] a_;
        delete [] p_;
#endif
    }

    const ulong * data()  const  { return a_ + 1; }

    void first()
    {
        for (ulong k=0; k<=n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<=n_; ++k)  p_[k] = 0;
        p_[0] = n_;  // n zeros
    }

//    void last()
//    {
//        for (ulong k=0; k<n_; ++k)  a_[k] = k;
//        for (ulong k=0; k<n_; ++k)  p_[k] = 1;
//    }

    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_;
        while ( j != 0 )
        {
            ulong d = a_[j];
            p_[d] -= 1;  // update stats

            // the following may read sentinels at end of p[]:
            do { ++d; }  while ( p_[d+1] != 0 );

            if ( d < j )  // can increment
            {
                p_[d] += 1;
                a_[j] = d;
                break;
            }
            // defer stats until finished
            --j;
        }

        if ( j==0 )  return 0;  // current is last

        // find smallest digit allowed for suffix:
        ulong d = 0;
        while ( p_[d+1] != 0 )  { ++d; }

        p_[d] += ( n_ - j );  // update stats

        // fill suffix:
        ulong i = j;
        do  { ++i;  a_[i] = d; }  while ( i <= n_ );  // may write a[n+1]

        return j;
    }

//    ulong prev()
//    // Return position of leftmost change, zero with first.
//    {
//        ulong j = n_ - 1;
//        while ( j != 0 )
//        {
//            if ( a_[j] != 0 )  break;  // can decrement
//            --j;
//        }
//
//        if ( j==0 )  return 0;  // current is first
//
//        --a_[j];
//        m_[j] = m_[j-1] + ( a_[j] > a_[j-1] );
//
//        ulong i = j;
//        while ( ++i < n_ )
//        {
//            const ulong na = m_[i-1] + 1;
//            a_[i] = na;
//            m_[i] = na;
//        }
//        return j;
//    }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        // digit a[j] < = j?
        for (ulong j=0; j<=n_; ++j)
            if ( a_[j] > j )  return false;

        // stats in p[] OK?
        ulong t[34];
        for (ulong j=1; j<=n_; ++j)  t[j] = 0;
        for (ulong j=1; j<=n_; ++j)  t[a_[j]] += 1;
        for (ulong j=1; j<n_; ++j)
            if ( t[j] != p_[j] )  return false;

        // todo: test condition

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_ASCENT_ALT_RGS_H__
