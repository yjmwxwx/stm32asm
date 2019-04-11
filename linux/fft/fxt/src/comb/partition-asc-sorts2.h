#if !defined HAVE_PARTITION_ASC_SORTS2_H__
#define      HAVE_PARTITION_ASC_SORTS2_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-partition-asc.h"
#include "comb/is-sorts-in-runs-sorted.h"

#include "comb/print-composition-by-sorts.h"

#include "fxttypes.h"


//#define PARTITION_ASC_SORTS2_FIXARRAYS  // default off


class partition_asc_sorts2
// Partitions into parts of s sorts, as weakly ascending lists.
// Lexicographic order: major order by parts, minor by sorts, where
// comparison proceeds as part1, sort1; part2, sort2; part3, sort3, etc.
// Cf. OEIS sequences (partitions of n into parts of s kinds):
// A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
// A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).
{
public:
#ifndef PARTITION_ASC_SORTS2_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong *s_;  // sorts of parts, 0 <= s_[j] <= ns1
#else
    ulong a_[448];  // > 2^66 partitions of 1 sort
    ulong s_[448];
#endif
    ulong n_;   // partition of n
    ulong m_;   // current partition has m parts
    ulong ns1_; // number of sorts - 1

private:  // have pointer data
    partition_asc_sorts2(const partition_asc_sorts2&);  // forbidden
    partition_asc_sorts2 & operator = (const partition_asc_sorts2&);  // forbidden

public:
    explicit partition_asc_sorts2(ulong n, ulong ns)
    // Should have: ns >= 1.
    {
        n_ = n;
        ns1_ = (ns ? ns-1 : 0 );
#ifndef PARTITION_ASC_SORTS2_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        s_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        s_[0] = ns1_;  // returned by last_sort() when n==0
        s_[1] = 0;  // returned by first_sort() when n==0
        first();
    }

    ~partition_asc_sorts2()
    {
#ifndef PARTITION_ASC_SORTS2_FIXARRAYS
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
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        if ( s_[m_] != ns1_ )  // a[m] is not last sort
        {
            s_[m_] += 1;  // next sort for current end
            return  m_;
        }

        // else:  a[m] is last sort
        if ( a_[m_] == n_ )  return 0;  // current is last

        if ( s_[m_-1] != ns1_ )  // previous part not last sort
        {
            const ulong s1 = s_[m_-1] + 1;
            s_[m_-1] = s1;  // next sort of previous part

            ulong y = a_[m_];
            const ulong x = a_[m_-1];
            while ( x <= y )
            {
                a_[m_] = x;
                s_[m_] = s1;
                y -= x;
                m_ += 1;
            }

            m_ -= 1;
            a_[m_] = x + y;

            if ( a_[m_] == x )  s_[m_] = s1;
            else                s_[m_] = 0;

            return  m_;
        }
        else  // previous part is last sort
        {
            ulong y = a_[m_] - 1;
            m_ -= 1;
            const ulong x = a_[m_] + 1;
            while ( x <= y )
            {
                a_[m_] = x;
                s_[m_] = 0;
                y -= x;
                m_ += 1;
            }
            a_[m_] = x + y;
            s_[m_] = 0;

            return  m_;
        }
    }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // valid sorts?
            if ( s_[j] > ns1_ )  return false;

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


#endif  // !defined HAVE_PARTITION_ASC_SORTS2_H__
