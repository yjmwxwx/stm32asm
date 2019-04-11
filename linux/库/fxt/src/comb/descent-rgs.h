#if !defined  HAVE_DESCENT_RGS_H__
#define       HAVE_DESCENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-descent-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
#define DESCENT_RGS_FIXARRAYS  // default is on

class descent_rgs
// Descent sequences (restricted growth strings, RGS), lexicographic order.
// A descent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//   d(k)>=0, and d(k) <= 1 + desc([d(1), d(2), ..., d(k-1)]) and desc(.)
//   counts the number of descents of its argument.
// See OEIS sequence A225588.
{
public:
#ifndef DESCENT_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of descents in prefix a[0,1,..,k]
#else
    ulong a_[32];  // > 2^87 descent sequences
    ulong m_[32];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    descent_rgs(const descent_rgs&);  // forbidden
    descent_rgs & operator = (const descent_rgs&);  // forbidden

public:
    explicit descent_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
#ifndef DESCENT_RGS_FIXARRAYS
        a_ = new ulong[n_];
        m_ = new ulong[n_];
#endif
        first();
    }

    ~descent_rgs()
    {
#ifndef DESCENT_RGS_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    const ulong *data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  m_[k] = 0;
//        for (ulong k=0; k<n_; ++k)  m_[k] = k;  // for non-changes: A000110
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 1;
        a_[0] = 0;
        for (ulong k=0; k<n_; ++k)  m_[k] = 0;
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

        ulong na = m_[j-1] + ( a_[j] < a_[j-1] );  // descents: A225588
        m_[j] = na;
        na += 1;
        for (ulong z=j+1; z<n_; ++z)  m_[z] = na;

//        const ulong na = m_[j-1] + ( a_[j] > a_[j-1] );  // ascents: A022493
//        for (ulong z=j; z<n_; ++z)  m_[z] = na;

//        ulong na = m_[j-1] + ( a_[j] != a_[j-1] );  // changes: A000522
//        m_[j] = na;
//        for (ulong z=j+1; z<n_; ++z) { na+=(a_[z-1]!=a_[z]);  m_[z] = na; }

//        ulong na = m_[j-1] + ( a_[j] == a_[j-1] );  // non-changes: A000110
//        m_[j] = na;
//        for (ulong z=j+1; z<n_; ++z) { na+=(a_[z-1]==a_[z]);  m_[z] = na; }


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
        m_[j] = m_[j-1] + ( a_[j] < a_[j-1] );
        const ulong na = m_[j] + 0;
        ulong i = j;
        while ( ++i < n_ )
        {
            a_[i] = na + 1;
            m_[i] = na;
        }
        return j;
    }

    ulong num_descents()  const
    // Return number of descents.
    { return  m_[n_-1]; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }


    bool OK()  const
    {
        ulong na = 0;
        if ( m_[0] != 0 )  return false;
        for (ulong j=1; j<n_; ++j)  // descent stats in m[] OK?
        {
            na += (a_[j] < a_[j-1]);
            if ( m_[j] != na )  return false;
        }

        return  is_descent_rgs(a_, n_);
    }
};
// -------------------------


#endif  // !defined HAVE_DESCENT_RGS_H__
