#if !defined HAVE_PARTITION_ASC_SORTS_H__
#define      HAVE_PARTITION_ASC_SORTS_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-partition-asc.h"
#include "comb/is-sorts-in-runs-sorted.h"

#include "comb/print-composition-by-sorts.h"

#include "fxttypes.h"

//#include "fxtio.h"
//#include "jjassert.h"


#define PARTITION_ASC_SORTS_FIXARRAYS  // default on
// speedup with gcc 4.8.0

class partition_asc_sorts
// Partitions into parts of s sorts, as weakly ascending lists.
// Lexicographic order: major order by parts, minor by sorts, where
// comparison proceeds as sort1, part1; sort2, part2; sort3, part3, etc.
// Cf. OEIS sequences (partitions of n into parts of s kinds):
// A000041 (s=1), A000712 (s=2), A000716 (s=3), A023003 (s=4),
// A023004 (s=5), A023005 (s=6), A023006 (s=7), and A023007 (s=8).
{
public:
#ifndef PARTITION_ASC_SORTS_FIXARRAYS
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
    partition_asc_sorts(const partition_asc_sorts&);  // forbidden
    partition_asc_sorts & operator = (const partition_asc_sorts&);  // forbidden

public:
    explicit partition_asc_sorts(ulong n, ulong ns)
    // Should have: ns >= 1.
    {
        n_ = n;
        ns1_ = (ns ? ns-1 : 0 );

#ifndef PARTITION_ASC_SORTS_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        s_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = (n_ ? 1 : 0);  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        s_[0] = (n_ ? 0 : ns1_);  // sentinel;  returned by last_sort() when n==0
        s_[1] = 0;  // returned by first_sort() when n==0

        first();
    }

    ~partition_asc_sorts()
    {
#ifndef PARTITION_ASC_SORTS_FIXARRAYS
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


private:
    ulong write_s0_tail(ulong j, ulong w, ulong y)
    {
        while ( y <= w )  // can put part Y
        {
//            s_[j] = 0;  // already ==0
            a_[j] = y;
            w -= y;
            j += 1;
        }
        j -= 1;
        a_[j] = y + w;

        return j;
    }

public:

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // The position of the leftmost change is M-1 where
    // M is the value of m before the call to next.
    {
        if ( s_[m_] != ns1_ )  // a[m] is not last sort
        {
            ulong j = m_;

            const ulong s1 = s_[j] + 1;  // next sort
            s_[j] = s1;
            const bool iq = ( s_[j-1] > s1 );  // whether sort inversion

            const ulong y = a_[j-1];
            const ulong z = a_[j];

            ulong w;
            const ulong y1 = y + iq;

            if ( z < 2*y1 )  // just increment sort
            {
//                m_ = j;  // already there
                return  m_;
            }

            if ( z == 2*y1 )  // dup part and sort
            {
                a_[j] = y1;
                j += 1;
                m_ = j;
                s_[j] = s1;
                a_[j] = y1;
                return  m_;
            }


            a_[j] = y1;
            w = z - y1;
            j += 1;

            m_ = write_s0_tail(j, w, y1+1);

            return  m_;
        }
        else  // a[m] is last sort
        {
            if ( m_ <= 1 )  return 0;  // current is last
            ulong j = m_;

            const ulong y = a_[j-1];
            const ulong z = a_[j];
            const ulong y1 = y + 1;
            ulong z1 = z - 1;

            s_[j] = 0;  // always leave first sort at end

            if ( z1 < y1 )  // shrink
            {
                m_ -= 1;
                a_[m_] = y1 + z1;
                return m_;
            }

            if ( z1 == y1 )  // dup part and sort
            {
                const ulong sy = s_[j-1];
                a_[j-1] = y1;
                a_[j] = y1;
                s_[j] = sy;
                return m_;
            }

            a_[j-1] = y1;

            const ulong sy = s_[j-1];
            j = write_s0_tail(j, z1, y1+(sy!=0));

//            for (ulong i=m_; i<=j; ++i)  // repair sorts
//                if ( a_[i]==a_[i-1] )  s_[i] = s_[i-1];

            m_ = j;
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


#endif  // !defined HAVE_PARTITION_ASC_SORTS_H__
