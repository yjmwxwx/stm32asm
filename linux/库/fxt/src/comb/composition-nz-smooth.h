#if !defined  HAVE_COMPOSITION_NZ_SMOOTH_H__
#define       HAVE_COMPOSITION_NZ_SMOOTH_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"
#include "comb/is-smooth.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_smooth
// Smooth compositions: compositions of n with first and last part 1
// and maximal absolute difference 1 between consecutive parts.
// Lexicographic order.
// Same as "1-dimensional sand piles", see OEIS sequence A186085.
{
public:
    ulong *a_;  // parts of the composition: a[1] + a[2] + ... + a[m] == n
    ulong n_;   // compositions of n
    ulong m_;   // number of parts in current composition

private:  // have pointer data
    composition_nz_smooth(const composition_nz_smooth&);  // forbidden
    composition_nz_smooth & operator = (const composition_nz_smooth&);  // forbidden

public:
    explicit composition_nz_smooth(ulong n)
    {
        n_ = n;  // works for n==0

        a_ = new ulong[n_+2];
        a_[0] = 0;  // sentinel
        a_[1] = 0;  // sentinel
        ++a_;  // nota bene

        first();
    }

    ~composition_nz_smooth()
    {
        --a_;
        delete [] a_;
    }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }


    ulong next()
    // Return number of parts.
    // Return 0 if current composition is last.
    {
        if ( m_ <= 3 )  return 0;   // current is last

        ulong z = a_[m_-1] + a_[m_];  // sum of parts we scanned over
        a_[m_-1] = 1;
        a_[m_] = 1;

        ulong s = 2;  // number of parts we scanned over
        ulong j = m_ - 2;

#if 0  // slightly slower version:
        while ( j > 1 )
        {
            if ( s >= a_[j] + 1 )  // can build falling slope
                if ( a_[j] <= a_[j-1] )  // still left-smooth
                    break;

            ++s;
            z += a_[j];
            a_[j] = 1;
            --j;
        }

        if ( j<=1 )  return 0;  // current is last

#else  // slightly faster version:

        while ( s < a_[j] + 1 )  // until we can build falling slope
        {
            ++s;
            z += a_[j];
            a_[j] = 1;
            --j;
        }

        while ( a_[j] > a_[j-1] )  // until still left-smooth after increment
        {
            z += a_[j];
            a_[j] = 1;
            --j;
        }

        if ( j==0 )  return 0;  // current is last

#endif


        ulong v = a_[j] + 1;
        a_[j] = v;
        --z;

        do  // build falling slope
        {
            ++j;
            --v;
            a_[j] = v;
            z -= v;
        }
        while ( v > 1 );

        m_ = j + z;  // attach z ones (already written)

        return  m_;
    }


    const ulong *data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        if ( m_ >= 1 )
        {
            if ( a_[1] > 1 )  return false;
            if ( a_[m_] > 1 )  return false;
        }

        if ( ! is_smooth(data(), num_parts(), 1 ) )  return false;

//        for (ulong j=2; j<=m_; ++j)  // left smooth?
//            if ( a_[j] > a_[j-1] + 1 )  return false;
//        for (ulong j=2; j<=m_; ++j)  // right smooth?
//            if ( a_[j-1] > a_[j] + 1 )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_SMOOTH_H__
