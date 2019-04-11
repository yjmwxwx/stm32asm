#if !defined HAVE_COMPOSITION_NZ_MAX_H__
#define      HAVE_COMPOSITION_NZ_MAX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


#define COMPOSITION_NZ_MAX_FIXARRAYS  // default on, speedup


class composition_nz_max
// Compositions of n into positive parts <= mx.
// Lexicographic order.
{
public:
#ifndef COMPOSITION_NZ_MAX_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[128]; // > 2^85 compositions (for mx=2, else even more)
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts
    ulong mx_;  // all parts <= mx

private:  // have pointer data
    composition_nz_max(const composition_nz_max&);  // forbidden
    composition_nz_max & operator = (const composition_nz_max&);  // forbidden

public:
    explicit composition_nz_max(ulong n, ulong mx)
    {
        n_ = n;

        if ( mx == 0 )  mx = 1;
//        if ( mx > n )  mx = n;
        mx_ = mx;
#ifndef COMPOSITION_NZ_MAX_FIXARRAYS
        a_ = new ulong[n_+1 + (n_==0)];
#endif
        a_[0] = 0;  // sentinel; returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0

        first();
    }

    ~composition_nz_max()
    {
#ifndef COMPOSITION_NZ_MAX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }
    ulong max_part()  const
    {
        ulong t = 0;
        for (ulong j=1; j<=m_; ++j)
        { const ulong d = a_[j];  if ( d > t )  t = d; }
        return t;
    }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[1] = 0;  // make things work for n==0: one part ==0
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = ( n_ ? n_ : 1 );
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        ulong z = a_[m_];  // last part
        a_[m_] = 1;
        ulong j = m_ - 1;
        // GCC 4.9.1 issues a spurious warning
        // "array subscript is above array bounds"
        // This is a known bug in GCC.
        while ( a_[j] == mx_ )  // collect all max parts before last part
        {
            z += mx_;
            a_[j] = 1;
            --j;
        }

        if ( j==0 )  return 0;  // current is last

        a_[j] += 1;  // add one unit to last non-max part
        z -= 1;
        m_ = j + z;  // tail is all ones; already written

        return  m_;
    }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j) // all parts <= max?
            if ( a_[j] > mx_ )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_MAX_H__
