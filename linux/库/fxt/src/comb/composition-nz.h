#if !defined HAVE_COMPOSITION_NZ_H__
#define      HAVE_COMPOSITION_NZ_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/composition-nz-rank.h"

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"

//#include "jjassert.h"


#define COMPOSITION_NZ_FIXARRAYS  // default on, speedup


class composition_nz
// Compositions of n into positive parts, lexicographic order.
// Loopless algorithm for successor.
{
public:
#ifndef COMPOSITION_NZ_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[64];
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz(const composition_nz&);  // forbidden
    composition_nz & operator = (const composition_nz&);  // forbidden

public:
    explicit composition_nz(ulong n)
    {
        n_ = n;
#ifndef COMPOSITION_NZ_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        first();
    }

    ~composition_nz()
    {
#ifndef COMPOSITION_NZ_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }

    void last()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        a_[1] = n_;
        m_ = 1;
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    // Loopless algorithm.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        // [*, Y, Z] --> [*, Y+1, 1, 1, 1, ..., 1]  (Z-1 trailing ones)
        a_[m_-1] += 1;
        const ulong z = a_[m_];
        a_[m_] = 1;
        // all parts a[m+1], a[m+2], ..., a[n] are already ==1
        m_ += z - 2;

        return  m_;
    }

    ulong prev()
    // Return number of parts of generated composition.
    // Return zero if the current is the first composition.
    // Can be made loopless by keeping list of elements != 1.
    {
        if ( m_ >= n_ )  return 0;  // current is first

        const ulong z = a_[m_];
        if ( z!=1 )  // easy case
        {  // [*, Z] --> [*, Z-1, 1]
            a_[m_] = z - 1;
            ++m_;
            return  m_;
        }
        // here z==1

#if 0  // default off, slight slowdown
        const ulong t = a_[m_-1] - 1;
        if ( t != 0 )  // easy case
        {  // [*, Y, 1] --> [*, Y-1, 2]]
            a_[m_-1] = t;
            a_[m_] = 2;
            return  m_;
        }
#endif

        ulong j = m_;
        do  { --j; }  while ( a_[j] == 1 );  // scan over ones
        // [*, Y, 1, 1, ..., 1]  (q trailing ones) --> [*, Y-1, q+1]
        --a_[j];
        a_[j+1] =  m_ - j + 1;
        m_ = j + 1;
        return  m_;
    }


    ulong rank()  const
    // Return rank r of current composition, 0 <= r < 2**(n-1).
    {
#if 1
        return  composition_nz_rank(a_+1, m_);
#else
        ulong r = 0;
        ulong b = 1;
        ulong j = m_; // read from a[m], a[m-1], ..., a[1]
        while ( j )
        {
            ulong p = a_[j];
//            jjassert( p );
            while ( --p != 0 )
            {
                r |= b;
                b <<= 1;
            }
            b <<= 1;

            --j;
        }
        return  r;
#endif
    }

    ulong unrank(ulong r)
    // Return number of parts m of generated composition, 1 <= m <= n.
    {
#if 1
        m_ = composition_nz_unrank(r, a_+1, n_);
        // set all trailing elements to 1:
        for (ulong j=m_+1; j<=n_; ++j)  a_[j] = 1;

#else
        ulong b = 1UL << (n_-1);
        r &= (b<<1) - 1;  // take modulo 2**n

        ulong s = 0;
        ulong m = 0;
        while ( s < n_ )
        {
            ++m;  // write to a[1], a[2], ...
            b >>= 1;
            ulong p = 1;
            while ( r & b )
            {
                ++p;
                b >>= 1;
            }
            a_[m] = p;
            s += p;
        }
//        jjassert( s == n_ );

        // set all trailing elements to 1:
        for (ulong j=m+1; j<=n_; ++j)  a_[j] = 1;

        m_ = m;
#endif
        return m_;
    }

    bool OK()  const
    { return is_composition_nz(data(), num_parts(), n_); }

    void print(const char *bla)  const
    { print_vec(bla, data(), num_parts(), false); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), num_parts()); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_H__
