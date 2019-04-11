#if !defined  HAVE_COMPOSITION_NZ_LEFT_SMOOTH_H__
#define       HAVE_COMPOSITION_NZ_LEFT_SMOOTH_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/is-smooth.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_left_smooth
// Left-smooth compositions: compositions of n
// with maximal up-step <= 1 and first part 1.
// Lexicographic order.
// Same as "fountains of coins", see OEIS sequence A005169.
{
public:
    ulong *a_;  // parts of the composition: a[1] + a[2] + ... + a[m] == n
    ulong n_;   // compositions of n
    ulong m_;   // number of parts in current composition

private:  // have pointer data
    composition_nz_left_smooth(const composition_nz_left_smooth&);  // forbidden
    composition_nz_left_smooth & operator = (const composition_nz_left_smooth&);  // forbidden

public:
    explicit composition_nz_left_smooth(ulong n)
    {
        n_ = n;
        if ( n_ )  a_ = new ulong[n_+2];
        else
        {
            a_ = new ulong[n_+3];
            a_[2] = 0;  // special case n==0: one part, which is zero
        }

        a_[0] = 0;  // sentinel
        ++a_;  // nota bene
        a_[0] = 0;  // sentinel

        first();
    }

    ~composition_nz_left_smooth()
    {
        --a_;
        delete [] a_;
    }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
//        m_ = n_;
        m_ = (n_ ? n_ : 1 );  // make things work for n==0: one part ==0
    }


    ulong next()
    // Return number of parts.
    // Return 0 if current composition is last.
    {
        ulong z = a_[m_];
        a_[m_] = 1;

        ulong j = m_ - 1;  // j==0 for both n==1, and n==0
        while ( a_[j] > a_[j-1] )
//        while ( a_[j] > a_[j-1] - 1 )  // partitions in weakly descending order
        {
            z += a_[j];
            a_[j] = 1;
            --j;
        }

        if ( j==0 )  return 0;  // current is last

        ++a_[j];
        --z;
        m_ = j + z;

        return  m_;
    }


    const ulong *data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }


    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )
            return false;
        if ( data()[0] > 1 )  return false;
        return  is_left_smooth(data(), m_, 1);
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_composition_aa()  const  // ASCII art
    { ::print_composition_aa(data(), m_); }

    void print_fountain_aa()  const  // ASCII art
    { ::print_fountain_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_LEFT_SMOOTH_H__
