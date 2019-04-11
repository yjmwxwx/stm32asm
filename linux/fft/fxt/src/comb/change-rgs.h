#if !defined  HAVE_CHANGE_RGS_H__
#define       HAVE_CHANGE_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-change-rgs.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


// whether to use arrays instead of pointers:
#define CHANGE_RGS_FIXARRAYS  // default is on


class change_rgs
// Change sequences (restricted growth strings, RGS), lexicographic order.
// A change sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0,
//   d(k)>=0, and d(k) <= 1 + chg([d(1), d(2), ..., d(k-1)]) and chg(.)
//   counts the number of changes of its argument.
// See OEIS sequence A000522.
{
public:
#ifndef CHANGE_RGS_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of changes in prefix a[0,1,..,k]
#else
    ulong a_[32];  // > 2*10^34 change sequences
    ulong m_[32];
#endif
    ulong n_;   // Number of digits

private:  // have pointer data
    change_rgs(const change_rgs&);  // forbidden
    change_rgs & operator = (const change_rgs&);  // forbidden

public:
    explicit change_rgs(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
#ifndef CHANGE_RGS_FIXARRAYS
        a_ = new ulong[n_];
        m_ = new ulong[n_];
#endif
        first();
    }

    ~change_rgs()
    {
#ifndef CHANGE_RGS_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    const ulong *data()  const  { return a_; }

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

        ulong nc = m_[j-1] + ( a_[j] != a_[j-1] );  // changes: A000522
        m_[j] = nc;
        for (ulong z=j+1; z<n_; ++z) { nc+=(a_[z-1]!=a_[z]);  m_[z] = nc; }

//        ulong nc = m_[j-1] + ( a_[j] == a_[j-1] );  // non-changes: A000110
//        m_[j] = nc;
//        for (ulong z=j+1; z<n_; ++z) { nc+=(a_[z-1]==a_[z]);  m_[z] = nc; }


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
        m_[j] = m_[j-1] + ( a_[j] != a_[j-1] );
        ulong nc = m_[j] + 0;
        ulong i = j;
        while ( ++i < n_ )
        {
            nc += 1;
            a_[i] = nc;
            m_[i] = nc;
        }
        return j;
    }

    ulong num_changes()  const
    // Return number of changes.
    { return  m_[n_-1]; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        ulong nc = 0;
        if ( m_[0] != 0 )  return false;
        for (ulong j=1; j<n_; ++j)  // change stats in m[] OK?
        {
            nc += (a_[j] != a_[j-1]);
            if ( m_[j] != nc )  return false;
        }

        return  is_change_rgs(a_, n_);
    }
};
// -------------------------


#endif  // !defined HAVE_CHANGE_RGS_H__
