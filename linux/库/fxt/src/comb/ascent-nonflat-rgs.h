#if !defined  HAVE_ASCENT_NONFLAT_RGS_H__
#define       HAVE_ASCENT_NONFLAT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-ascent-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"



class ascent_nonflat_rgs
// Ascent sequences (restricted growth strings, RGS) without flat steps
// (i.e., no two adjacent digits are equal), lexicographic order.
// An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(k)>=0
//   and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the
//   number of ascents of its argument.
// The number of length-n RGS is (OEIS sequence A138265)
//   1, 1, 1, 2, 5, 16, 61, 271, 1372, 7795, 49093, 339386, 2554596, ...
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of ascents in prefix a[0,1,..,k]
    ulong n_;   // Number of digits

private:  // have pointer data
    ascent_nonflat_rgs(const ascent_nonflat_rgs&);  // forbidden
    ascent_nonflat_rgs & operator = (const ascent_nonflat_rgs&);  // forbidden

public:
    explicit ascent_nonflat_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
        a_ = new ulong[n_];
        m_ = new ulong[n_];

        first();
    }

    ~ascent_nonflat_rgs()
    {
        delete [] a_;
        delete [] m_;
    }

private:
    void refresh_m(ulong j)
    // Refresh m[] beyond position j.
    {
        ulong na = m_[j];
        for ( ++j; j<n_; ++j)
        {
            na += (a_[j] > a_[j-1]);
            m_[j] = na;
        }
    }

public:
    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = k & 1UL;

        m_[0] = 0;
        refresh_m(0);
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = k;
        for (ulong k=0; k<n_; ++k)  m_[k] = k;
    }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_ - 1;
        while ( j != 0 )
        {
            if ( a_[j] <= m_[j-1] )  break;  // can increment
            a_[j] = 0;
            --j;
        }

        if ( j==0 )  return 0;  // current is last

        const ulong aj1 = a_[j] + 1;
        a_[j] = aj1 + ( aj1 == a_[j-1] );


        // append 0, 1, 0, 1, 0, 1, ... :
        for (ulong z=j+2; z<n_; z+=2)  a_[z] = 1;

        refresh_m(j-1);

        return j;
    }


    ulong num_ascents()  const
    // Return number of ascents.
    {
        return  m_[n_-1];  // gives 0 for n==0
    }


    const ulong *data()  const  { return a_; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }


    bool OK()  const
    {
        ulong na = 0;
        for (ulong j=1; j<n_; ++j)  // ascent stats in m[] OK?
        {
            na += (a_[j] > a_[j-1]);
            if ( m_[j] != na )  return false;
        }

        if ( ! is_ascent_rgs(a_, n_) )  return false;

        for (ulong j=1; j<n_; ++j)  // non-flat?
            if (a_[j] == a_[j-1])  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_ASCENT_NONFLAT_RGS_H__
