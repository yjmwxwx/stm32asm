#if !defined  HAVE_SCHROEDER_RGS_LEX_H__
#define       HAVE_SCHROEDER_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "restrict.h"

#include "comb/is-schroeder-rgs.h"

#include "comb/comb-print.h"


#define SCHROEDER_RGS_LEX_FIXARRAYS  // default on
// GCC 4.8.0: substantial speedup


class schroeder_rgs_lex
// Schroeder restricted growth strings (RGS):
// a Schroeder RGS is a word a[0,1,2,...,n-1] where
// a[k] <= k + 1 (rising factorial numbers),
// a[0] <= m0 and  a[k] + 1 >= max(j=1..k-1, a[j])
// m0 == 0  ==> little Schroeder numbers, A001003
// m0 == 1  ==> large Schroeder numbers, A006318
// Lexicographic order.
// Cf. OEIS sequences A001003 and A006318.
{
public:
#ifndef SCHROEDER_RGS_LEX_FIXARRAYS
    ulong * restrict a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
    ulong * restrict m_;  // m[k]: maximum value in prefix a[0,...,k-1]
#else
    ulong a_[40];  // 1160541512681304496111863447 RGS
    ulong m_[40];
#endif

    ulong n_;   // number of digits

    ulong m0_;  // max of first digit:
    // m0==0 ==> little Schroeder RGS, A001003
    // m0==1 ==> large Schroeder RGS, A006318



private:  // have pointer data
    schroeder_rgs_lex(const schroeder_rgs_lex&);  // forbidden
    schroeder_rgs_lex & operator = (const schroeder_rgs_lex&);  // forbidden

public:
    explicit schroeder_rgs_lex(ulong n, ulong m0=1)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
        m0_ = (n > 0 ? m0 : 0);
#ifndef SCHROEDER_RGS_LEX_FIXARRAYS
        a_ = new ulong[n_];
        m_ = new ulong[n_+1];
#endif
        m_[0] = 0;

        first();
    }

    ~schroeder_rgs_lex()
    {
#ifndef SCHROEDER_RGS_LEX_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<=n_; ++k)  m_[k] = 0;
    }


    ulong next()
    // Return 1 + position of leftmost change, zero with last.
    {
        ulong j = n_ - 1;
        while ( j != 0 )
        {
            ulong pm = m_[j];
            ulong aj1 = a_[j] + 1;
            if ( (pm <= aj1) & (aj1 <= j+1) )  // can increment
            {
                a_[j] = aj1;
                if ( aj1 > pm )  pm = aj1;
                for (ulong i=j+1; i<n_; ++i)
                {
                    a_[i] = pm - 1;
                    m_[i+1] = pm;
                }

                return j + 1;
            }
            --j;
        }

        if ( a_[0] == m0_ )  return 0;  // current is last

        ulong d0 = a_[0] + 1;
        a_[0] = d0;
        for (ulong i=1; i<n_; ++i)
        {
            a_[i] = d0 - 1;
            m_[i+1] = d0;
        }

        return 1;
    }


    const ulong *data()  const  { return a_; }

    bool OK()  const
    {
        ulong pm = a_[0];
        for (ulong j=1; j<n_; ++j)  // check m[]
        {
            if ( pm != m_[j+1] )  return false;
            if ( a_[j] > pm )  pm = a_[j];
        }

        return is_schroeder_rgs(data(), n_, m0_);
    }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz ); }
};
// -------------------------


#endif  // !defined HAVE_SCHROEDER_RGS_LEX_H__
