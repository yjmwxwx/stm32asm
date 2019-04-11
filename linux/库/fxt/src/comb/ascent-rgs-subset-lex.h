#if !defined  HAVE_ASCENT_RGS_SUBSET_LEX_H__
#define       HAVE_ASCENT_RGS_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-ascent-rgs.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

#include "jjassert.h"
#include "fxtio.h"


// whether to use arrays instead of pointers:
#define ASCENT_RGS_SUBSET_LEX_FIXARRAYS  // default on (speedup)


class ascent_rgs_subset_lex
// Ascent sequences (restricted growth strings, RGS), subset-lex order.
// An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(1)=0, d(k)>=0,
//   and d(k) <= 1 + asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the
//   number of ascents of its argument.
// The number of length-n RGS is (OEIS sequence A022493)
//   1, 1, 2, 5, 15, 53, 217, 1014, 5335, 31240, 201608, ...
{
public:
#ifndef ASCENT_RGS_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // digits of the RGS: a_[k] <= m_[k-1] + 1
    ulong *m_;  // m[k] = number of ascents in prefix a[0,1,..,k]
    // m[] is correct only in prefix m[0,...,tr]
    // m[tr] gives the total number of ascents
#else
    ulong a_[32];  // > 2^98 ascent sequences
    ulong m_[32];
#endif
    ulong n_;   // Number of digits
    ulong n1_;  // last track
    ulong tr_;  // current track (position of rightmost nonzero digit)

private:  // have pointer data
    ascent_rgs_subset_lex(const ascent_rgs_subset_lex&);  // forbidden
    ascent_rgs_subset_lex & operator = (const ascent_rgs_subset_lex&);  // forbidden

public:
    explicit ascent_rgs_subset_lex(ulong n)
    {
        n_ = n;
        n1_ = (n <= 1 ? 0 : n-1 );  // make things work for n==0
#ifndef ASCENT_RGS_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[n1_+1];
        m_ = new ulong[n1_+1];
#endif

        first();
    }

    ~ascent_rgs_subset_lex()
    {
#ifndef ASCENT_RGS_SUBSET_LEX_FIXARRAYS
        delete [] a_;
        delete [] m_;
#endif
    }

    const ulong *data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<=n1_; ++k)  a_[k] = 0;
        for (ulong k=0; k<=n1_; ++k)  m_[k] = 0;
        tr_ = (n1_!=0);
    }

    void last()
    {
        for (ulong k=0; k<=n1_; ++k)  a_[k] = 0;
        for (ulong k=0; k<=n1_; ++k)  m_[k] = 0;
        tr_ = n1_;
        a_[tr_] = (n1_ != 0);
        m_[tr_] = (n1_ != 0);
    }

    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = tr_;
        const ulong j1 = j - (j!=0);

        const ulong y1 = a_[j1];
        const ulong z1 = a_[j] + 1;

        const ulong u1 = m_[j1];

        if ( z1 <= u1 + 1 )  // can increment
        {
            a_[j] = z1;
            m_[j] = u1 + (z1 > y1);  // record ascent
            return tr_;
        }

        if ( j < n1_ )  // can attach new element
        {
            j += 1;
            m_[j] = u1 + 1; // record ascent
            a_[j] = 1;
            tr_ = j;
            return tr_;
        }

        a_[j] = 0;
        // scan for previous non-zero digit:
        ulong z;
        while ( j != 0 )
        {
            j -= 1;
            if ( (z=a_[j]) != 0 )  break;
        }

        if ( j==0 )  return 0;  // current is last

        const ulong y = a_[j-1];
        z -= 1;
        a_[j] = z;

        const ulong v = m_[j-1] + (z > y);
        m_[j] = v;  // record ascent

        j += 1;
        a_[j] = 1;
        m_[j] = v + (z==0); // for num_ascents()
        tr_ = j;

        return  tr_ - 1;
    }

    ulong prev()
    // Return position of leftmost change, zero with first.
    {
        ulong j = tr_;
        ulong z = a_[j];
        if ( z==0 )  return 0;  // current is last

        z -= 1;
        a_[j] = z;

        if ( z != 0 )  // just decrement
        {
            // record ascent:
            m_[tr_] = m_[tr_-1] + ( z > a_[j-1] );
            return tr_;
        }

        j -= 1;
        if ( j == 0 )  // next is last (happens just once)
        {
            a_[1] = 0;
            m_[1] = 0;  // record (non-)ascent
            tr_ = 0;
            return 1;
        }

        const ulong y = a_[j];
        if ( y > m_[j-1] )  // y is maximal, can detach
        {
            tr_ = j;
            return  j + 1;
        }

        const ulong y1 = y + 1;
        a_[j] = y1;  // increment previous digit

        jjassert( j != 0 );
        const ulong x = a_[j-1];

        // record ascent:
        const ulong u  = m_[j-1] + (y1 > x);
        do  { m_[j] = u; }  while ( j++ < n1_ );

        // last element maximal:
        tr_ = n1_;
        const ulong u1 = u + 1;
        m_[tr_] = u1;
        a_[tr_] = u1;

        return tr_ - 1;
    }

    ulong num_ascents()  const
    // Return number of ascents.
    { return  m_[tr_]; }

    void print(const char *bla, bool dfz=true)  const
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        // ascent stats in m[] OK?
        if ( m_[0] != 0 )  return false;
        ulong na = 0;
        for (ulong j=1; j<=tr_; ++j)
        {
            na += (a_[j] > a_[j-1]);
            if ( m_[j] != na )  return false;
        }

        return  is_ascent_rgs(data(), n1_);
    }
};
// -------------------------


#endif  // !defined HAVE_ASCENT_RGS_SUBSET_LEX_H__
