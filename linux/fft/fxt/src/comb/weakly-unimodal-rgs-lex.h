#if !defined HAVE_WEAKLY_UNIMODAL_RGS_LEX_H__
#define      HAVE_WEAKLY_UNIMODAL_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "comb/is-unimodal.h"
#include "fxttypes.h"


// define to allow m==1:
//#define WEAKLY_UNIMODAL_RGS_LEX_M1  // default off (slowdown)

class weakly_unimodal_rgs_lex
// Weakly unimodal RGS (restricted growth strings), lexicographic order.
// Cf. OEIS sequences:
//  A088536: unimodal maps [1..n] -> [1..n].
//  A225006: unimodal maps [1..n] -> [1..n+1].
//  A000000: unimodal maps [1..n] -> [1..n+2] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1..2*n] (not in the OEIS).
//  A000000: unimodal maps [1..2*n] -> [1..n] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1..n-1] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1..floor(n/2)] (not in the OEIS).
//  A000124: unimodal maps [1..n] -> [1,2].
//  A000000: unimodal maps [1..n] -> [1,2,3] (not in the OEIS).
//  A002412: unimodal maps [1,2,3] -> [1..n].
//  A006324: unimodal maps [1,2,3,4] -> [1..n].
{
public:
    ulong *a_;  // RGS
    ulong n_;   // length of the RGS.
    ulong tr_;  // track
    ulong mp_;  // rightmost position of a maximal digit
    ulong mv_;  // value of maximal digit(s)
    ulong m1_;  // maximal digit value allowed

private:  // have pointer data
    weakly_unimodal_rgs_lex(const weakly_unimodal_rgs_lex&);  // forbidden
    weakly_unimodal_rgs_lex & operator = (const weakly_unimodal_rgs_lex&);  // forbidden

public:
    explicit weakly_unimodal_rgs_lex(ulong n, ulong m)
    {
        n_ = n;

#ifdef WEAKLY_UNIMODAL_RGS_LEX_M1
        n_ += (n==0);
        if ( m < 1 )  m = 1;
#else
        if ( m < 2 )  m = 2;
#endif
        m1_ = m - 1;

        a_ = new ulong[n_+2];
        a_[0] = 0;  // sentinel for scan (with n==0)
        a_[1] = 0;  // sentinel for scan
        ++a_;  // nota bene

        first();
    }

    ~weakly_unimodal_rgs_lex()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        mp_ = n_;
        mv_ = 0;
        tr_ = n_;
    }

    ulong next()
    // Return position of leftmost change (1,...,n).
    // Return zero if current RGS is last.
    {
        if ( tr_ < n_ )  // easy case: append 1
        {
#ifdef WEAKLY_UNIMODAL_RGS_LEX_M1
            if ( m1_ == 0 )  return 0;  // to allow m==1
#endif
            ++tr_;
            a_[tr_] = 1;
            mp_ += ( mv_==1 );
            return tr_;
        }

        ulong z = a_[tr_];

        if ( tr_==mp_ )  // on (right edge of) peak
        {
            if ( z < m1_ )  // can increment
            {
                ++z;
                ++mv_;
                a_[tr_] = z;
                return tr_;
            }
        }

        if ( a_[tr_] < a_[tr_-1] )
        {
            ulong a1 = a_[tr_] + 1;
            a_[tr_] = a1;

            if ( mv_ <= a1 )
            {
                mv_ = a1;
                mp_ = tr_;
            }

            return  tr_;
        }

        a_[tr_] = 0;
        ulong j = tr_ - 1;

        do
        {
            ulong a0 = a_[j];
            ulong a1 = a_[j-1];  // can read sentinel

            if ( a0 == 0 )  // reached digit 0: set digit to 1, the new peak
            {
                a_[j] = 1;
                mv_ = 1;
                mp_ = j;
                tr_ = j;
                return  tr_;
            }

            if ( j < mp_ )  // left of old max: increment to make new right edge of peak
            {
                if ( a0 < m1_ )
                {
                    ++a0;
                    a_[j] = a0;
                    mv_ = a0;
                    mp_ = j;
                    tr_ = j;
                    return  tr_;
                }
            }

            if ( a0 < a1 )  // downstep: we can increment
            {
                ++a0;
                a_[j] = a0;
                if ( mv_ == a0 )  mp_ = j;  // cannot have a0 > mv
                tr_ = j;
                return  tr_;
            }

            a_[j] = 0;
            --j;
        }
        while ( j );

        return 0;  // current is last
    }


    bool OK()  const
    {
        for (ulong j=1; j<=n_; ++j)
            if ( a_[j] > m1_ )  return false;

        if ( a_[mp_] != mv_ )  return false;

        if ( ! is_weakly_unimodal(a_+1, n_) )  return false;

        return  true;
    }

    void print(const char *bla, bool dfz)  const
    { print_vec(bla, a_+1, n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_WEAKLY_UNIMODAL_RGS_LEX_H__
