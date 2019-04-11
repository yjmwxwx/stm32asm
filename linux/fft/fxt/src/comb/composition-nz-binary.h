#if !defined HAVE_COMPOSITION_NZ_BINARY_H__
#define      HAVE_COMPOSITION_NZ_BINARY_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


//#define COMPOSITION_NZ_BINARY_FIXARRAYS  // default off


class composition_nz_binary
// Compositions of n into powers of 2, lexicographic order.
// Cf. OEIS sequence A023359.
{
public:
#ifndef COMPOSITION_NZ_BINARY_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[124]; // > 2^100 compositions
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_binary(const composition_nz_binary&);  // forbidden
    composition_nz_binary & operator = (const composition_nz_binary&);  // forbidden

public:
    explicit composition_nz_binary(ulong n)
    {
        n_ = n;
#ifndef COMPOSITION_NZ_BINARY_FIXARRAYS
        a_ = new ulong[n_+1 +(n_==0)];
#endif
        a_[0] = 0;  // sentinel, also returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0

        first();
    }

    ~composition_nz_binary()
    {
#ifndef COMPOSITION_NZ_BINARY_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }
    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
        if ( n_==0 )  // make n==0 work: one part ==0
        {
            a_[1] = 0;
            m_ = 1;
        }
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        ulong y = a_[m_-1];  // can read sentinel
        ulong s = a_[m_];
        a_[m_] = 1;

        ulong j = m_ - 1;
        while ( s < y )
        {
            a_[j] = 1;
            j -= 1;
            s += y;
            y = a_[j];  // can read sentinel
        }

        if ( j==0 )  return 0;  // current is last

        a_[j] = 2 * y;  // part doubled
        m_ = j + (s - y);  // tail is s-y ones

        return m_;
    }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // all parts powers of 2 ?
        {
            ulong v = a_[j];
            if ( !!(v&(v-1)) )  return false;
        }

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_BINARY_H__
