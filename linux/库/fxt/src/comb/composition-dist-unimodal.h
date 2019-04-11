#if !defined HAVE_COMPOSITION_DIST_UNIMODAL_H__
#define      HAVE_COMPOSITION_DIST_UNIMODAL_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "comb/comb-print.h"
#include "comb/print-composition-by-sorts.h"
#include "comb/print-composition-unimodal.h"

#include "fxttypes.h"

//#include <cmath>


class composition_dist_unimodal
// Strongly unimodal compositions into distinct parts.
// Representation as list of parts in increasing order,
//   with each part except for the last of 2 sorts.
// Cf. OEIS sequence A072706.
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;   // sorts of parts
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts

private:  // have pointer data
    composition_dist_unimodal(const composition_dist_unimodal&);  // forbidden
    composition_dist_unimodal & operator = (const composition_dist_unimodal&);  // forbidden

public:
    explicit composition_dist_unimodal(ulong n)
    {
        n_ = n;

        // We need floor((sqrt(1+8*n)-1)/2) elements:
        ulong k = 1,  s = n_;
        while ( s >= ( k + (k+1) ) )  { s -= k;  k += 1; }
        a_ = new ulong[k+1];
        s_ = new ulong[k+1];

        first();
    }

    ~composition_dist_unimodal()
    {
        delete [] a_;
        delete [] s_;
    }

    const ulong * data()  const  { return  a_ + 1; }
    const ulong * sdata()  const  { return  s_ + 1; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        s_[0] = 0;  // unused
        if ( n_ == 0 )  { m_=0;  return; }

        ulong k = 1;
        ulong s = n_;
        // split s into 1, 2, 3, 4, ..., k, z  where z >= k+1:
        while ( s >= ( k + (k+1) ) )
        {
            a_[k] = k;
            s_[k] = 0;
            s -= k;
            k += 1;
        }

        a_[k] = s;
        s_[k] = 0;
        m_ = k;
    }


    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong s1 = s_[m_-1];
        s_[m_-1] = 1 - s1;

        ulong s, k;
        if ( s1 == 1 )
        {
            s = a_[m_] + a_[m_-1];
            k = a_[m_-1] + 1;
            m_ -= 1;
        }
        else
        {
            s = a_[m_];
            k = a_[m_-1] + 1;
        }

        // split s into k, k+1, k+2, ..., y, z  where z >= y + 1:
        while ( s >= ( k + (k+1) ) )
        {
            a_[m_] = k;
            s -= k;
            k += 1;
            m_ += 1;
        }

        a_[m_] = s;

        return  m_;
    }


    bool OK()  const
    {
        for (ulong j=1; j<m_; ++j)  // parts distinct?
            if ( a_[j] == a_[j+1] )
                return false;

        ulong s = 0;  // sum of parts == n  ?
        for (ulong j=1; j<=m_; ++j)  s += a_[j];
        if ( s!=n_ )  return false;

        return true;
    }

    void print_with_sorts(const char *bla)  const
    { print_composition_with_sorts(bla, data(), sdata(), num_parts() ); }

    void print(const char *bla)  const
    { print_composition_unimodal(bla, data(), sdata(), num_parts() ); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_DIST_UNIMODAL_H__
