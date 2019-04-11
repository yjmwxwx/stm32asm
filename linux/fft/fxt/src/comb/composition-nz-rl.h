#if !defined HAVE_COMPOSITION_NZ_RL_H__
#define      HAVE_COMPOSITION_NZ_RL_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/composition-nz-rank.h"
#include "comb/print-composition-aa.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class composition_nz_rl
// Compositions of n into positive parts, order by run-length rank.
// Loopless algorithm.
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_rl(const composition_nz_rl&);  // forbidden
    composition_nz_rl & operator = (const composition_nz_rl&);  // forbidden

public:
    explicit composition_nz_rl(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+2+(n_==0)];
        a_[0] = 1;  // sentinel for n==0
        ++a_;  // nota bene
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        first();
    }

    ~composition_nz_rl()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }


    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[1] = n_;
        m_ = ( n_ ? 1 : 0 );
    }

    void last()
    {
        if ( n_ <= 1 )
        {
            a_[n_] =  n_;
            m_ = n_;
        }
        else
        {
            a_[1] = 1;
            a_[2] = n_ - 1;
            m_ = 2;
        }
    }


    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // Loopless algorithm.
    {
        if ( (m_ & 1) != 0 )  // last part corresponds to a run of zeros
        {
            const ulong z = a_[m_] - 1;
            if ( z )  // [*, Z]  --> [*, Z-1, 1]
            {
                a_[m_] = z;
                ++m_;
                a_[m_] = 1;
                return m_;
            }
            else  // [*, Y, 1] --> [*, Y+1]
            {
                if ( m_ == 1 )  return 0;  // current is last (with n==1 only)
                --m_;
                a_[m_] += 1;
                return m_;
            }
        }
        else  // last part corresponds to a run of ones
        {
            // m==0 for n==0, so we end up here with n==0
            const ulong z = a_[m_];
            const ulong y = a_[m_-1] - 1;  // can read sentinel a[-1]
            if ( y )  // [*, Y, Z] --> [*, Y-1, 1, Z]
            {
                a_[m_-1] = y;
                a_[m_] = 1;
                ++m_;
                a_[m_] = z;
                return m_;
            }
            else  // [*, X, 1, Z] --> [*, X+1, Z]
            {
                if ( m_ <= 2 )  return 0;  // current is last
                // (m==0 only for n==0, otherwise m==2)

                a_[m_-2] += 1;
                --m_;
                a_[m_] = z;
                return m_;
            }
        }
    }


    ulong prev()
    // Return number of parts of generated composition.
    // Return zero if the current is the first composition.
    // Loopless algorithm.
    {
        if ( m_ <= 1 )  return 0;  // current is first

        if ( (m_ & 1) == 0 )  // last part corresponds to a run of ones
        {
            const ulong z = a_[m_] - 1;
            if ( z )  // [*, Z]  --> [*, Z-1, 1]
            {
                a_[m_] = z;
                ++m_;
                a_[m_] = 1;
                return m_;
            }
            else  // [*, Y, 1] --> [*, Y+1]
            {
                --m_;
                a_[m_] += 1;
                return m_;
            }
        }
        else  // last part corresponds to a run of zeros
        {
            // m==0 for n==0, so we end up here with n==0
            const ulong z = a_[m_];
            const ulong y = a_[m_-1] - 1;  // can read sentinel
            if ( y )  // [*, Y, Z] --> [*, Y-1, 1, Z]
            {
                a_[m_-1] = y;
                a_[m_] = 1;
                ++m_;
                a_[m_] = z;
                return m_;
            }
            else  // [*, X, 1, Z] --> [*, X+1, Z]
            {
                a_[m_-2] += 1;
                --m_;
                a_[m_] = z;
                return m_;
            }
        }
    }


    ulong rank()  const
    // Return rank r of current composition, 0 <= r < 2**(n-1).
    { return  composition_nz_rl_rank(a_+1, num_parts()); }

    ulong unrank(ulong r)
    // Return number of parts m of generated composition, 0 <= m <= n.
    { m_ = composition_nz_rl_unrank(r, a_+1, n_);  return m_; }

    bool OK()  const
    { return is_composition_nz(data(), num_parts(), n_); }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_RL_H__
