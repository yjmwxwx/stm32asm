#if !defined HAVE_PARTITION_ASC_SUBSET_LEX_CSH_H__
#define      HAVE_PARTITION_ASC_SUBSET_LEX_CSH_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


//#define PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS  // default off
// small speedup

class partition_asc_subset_lex_csh
// Partitions of n into positive parts as ascending list of parts.
// Cyclically shifted subset-lex order:
// The length of consecutive partitions changes by at most one.
// Only two adjacent positions in a partition at the end change,
//   with the single exception that one only position changes with
//   the partition into one part.
// Loopless algorithm.
{
public:
#ifndef PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions
#endif
    ulong n_;   // partition of n
    ulong m_;   // current partition has m parts

private:  // have pointer data
    partition_asc_subset_lex_csh(const partition_asc_subset_lex_csh&);  // forbidden
    partition_asc_subset_lex_csh & operator = (const partition_asc_subset_lex_csh&);  // forbidden

public:
    explicit partition_asc_subset_lex_csh(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        // sentinel a[0] set in first()
#endif
        first();
    }

    ~partition_asc_subset_lex_csh()
    {
#ifndef PARTITION_ASC_SUBSET_LEX_CSH_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }
    ulong first_part()  const  { return a_[1]; }  // returns 0 for n==0
    ulong last_part()  const  { return a_[m_]; }  // returns 0 for n==0

    void first()
    {
        if ( n_ == 0 )
        {
            a_[0] = 0;  // returned by last_part() when n==0
            a_[1] = 0;  // returned by first_part() when n==0
            m_ = 0;
        }
        else
        {
            a_[0] = 1;  // sentinel: read (once) by test for right-extension

            if ( n_ <= 3 )
            {
                a_[1] = n_;
                m_ = 1;
            }
            else
            {
                m_ = n_ - 2;
                for (ulong j=1; j<m_; ++j)  a_[j] = 1;
                a_[m_-1] = 2;
                a_[m_] = 2;
            }
        }
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Loopless algorithm.
    {
        if ( m_ == n_ )  return 0;  // all-ones partition is last

        ulong y = a_[m_-1];  // may read sentinel a[0]
        ulong z = a_[m_];

        if ( z >= 2*y )  // extend to the right:
        {  //   [*, Y, Z] --> [*, Y, Y, Z-Y]
            a_[m_] = y;
            a_[m_+1] = z - y;  // >= y
            ++m_;
            return  m_;
        }

        --z;
        ++y;
        if ( z >= y )  // add one unit to the left:
        {  //   [*, Y, Z] --> [*, Y+1, Z-1]
            a_[m_-1] = y;
            a_[m_] = z;
            return  m_;
        }

        if ( m_ != 2 )  // add one unit to second left, add rest to end
        {  //   [*, X, Y, Z] --> [*, X+1, Y+Z-1]
            a_[m_-2] += 1;
            a_[m_-1] += z;
            --m_;
            return  m_;
        }

        // create partition into one part (happens just once)
        //   [Y, Z] --> [Y+Z]
        ulong s = y + z;
        a_[1] = s;
        m_ = 1;
        return  m_;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_partition_asc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_asc_conj_aa(data(), m_); }

    bool OK()  const
    { return is_partition_asc(data(), num_parts(), n_); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_SUBSET_LEX_CSH_H__
