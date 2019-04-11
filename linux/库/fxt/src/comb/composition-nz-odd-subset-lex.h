#if !defined HAVE_COMPOSITION_NZ_ODD_SUBSET_LEX_H__
#define      HAVE_COMPOSITION_NZ_ODD_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"

#include "fxttypes.h"


#define COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS  // default on, speedup


class composition_nz_odd_subset_lex
// Compositions of n into positive odd parts, subset-lex order.
// Loopless algorithm.
// Cf. OEIS sequence A000045.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
#ifndef COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[128]; // > 2^85 compositions
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_odd_subset_lex(const composition_nz_odd_subset_lex&);  // forbidden
    composition_nz_odd_subset_lex & operator = (const composition_nz_odd_subset_lex&);  // forbidden

public:
    explicit composition_nz_odd_subset_lex(ulong n)
    {
        n_ = n;
#ifndef COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
#endif
        first();
    }

    ~composition_nz_odd_subset_lex()
    {
#ifndef COMPOSITION_NZ_ODD_SUBSET_LEX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[0] = 0;  // sentinel
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        if ( n_ & 1 )
        {
            a_[1] = n_;
            m_ = 1;
        }
        else
        {
            if ( n_==0 )  // make things work for n==0
            {
                a_[0] = 1;
                m_ = 0;
                return;
            }

            a_[1] = 1;
            a_[2] = n_ - 1;
            m_ = 2;
        }
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        const ulong z = a_[m_];

        if ( z != 1 )  // easy case: extend
        {  // [*, Z] --> [*, 1, 1, Z-2]
            a_[m_] = 1;
            // a_[m_+1] = 1;  // already ==1
            a_[m_+2] = z - 2;
            m_ += 2;
            return m_;
        }
        else  // z == 1
        {
            if ( m_ <= 2 )  return 0;  // current is last (n even)

            const ulong y = a_[m_-1];
            if ( y==1 )
            {  // [*, W, X, 1, 1] --> [*, W+2, X]
                if ( m_ == 3 )  return 0;  // current is last (n odd)
                a_[m_-3] += 2;
                m_ -= 2;
                return  m_;
            }
            else
            {  // [*, X, Y, 1] --> [*, X+2, 1, Y-2]
                a_[m_-2] += 2;
                a_[m_-1] = 1;
                a_[m_] = y - 2;
                return  m_;
            }
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


#endif  // !defined HAVE_COMPOSITION_NZ_ODD_SUBSET_LEX_H__
