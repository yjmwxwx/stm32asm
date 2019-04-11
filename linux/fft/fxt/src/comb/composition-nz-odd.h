#if !defined HAVE_COMPOSITION_NZ_ODD_H__
#define      HAVE_COMPOSITION_NZ_ODD_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


#define COMPOSITION_NZ_ODD_FIXARRAYS  // default on, speedup


class composition_nz_odd
// Compositions of n into positive odd parts, lexicographic order.
// Loopless algorithm.
// Cf. OEIS sequence A000045.
{
public:
#ifndef COMPOSITION_NZ_ODD_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[128]; // > 2^85 compositions
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_odd(const composition_nz_odd&);  // forbidden
    composition_nz_odd & operator = (const composition_nz_odd&);  // forbidden

public:
    explicit composition_nz_odd(ulong n)
    {
        n_ = n;
#ifndef COMPOSITION_NZ_ODD_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // sentinel, also returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0

        first();
    }

    ~composition_nz_odd()
    {
#ifndef COMPOSITION_NZ_ODD_FIXARRAYS
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
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        if ( a_[m_] != 1 )  // easy case
        {  // [*, Y, Z] --> [*, Y+2, 1, 1, .., 1]  (Z-2 ones)
            if ( m_ <= 1 )  return 0;  // current is last

            const ulong z = a_[m_];
            a_[m_] = 1;
            a_[m_-1] += 2;
            // all parts a[m+1], a[m+2], ..., a[n] are already ==1
            m_ += z - 3;
            return m_;
        }
        else
        {  // [*, X, Y, 1] --> [*, X+2, 1, 1, ..., 1] (Y-2 ones)
            if ( m_ < 3 )  return 0;  // current is last

            const ulong y = a_[m_-1];
            // all parts a[m], a[m+1], ..., a[n] are already ==1
            a_[m_-1] = 1;
            a_[m_-2] += 2;
            m_ += y - 3;
            return  m_;
        }
    }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j) // all parts odd?
            if ( 0==(a_[j] & 1UL) )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_ODD_H__
