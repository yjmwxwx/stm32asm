#if !defined HAVE_COMPOSITION_NZ_SORTS_H__
#define      HAVE_COMPOSITION_NZ_SORTS_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"
#include "comb/is-sorts-in-runs-sorted.h"

//#include "comb/print-composition-aa.h"
#include "comb/print-composition-by-sorts.h"

#include "fxttypes.h"


#define COMPOSITION_NZ_SORTS_FIXARRAYS  // default on, speedup


class composition_nz_sorts
// Compositions of n into positive parts of s sorts.
// Lexicographic order: major order by sorts, minor by parts, where
// comparison proceeds as sort1, part1; sort2, part2; sort3, part3, etc.
// Loopless algorithm.
// Cf. OEIS sequences (compositions of n into parts of s kinds):
// A011782 (s=1), A025192 (s=2), A002001 (s=3), A005054 (s=4),
// A052934 (s=5), A055272 (s=6), A055274 (s=7), and A055275 (s=8).
{
public:
#ifndef COMPOSITION_NZ_SORTS_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;  // sorts of parts, 0 <= s_[j] <= ns1
#else
    ulong a_[64];
    ulong s_[64];
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts
    ulong ns1_; // number of sorts - 1

private:  // have pointer data
    composition_nz_sorts(const composition_nz_sorts&);  // forbidden
    composition_nz_sorts & operator = (const composition_nz_sorts&);  // forbidden

public:
    explicit composition_nz_sorts(ulong n, ulong ns)
    // Should have: ns >= 1.
    {
        n_ = n;
        ns1_ = (ns ? ns-1 : 0 );
#ifndef COMPOSITION_NZ_SORTS_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        s_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        s_[0] = ns1_;  // returned by last_sort() when n==0
        s_[1] = 0;  // returned by first_sort() when n==0
        first();
    }

    ~composition_nz_sorts()
    {
#ifndef COMPOSITION_NZ_SORTS_FIXARRAYS
        delete [] a_;
        delete [] s_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }
    const ulong * sdata()  const  { return  s_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong first_sort()  const  { return s_[1]; }
    ulong last_sort()  const  { return s_[m_]; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        for (ulong k=1; k<=n_; ++k)  s_[k] = 0;
        m_ = n_;
    }

//    void last()
//    {
//        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
//        a_[1] = n_;
//        for (ulong k=1; k<=n_; ++k)  s_[k] = 0;
//        s_[1] = ns_ - 1;
//        m_ = 1;
//    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    // Loopless algorithm.
    {
        const bool q = (s_[m_] != ns1_);
        const ulong z = a_[m_];
        if ( q )  // a[m] is not last sort
        {
            // [*, Z] --> [*, 1, 1, ..., 1] (Z-1 trailing ones)
            a_[m_] = 1;
            s_[m_] += 1;  // next sort on current end
            m_ += z - 1;
            // all parts a[m+1], a[m+2], ..., a[n] are already ==1
            // all sorts s[m+1], s[m+2], ..., s[n] are already ==0
            return  m_;
        }
        else  // a[m] is last sort
        {
            if ( m_ <= 1 )  return 0;  // current is last

            // [*, Y, Z] --> [*, Y+1, 1, 1, 1, ..., 1]  (Z-1 trailing ones)
            a_[m_-1] += 1;
            a_[m_] = 1;
            // all parts a[m+1], a[m+2], ..., a[n] are already ==1
            s_[m_] = 0;
            // all sorts s[m+1], s[m+2], ..., s[n] are already ==0
            m_ += z - 2;
            return  m_;
        }
    }

    bool sorts_in_runs_sorted(bool aq=true)  const
    // Return whether for all runs of equal parts
    // the sorts of parts are monotone.
    // By default test for ascending order (aq==true),
    // otherwise for decreasing order.
    {
        if ( aq )  return is_sorts_in_runs_sorted_asc(data(), sdata(), m_);
        else       return is_sorts_in_runs_sorted_desc(data(), sdata(), m_);
    }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // valid sorts?
            if ( s_[j] > ns1_ )  return false;

        return true;
    }

    void print(const char *bla)  const
    { print_composition_with_sorts(bla, data(), sdata(), num_parts() ); }

    void print_by_sorts(const char *bla)  const
    { print_composition_by_sorts(bla, data(), sdata(), num_parts() ); }

//    void print_aa()  const  // ASCII art
//    { print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_SORTS_H__
