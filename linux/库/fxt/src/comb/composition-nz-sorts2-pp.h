#if !defined HAVE_COMPOSITION_NZ_SORTS2_PP_H__
#define      HAVE_COMPOSITION_NZ_SORTS2_PP_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"
#include "comb/is-sorts-in-runs-sorted.h"

//#include "comb/print-composition-aa.h"
#include "comb/print-composition-by-sorts.h"

#include "fxttypes.h"


#define COMPOSITION_NZ_SORTS2_PP_FIXARRAYS  // default on


class composition_nz_sorts2_pp
// Compositions of n into positive parts of s[k] sorts for part (size) k.
// Lexicographic order: major order by parts, minor by sorts, where
// comparison proceeds as part1, sort1; part2, sort2; part3, sort3, etc.
// Loopless algorithm.
// Cf. OEIS sequence A088305
//   compositions of n into one sort of 1's, two sorts of 2's, ..., k sorts of k's.
// Cf. OEIS sequences (compositions of n into (all) parts of s kinds):
// A011782 (s=1), A025192 (s=2), A002001 (s=3), A005054 (s=4),
// A052934 (s=5), A055272 (s=6), A055274 (s=7), and A055275 (s=8).
{
public:
#ifndef COMPOSITION_NZ_SORTS2_PP_FIXARRAYS
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;  // sorts of parts, 0 <= s_[j] <= ns1
    ulong *ns1_;  // ns1[j] is sort of part a[j]
#else
    ulong a_[64];
    ulong s_[64];
    ulong ns1_[64];  // number of sorts - 1 for each part size
#endif
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts

private:  // have pointer data
    composition_nz_sorts2_pp(const composition_nz_sorts2_pp&);  // forbidden
    composition_nz_sorts2_pp & operator = (const composition_nz_sorts2_pp&);  // forbidden

public:
    explicit composition_nz_sorts2_pp(ulong n, ulong ns, const ulong *vns=0)
    // Should have: ns >= 1.
    {
        n_ = n;
#ifndef COMPOSITION_NZ_SORTS2_PP_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        s_ = new ulong[n_+1+(n_==0)];
        ns1_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        s_[0] = 0;  // returned by last_sort() when n==0
        s_[1] = 0;  // returned by first_sort() when n==0
        ns1_[0] = 0;

        if ( vns )  // number of sorts given for all parts
        {
            for (ulong k=0; k<n; ++k)
                ns1_[k+1] = (vns[k] ? vns[k] - 1 : 0);  // avoid 'no sorts'
        }
        else
        {
            if ( ns==0 )  // k sorts of part (size) k
                for (ulong k=1; k<=n; ++k)  ns1_[k] = k - 1;
            else // use ns as number of sorts for all parts:
                for (ulong k=1; k<=n; ++k)  ns1_[k] = ns - 1;
        }

        first();
    }

    ~composition_nz_sorts2_pp()
    {
#ifndef COMPOSITION_NZ_SORTS2_PP_FIXARRAYS
        delete [] a_;
        delete [] s_;
        delete [] ns1_;
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
//        s_[1] = ns1_[1];
//        m_ = 1;
//    }

    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    // Loopless algorithm.
    {
        const ulong z = a_[m_];
        const bool q = (s_[m_] != ns1_[z]);

        if ( q )  // a[m] is not last sort
        {
            s_[m_] += 1;  // next sort on current end
            return  m_;
        }

        // a[m] is last sort
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong y = a_[m_-1];
        if ( s_[m_-1] != ns1_[y] )  // previous part not last sort
        {
            // [*, Y, Z] --> [*, Y, 1, 1, 1, ..., 1]  (Z trailing ones)
            s_[m_-1] += 1;  // next sort of previous part
            a_[m_] = 1;
            // all parts a[m+1], a[m+2], ..., a[n] are already ==1
            s_[m_] = 0;
            // all sorts s[m+1], s[m+2], ..., s[n] are already ==0
            m_ += z - 1;
            return  m_;
        }
        else  // previous part is last sort
        {
            // [*, Y, Z] --> [*, Y+1, 1, 1, 1, ..., 1]  (Z-1 trailing ones)
            a_[m_-1] += 1;
            s_[m_-1] = 0;  // previous parts of first sort
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
            if ( s_[j] > ns1_[a_[j]] )  return false;

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


#endif  // !defined HAVE_COMPOSITION_NZ_SORTS2_PP_H__
