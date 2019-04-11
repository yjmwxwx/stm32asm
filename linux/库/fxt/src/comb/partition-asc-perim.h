#if !defined HAVE_PARTITION_ASC_PERIM_H__
#define      HAVE_PARTITION_ASC_PERIM_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-partition-asc.h"
#include "comb/is-sorts-in-runs-sorted.h"

#include "comb/print-composition-by-sorts.h"

#include "fxttypes.h"


class partition_asc_perim
// Partitions into parts of 2 sorts where sorts are oscillating.
// These are conjectured to be equinumerous with
//   non-empty sets of non-negative integers with perimeter n,
//   as defined in OEIS sequence A182372.
// Representations as weakly ascending lists.
// Lexicographic order: major order by sorts, minor by parts.
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;  // sorts of parts, 0 <= s_[j] <= ns1
    ulong n_;   // partition of n
    ulong m_;   // current partition has m parts

private:  // have pointer data
    partition_asc_perim(const partition_asc_perim&);  // forbidden
    partition_asc_perim & operator = (const partition_asc_perim&);  // forbidden

public:
    explicit partition_asc_perim(ulong n)
    {
        n_ = n;

        // need A055086(n) elements:
        a_ = new ulong[n_+1+(n_==0)];  // slightly wasteful
        s_ = new ulong[n_+1+(n_==0)];

        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        s_[0] = 1;  // returned by last_sort() when n==0
        s_[1] = 0;  // returned by first_sort() when n==0
        first();
    }

    ~partition_asc_perim()
    {
        delete [] a_;
        delete [] s_;
    }

    const ulong * data()  const  { return  a_ + 1; }
    const ulong * sdata()  const  { return  s_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong first_sort()  const  { return s_[1]; }
    ulong last_sort()  const  { return s_[m_]; }

    ulong num_parts()  const  {  return m_; }

private:
    ulong write_tail(ulong j, ulong s)
    {
        ulong p = a_[j-1] + s_[j-1];  // minimal part to write
        while ( p <= s )
        {
            a_[j] = p;
            s -= p;
            p = a_[j] + s_[j];
            j += 1;
        }

        j -= 1;
        a_[j] += s;

        return j;
    }

public:
    void first()
    {
        for (ulong k=1; k<=n_; ++k)  s_[k] = !(k & 1UL);

        if ( n_ )  m_ = write_tail(1, n_);
        else       m_ = 0;
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        if ( m_ > 1 )
        {  // could optimize via easy case
            ulong s = a_[m_] - 1;
            a_[m_-1] += 1;
            m_ = write_tail(m_, s);
            return  m_;
        }
        else  // occurs only twice
        {
            if ( s_[m_] == 1 )  return 0;  // current is last

            for (ulong k=1; k<=n_; ++k)  s_[k] = k & 1UL;
            m_ = write_tail(1, n_);
            return m_;
        }
    }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // valid sorts?
            if ( s_[j] > 1 )  return false;

        for (ulong j=1; j<m_; ++j)  // oscillating sorts?
            if ( s_[j] == s_[j+1] )  return false;

        if ( ! is_sorts_in_runs_sorted_asc(data(), sdata(), m_) )  return false;

        return true;
    }

    void print(const char *bla)  const
    { print_composition_with_sorts(bla, data(), sdata(), num_parts() ); }

    void print_rev(const char *bla)  const
    // print in weakly descending order
    { print_rev_composition_with_sorts(bla, data(), sdata(), num_parts() ); }

    void print_by_sorts(const char *bla)  const
    { print_composition_by_sorts(bla, data(), sdata(), num_parts() ); }

//    void print_aa()  const  // ASCII art
//    { print_composition_aa(data(), m_); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_PERIM_H__
