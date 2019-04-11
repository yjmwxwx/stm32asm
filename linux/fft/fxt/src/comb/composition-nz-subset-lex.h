#if !defined HAVE_COMPOSITION_NZ_SUBSET_LEX_H__
#define      HAVE_COMPOSITION_NZ_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/composition-nz-rank.h"
#include "bits/bitlex.h"

#include "comb/print-composition-aa.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


#define COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS  // default on

// choose versions for next() and prev():
#define COMPOSITION_NZ_SUBSET_LEX_NEXT_A  // default on
#define COMPOSITION_NZ_SUBSET_LEX_PREV_A  // default on


class composition_nz_subset_lex
// Compositions of n into positive parts.
// Gray code such that either two adjacent positions change
//   or one unit is moved by two positions.
// The number of parts changes by one at each transition.
// Loopless algorithm.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
#ifndef COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[64];
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_subset_lex(const composition_nz_subset_lex&);  // forbidden
    composition_nz_subset_lex & operator = (const composition_nz_subset_lex&);  // forbidden

public:
    explicit composition_nz_subset_lex(ulong n)
    {
        n_ = n;
#ifndef COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[n_+1+(n==0)];
#endif
        first();
    }

    ~composition_nz_subset_lex()
    {
#ifndef COMPOSITION_NZ_SUBSET_LEX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }
    ulong num_parts()  const  {  return m_; }


    void first()
    {
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = n_;   // returned by first_part() when n==0
        m_ = ( n_ ? 1 : 0 );
    }

    void last()
    {
        if ( n_ >= 2 )
        {
            a_[1] = n_ - 1;
            a_[2] = 1;
            for (ulong j=2; j<=n_; ++j)  a_[j] = 1;
            m_ = 2;
        }
        else
        {
            a_[1] = n_;
            m_ = n_;
        }
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    // Loopless algorithm.
    {
#ifdef COMPOSITION_NZ_SUBSET_LEX_NEXT_A  // version A:
        const ulong z = a_[m_];
        if ( z<=1 )  // move one unit two places left
        { //   [*, X, Y, 1] --> [*, X+1, Y]
            if ( m_ <= 2 )  return 0;  // current is last
            m_ -= 1;
            a_[m_-1] += 1;
            return  m_;
        }
        else  // move all but one unit right
        { //   [*, Y, Z] --> [*, Y, 1, Z-1]
            a_[m_] = 1;
            m_ += 1;
            a_[m_] = z - 1;
            return  m_;
        }

#else  // version B:  very fast if case n==0 _not_ handled

        const ulong z1 = a_[m_] - 1;
        if ( z1 )  // move all but one unit right
        { //   [*, Y, Z] --> [*, Y, 1, Z-1]
//            if ( m_==0 )  return 0;  // make n==0 work: slowdown!
            a_[m_] = 1;
            m_ += 1;
            a_[m_] = z1;
            return  m_;
        }
        else  // move one unit two places left
        { //   [*, X, Y, 1] --> [*, X+1, Y]
            if ( m_ <= 2 )  return 0;  // current is last
            m_ -= 1;
            a_[m_-1] += 1;
            return  m_;
        }
#endif
    }

    ulong prev()
    // Return number of parts of generated composition.
    // Return zero if the current is the first composition.
    // Loopless algorithm.
    {
        if ( m_ <= 1 )  return 0;  // current is first

#ifdef COMPOSITION_NZ_SUBSET_LEX_PREV_A  // version A:
        const ulong y = a_[m_-1];
        if ( y==1 )  // add Z to left place
        { //   [*, 1, Z] --> [*, Z+1]
            const ulong z = a_[m_];
            a_[m_-1] = z + 1;
            a_[m_] = 1;
            m_ -= 1;
            return  m_;
        }
        else  // move one unit two places right
        { //   [*, Y, Z] --> [*, Y-1, Z, 1]
            a_[m_-1] = y - 1;
            m_ += 1;
            // a[m] == 1 already
            return  m_;
        }

#else  // version B:
        const ulong m1 = m_ - 1;
        const ulong y1 = a_[m1] - 1;
        if ( y1==0 )  // add Z to left place
        { //   [*, 1, Z] --> [*, Z+1]
            const ulong z = a_[m_];
            a_[m1] = z + 1;
            a_[m_] = 1;
            m_ -= 1;
            return  m_;
        }
        else  // move one unit two places right
        { //   [*, Y, Z] --> [*, Y-1, Z, 1]
            a_[m1] = y1;
            m_ += 1;
            // a[m] == 1 already
            return  m_;
        }
#endif
    }

    ulong rank()  const
    // Return rank r of current composition, 0 <= r < 2**(n-1).
    {
#if 1
        return composition_nz_subset_lex_rank(data(), m_, n_);
#else
        ulong r = composition_nz_rank(data(), m_);
        const ulong w = (1UL<<n_) - 1;
        r ^= w;
        r = lexrev2negidx(r);
        r ^= w;
        return r;
#endif
    }

    ulong unrank(ulong r)
    // Return number of parts m of generated composition, 1 <= m <= n.
    {
#if 1
        return composition_nz_subset_lex_unrank(r, a_+1, n_);
#else
        if ( n_==0 )  return 0;
        const ulong w = (1UL<<n_) - 1;
        ulong r2 = +r;
        r2 ^= w;
        r2 = negidx2lexrev(r2);
        r2 ^= w;
        m_ = composition_nz_unrank(r2, a_+1, n_);
        return m_;
#endif
    }

    bool OK()  const
    { return is_composition_nz(data(), num_parts(), n_); }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_SUBSET_LEX_H__
