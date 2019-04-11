#if !defined HAVE_COMPOSITION_NZ_UPSTEP_H__
#define      HAVE_COMPOSITION_NZ_UPSTEP_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"

//#include "jjassert.h"


class composition_nz_upstep
// Compositions of n into positive parts, with limit on up-step.
// Lexicographic order.
// Cf. OEIS sequences A003116 (max up-step 1)
// and A224959 (max up-step 2).
// Max up-step 0 gives partitions as weakly descending lists.
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts
    ulong u_;   // maximal allowed up-step

private:  // have pointer data
    composition_nz_upstep(const composition_nz_upstep&);  // forbidden
    composition_nz_upstep & operator = (const composition_nz_upstep&);  // forbidden

public:
    explicit composition_nz_upstep(ulong n, ulong u)
    {
        n_ = n;
        u_ = u;
        a_ = new ulong[n_+1+(n_==0)];
        a_[0] = n_;  // sentinel, also returned by last_part() when n==0
        a_[1] = 0;   // returned by first_part() when n==0
        first();
    }

    ~composition_nz_upstep()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }

//    void last()
//    {
//    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong j = m_;
        ulong s = a_[j];    // sum of all parts scanned over
        ulong y = a_[j-1];  // value we try to increment
        ulong x = a_[j-2];  // can read sentinel

        a_[j] = 1;
        --j;
        while ( y + 1 > x + u_ )  // cannot increment
        {
            a_[j] = 1;
            s += y;
            y = x;
            --j;
            x = a_[j-1];  // can read sentinel
        }

        a_[j] = y + 1;  // == a[j] + 1
        s -= 1;  // 1 borrowed from s
        // all parts a[m+1], a[m+2], ..., a[n] are already ==1
        m_ = j + s;

        return  m_;
    }

//    ulong prev()
//    {
//        if ( m_ >= n_ )  return 0;  // current is first
//    }


    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=2; j<=m_; ++j)  // check that up-steps are <= u
            if ( a_[j] > a_[j-1] + u_ )
                return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_UPSTEP_H__
