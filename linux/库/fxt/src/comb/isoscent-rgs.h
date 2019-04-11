#if !defined  HAVE_ISOSCENT_RGS_H__
#define       HAVE_ISOSCENT_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-isoscent-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
#define ISOSCENT_RGS_FIXARRAYS  // default is on

class isoscent_rgs
// Isoscent sequences (restricted growth strings, RGS).
// An isoscent sequence is a sequence [d(1), d(2), ..., d(n)] where
//  d(1)=0, d(k)>=0, and d(k) <= 1 + eq([d(1), d(2), ..., d(k-1)])
//  where eq(.) counts the number of flat steps of its argument.
// Lexicographic order.
// See OEIS sequence A000110.
{
public:
#ifndef ISOSCENT_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of isoscents in prefix a[0,1,..,k]
#else
    ulong a_[32];  // > 10^25 isoscent sequences
    ulong m_[32];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    isoscent_rgs(const isoscent_rgs&);  // forbidden
    isoscent_rgs & operator = (const isoscent_rgs&);  // forbidden

public:
    explicit isoscent_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
#ifndef ISOSCENT_RGS_FIXARRAYS
        a_ = new ulong[n_];
        m_ = new ulong[n_];
#endif
        first();
    }

    ~isoscent_rgs()
    {
#ifndef ISOSCENT_RGS_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    const ulong *data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  m_[k] = k;  // for non-changes: A000110
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

        ulong na = m_[j-1] + ( a_[j] == a_[j-1] );  // non-changes: A000110
        m_[j] = na;
        for (ulong z=j+1; z<n_; ++z) { na+=(a_[z-1]==a_[z]);  m_[z] = na; }

        return j;
    }

    ulong num_flat_steps()  const
    // Return number of flat steps.
    { return  m_[n_-1]; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }


    bool OK()  const
    {
        ulong na = 0;
        if ( m_[0] != 0 )  return false;
        for (ulong j=1; j<n_; ++j)  // isoscent stats in m[] OK?
        {
            na += (a_[j] == a_[j-1]);
            if ( m_[j] != na )  return false;
        }

        return  is_isoscent_rgs(a_, n_);
    }
};
// -------------------------


#endif  // !defined HAVE_ISOSCENT_RGS_H__
