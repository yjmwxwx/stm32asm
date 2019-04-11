#if !defined HAVE_COMPOSITION_NZ_RESTRPREF_H__
#define      HAVE_COMPOSITION_NZ_RESTRPREF_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_restrpref
// Compositions of n into positive parts with restricted prefixes.
// Lexicographic order.
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts (m!=0 if valid composition)

    typedef bool (* cond_func)(const ulong*, ulong);
    cond_func cond;  // condition function

private:  // have pointer data
    composition_nz_restrpref(const composition_nz_restrpref&);  // forbidden
    composition_nz_restrpref & operator = (const composition_nz_restrpref&);  // forbidden

public:
    explicit composition_nz_restrpref(ulong n, cond_func cnd)
    // Should have n>=1, (for n==0 zero compositions are reported).
    {
        n_ = n;
        a_ = new ulong[n_+1+(n_==0)];
        a_[0] = 0;  //  returned by last_part() when n==0
        a_[1] = 0;  //  returned by first_part() when n==0
        first(cnd);
    }

    ~composition_nz_restrpref()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    bool valid()  const { return  m_; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong num_parts()  const  {  return m_; }

public:
    void first(cond_func cnd = 0)
    // Try to generate first composition.
    // Whether this was successful is returned by valid().
    {
        if ( cnd != 0 )  cond = cnd;

        ulong s = n_;
        for (ulong j=1; j<=n_; ++j)
        {
            a_[j] = 1;

            if ( ! cond( data(), j-1 ) )  // hand over to next()
            {
                if ( s >= 2 )  // move rest beyond position
                {
                    j += 1;
                    s -= 1;
                }

                m_ = j;  // next() starts with position m
                a_[j] = s;

                next();

                return;
            }
            --s;
        }

        m_ = n_;
    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        if ( m_ <= 1 )  { m_=0;  return 0; } // current is last

        ulong s = a_[m_] - 1;  // sum of parts in tail
        a_[m_] = 1;  // leave ones
        ulong j = m_ - 1;
        a_[j] += 1;

        do
        {
            const ulong y = a_[j];
            ulong i;

            for (i=0; i<=s; ++i)  // try for each value
            {
                a_[j] = y + i;
                if ( cond( data(), j-1) )  // found allowed part
                    break;
            }

            if ( i > s )  // no increment allowed here: go left
            {
                a_[j] = 1;   // leave ones
                --j;         // go left
                a_[j] += 1;  // add (at least) 1 to the left
                s += y - 1;  // adjust sum
            }
            else  // found allowed part: done or go right
            {
                s -= i;  // adjust sum: we left i units at index j

                if ( s==0 )  // done
                {
                    m_ = j;
                    return m_;
                }

                ++j;         // go right
                a_[j] = 1;   // put (at least) 1 to the right
                s -= 1;      // adjust sum
            }
        }
        while ( j!=0 );

        m_ = 0;
        return m_;  // current is last
    }

    bool OK()  const
    { return is_composition_nz(data(), num_parts(), n_); }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_composition_aa()  const  // ASCII art
    { ::print_composition_aa(data(), m_); }

    void print_fountain_aa()  const  // ASCII art
    { ::print_fountain_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_RESTRPREF_H__
