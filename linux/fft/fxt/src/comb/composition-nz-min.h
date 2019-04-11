#if !defined HAVE_COMPOSITION_NZ_MIN_H__
#define      HAVE_COMPOSITION_NZ_MIN_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

#define COMPOSITION_NZ_MIN_FIXARRAYS  // default on, speedup


class composition_nz_min
// Compositions of n into positive parts >= mi.
// Lexicographic order.
{
public:
#ifndef COMPOSITION_NZ_MIN_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[64]; // up to 2^63 compositions
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts
    ulong mi_;  // all parts <= mi

private:  // have pointer data
    composition_nz_min(const composition_nz_min&);  // forbidden
    composition_nz_min & operator = (const composition_nz_min&);  // forbidden

public:
    explicit composition_nz_min(ulong n, ulong mi)
    {
        n_ = n;
        mi_ = mi;
#ifndef COMPOSITION_NZ_MIN_FIXARRAYS
        a_ = new ulong[n_+1];
#endif
        a_[0] = 0;  // unused

        first();
    }

    ~composition_nz_min()
    {
#ifndef COMPOSITION_NZ_MIN_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }

private:
    ulong write_tail(ulong s, ulong j)
    // Write lexicographically first composition of s, starting at index j.
    // Return last index written to.
    // Undefined for s < mi.
    {
        do
        {
            a_[j] = mi_;
            ++j;
            s -= mi_;
        }
        while ( s >= mi_ );

        --j;
        a_[j] += s;
        return j;
    }

public:

    void first()
    {
        if ( n_ >= mi_ )
            m_ = write_tail(n_, 1);
        else
            m_ = 0;
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong z = a_[m_];

        if ( z == mi_ )  // easy case
        {  // [*, Y, Z] --> [*, Y+Z]
            a_[m_-1] += z;
            --m_;
            return  m_;
        }

        ++a_[m_-1];

#if 1  // second easy case: m unchanged (speedup)
        if ( z <= 2 * mi_ )
        {  // [*, Y, Z] --> [*, Y+1, Z-1]
            a_[m_] = z - 1;
            return  m_;
        }
#endif

        // [*, Y, Z] --> [*, Y+1, M, M, ..., M, T]  where M=mi, and mi <= T < 2*mi
        m_ = write_tail(z-1, m_);
        return  m_;
    }


    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j) // all parts >= min?
            if ( a_[j] < mi_ )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_MIN_H__
