#if !defined  HAVE_ASCENT_RGS_H__
#define       HAVE_ASCENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-ascent-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
#define ASCENT_RGS_FIXARRAYS  // default on
// gcc 4.5.0: slight slowdown
// gcc 4.8.0: speedup

class ascent_rgs
// Ascent sequences (restricted growth strings, RGS), lexicographic order.
// An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0, d(k)>=0,
//   and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the
//   number of ascents of its argument.
// See OEIS sequence A022493.
{
public:
#ifndef ASCENT_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of ascents in prefix a[0,1,..,k]
#else
    ulong a_[32];  // > 2^98 ascent sequences
    ulong m_[32];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    ascent_rgs(const ascent_rgs&);  // forbidden
    ascent_rgs & operator = (const ascent_rgs&);  // forbidden

public:
    explicit ascent_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
#ifndef ASCENT_RGS_FIXARRAYS
        a_ = new ulong[n_];
        m_ = new ulong[n_];
#endif
        first();
    }

    ~ascent_rgs()
    {
#ifndef ASCENT_RGS_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  m_[k] = 0;
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

        ++a_[j];

        const ulong na = m_[j-1] + ( a_[j] > a_[j-1] );  // ascents: A022493
        for (ulong z=j; z<n_; ++z)  m_[z] = na;

//        ulong na = m_[j-1] + ( a_[j] != a_[j-1] );  // changes: A000522
//        m_[j] = na;
//        for (ulong z=j+1; z<n_; ++z) { na+=(a_[z-1]!=a_[z]);  m_[z] = na; }

//        ulong na = m_[j-1] + ( a_[j] < a_[j-1] );  // descents: A225588
//        m_[j] = na;
//        na += 1;
//        for (ulong z=j+1; z<n_; ++z)  m_[z] = na;

        return j;
    }

    ulong prev()
    // Return position of leftmost change, zero with first.
    {
        ulong j = n_ - 1;
        while ( j != 0 )
        {
            if ( a_[j] != 0 )  break;  // can decrement
            --j;
        }

        if ( j==0 )  return 0;  // current is first

        --a_[j];
        m_[j] = m_[j-1] + ( a_[j] > a_[j-1] );

        ulong i = j;
        while ( ++i < n_ )
        {
            const ulong na = m_[i-1] + 1;
            a_[i] = na;
            m_[i] = na;
        }
        return j;
    }

    ulong num_ascents()  const
    // Return number of ascents.
    { return  m_[n_-1]; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        // ascent stats in m[] OK?
        if ( m_[0] != 0 )  return false;
        ulong na = 0;
        for (ulong j=1; j<n_; ++j)
        {
            na += (a_[j] > a_[j-1]);
            if ( m_[j] != na )  return false;
        }

        return  is_ascent_rgs(a_, n_);
    }
};
// -------------------------


#endif  // !defined HAVE_ASCENT_RGS_H__
