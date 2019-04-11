#if !defined  HAVE_ASCENT_RGS_H__
#define       HAVE_ASCENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-ascent-rgs.h"
#include "fxttypes.h"

// Variant with sentinel

// whether to use arrays instead of pointers:
//#define ASCENT_RGS_FIXARRAYS  // default off

class ascent_rgs
// Ascent sequences (restricted growth strings, RGS), lexicographic order.
// An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0, d(k)>=0,
//   and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the
//   number of ascents of its argument.
// The number of length-n RGS is (OEIS sequence A022493)
//   1, 1, 2, 5, 15, 53, 217, 1014, 5335, 31240, 201608, ...
{
public:
#ifndef ASCENT_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of ascents in prefix a[0,1,..,k]
#else
    ulong a_[64];
    ulong m_[64];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    ascent_rgs(const ascent_rgs&);  // forbidden
    ascent_rgs & operator = (const ascent_rgs&);  // forbidden

public:
    explicit ascent_rgs(ulong n)
    {
        n_ = n + (n==0);  // shall work for n==0
#ifndef ASCENT_RGS_FIXARRAYS
        a_ = new ulong[n_ + 1];
        m_ = new ulong[n_ + 1];
#endif
        a_[0] = 0;  // sentinel
        m_[0] = 0;  // sentinel

        first();
    }

    virtual ~ascent_rgs()
    {
#ifndef ASCENT_RGS_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        for (ulong k=1; k<=n_; ++k)  m_[k] = 0;
    }

    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_;
        while ( a_[j] > m_[j-1] )
        {
            a_[j] = 0;
            --j;
        }

        if ( j==1 )  return 0;  // current is last

        ++a_[j];

        const ulong na = m_[j-1] + ( a_[j] > a_[j-1] );  // ascents: A022493
        for (ulong z=j; z<=n_; ++z)  m_[z] = na;

//        const ulong na = m_[j-1] + ( a_[j] > a_[j-1] );  // ascents: A022493
//        for (ulong z=j; z<n_; ++z)  m_[z] = na;

//        ulong na = m_[j-1] + ( a_[j] != a_[j-1] );  // changes: A000522
//        m_[j] = na;
//        for (ulong z=j+1; z<n_; ++z) { na+=(a_[z-1]!=a_[z]);  m_[z] = na; }

//        ulong na = m_[j-1] + ( a_[j] < a_[j-1] );  // descents: A225588
//        m_[j] = na;
//        na += 1;
//        for (ulong z=j+1; z<n_; ++z)  m_[z] = na;

        return j;
    }

    ulong num_ascents()  const
    // Return number of ascents.
    {
        return  m_[n_];  // gives 0 for n==0
    }

    const ulong *data()  const  { return a_ + 1; }

    bool OK()  const
    {
        ulong na = 0;
        const ulong *a = data();
        const ulong *m = m_ + 1;
        for (ulong j=1; j<n_; ++j)  // ascent stats in m[] OK?
        {
            na += (a[j] > a[j-1]);
            if ( m[j] != na )  return false;
        }

        return  is_ascent_rgs(data(), n_);
    }
};
// -------------------------


#endif  // !defined HAVE_ASCENT_RGS_H__
