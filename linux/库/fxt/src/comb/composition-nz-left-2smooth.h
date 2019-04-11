#if !defined  HAVE_COMPOSITION_NZ_LEFT_2SMOOTH_H__
#define       HAVE_COMPOSITION_NZ_LEFT_2SMOOTH_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"
#include "comb/is-smooth.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_left_2smooth
// Left-2smooth compositions:
// compositions of n with maximal up-step 1,
// no consecutive up-steps, and first part 1.
// Lexicographic order.
// Cf. OEIS sequence A186085.
{
public:
    ulong *a_;  // parts of the composition: a[1] + a[2] + ... + a[m] == n
    ulong n_;   // compositions of n
    ulong m_;   // number of parts in current composition

private:  // have pointer data
    composition_nz_left_2smooth(const composition_nz_left_2smooth&);  // forbidden
    composition_nz_left_2smooth & operator = (const composition_nz_left_2smooth&);  // forbidden

public:
    explicit composition_nz_left_2smooth(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+2+(n==0)];
        a_[0] = 0;  // sentinel
        a_[1] = 0;  // sentinel
        a_[1+(n==0)] = 0;  // init with n==0
        a_ += 1;  // nota bene
        first();
    }

    ~composition_nz_left_2smooth()
    {
        a_ -= 1;
        delete [] a_;
    }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = (n_ ? n_ : 1 );  // make things work for n==0: one part ==0
    }


    ulong next()
    // Return number of parts.
    // Return 0 if current composition is last.
    {
        ulong z = a_[m_];
        a_[m_] = 1;

        ulong j = m_ - 1;  // j==0 for both n==1, and n==0
        while ( j )
        {
            // can read sentinel:
            if ( (a_[j] <= a_[j-1]) && (a_[j] <= a_[j-2]) )   break;

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

        return  is_left_2smooth(data(), num_parts());
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_composition_aa()  const  // ASCII art
    { ::print_composition_aa(data(), m_); }

    void print_fountain_aa()  const  // ASCII art
    { ::print_fountain_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_LEFT_2SMOOTH_H__
