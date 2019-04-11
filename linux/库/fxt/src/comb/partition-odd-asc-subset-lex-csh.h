#if !defined HAVE_PARTITION_ODD_ASC_SUBSET_LEX_CSH_H__
#define      HAVE_PARTITION_ODD_ASC_SUBSET_LEX_CSH_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

//#define PARTITION_ODD_ASC_SUBSET_LEX_CSH_FIXARRAYS // default off
// speedup

class partition_odd_asc_subset_lex_csh
// Integer partitions into odd parts.
// Representation as list of parts in weakly ascending order.
// Cyclically shifted subset-lex order:
// The length of consecutive partitions changes by at most two.
// Only two or three adjacent positions in a partition at the end change,
//   with the single exception that one only position changes with
//   the partition into one part when n is odd.
// Loopless algorithm.
{
public:
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts
#ifndef PARTITION_ODD_ASC_SUBSET_LEX_CSH_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[1000]; // > 10^21
#endif

private:  // have pointer data
    partition_odd_asc_subset_lex_csh(const partition_odd_asc_subset_lex_csh&);  // forbidden
    partition_odd_asc_subset_lex_csh & operator = (const partition_odd_asc_subset_lex_csh&);  // forbidden

public:
    explicit partition_odd_asc_subset_lex_csh(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ODD_ASC_SUBSET_LEX_CSH_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
#endif
        a_[0] = 0;  // sentinel: read (once) by test for right-extension
        a_[1] = 0;  // returned by first_part() with n==0

        first();
    }

    ~partition_odd_asc_subset_lex_csh()
    {
#ifndef PARTITION_ODD_ASC_SUBSET_LEX_CSH_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }

    ulong first_part()  const  {  return a_[1]; }
    ulong last_part()  const  {  return a_[m_]; }

    void first()
    {
        if ( n_ == 0 )
        {
            a_[0] = 0;  // returned by last_part() when n==0
            m_ = 0;
        }
        else
        {
            a_[0] = 1;  // sentinel: read (once) by test for right-extension

            if ( n_ <= 5 )
            {
                if ( n_ & 1UL )  // n odd
                {
                    a_[1] = n_;
                    m_ = 1;
                }
                else
                {
                    a_[1] = 1;
                    a_[2] = n_ - 1;
                    m_ = 2;
                }
            }
            else  // [1, 1, 1, ..., 1, 1, 3, 3]
            {
                m_ = n_ - 4;
                for (ulong j=1; j<m_; ++j)  a_[j] = 1;
                a_[m_-1] = 3;
                a_[m_] = 3;
            }
        }
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Loopless algorithm.
    {
        if ( m_ == n_ )  return 0;  // current is last

        ulong y = a_[m_-1];  // may read sentinel a[0]
        ulong z = a_[m_];

        ulong r = z - 2*y;
        if ( z >= 3*y )  // can extend to the right
        {  // [*, Y, Z] --> [*, Y, Y, Y, Z-2*Y]
            a_[m_] = y;
            a_[m_+1] = y;
            a_[m_+2] = r;
            m_ += 2;
            return  m_;
        }
        else  // add to the left
        {
            ulong z2 = z - 2;
            ulong y2 = y + 2;

            if ( z2 >= y2 )  // add 2 units to the left
            {  // [*, Y, Z] --> [*, Y+2, Z-2]
                a_[m_-1] = y2;
                a_[m_] = z2;
                return  m_;
            }
            else  // add to second or third left
            {
                if ( m_==2 )  // next is [1, n-1] (happens only for n even)
                {   // [Y, Z] == [n/2-1, n/2+1] --> [1, n-1]
                    a_[1] = 1;
                    a_[2] = n_ - 1;
                    m_ = 2;
                    return m_;
                }
                // here m >= 3

                ulong x2 = a_[m_-2] + 2;
                ulong s = z + y - 2;

                if ( x2 <= z2 )  // add 2 units to third left, repeat part, put rest at end
                {  // [*, X, Y, Z] --> [*, X+2, X+2, Y+Z-2 -X-2]
                    a_[m_-2] = x2;
                    a_[m_-1] = x2;
                    a_[m_] = s - x2;
                    return  m_;
                }
                else  // add 2 units to third left, combine rest into second left
                {
                    if ( m_==3 )  // next is [n] (happens only for n odd)
                    {  // [X, Y, Z] --> [X+Y+Z]
                        a_[1] = n_;
                        m_ = 1;
                        return  m_;
                    }

                    // [*, W, X, Y, Z] --> [*, W+2, X+Y+Z-2]
                    a_[m_-3] += 2;
                    a_[m_-2] += s;
                    m_ -= 2;
                    return  m_;
                }
            }
        }
    }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // parts odd?
            if ( 0==(a_[j] & 1UL) )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ODD_ASC_SUBSET_LEX_CSH_H__
