#if !defined HAVE_PARTITION_ODD_ASC_SUBSET_LEX_H__
#define      HAVE_PARTITION_ODD_ASC_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

//#define PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS // default off
// slowdown with GCC 4.9.0

class partition_odd_asc_subset_lex
// Integer partitions into odd parts.
// Representation as list of parts in weakly ascending order.
// Subset-lex order.
// Only the two or three last parts at the end are different from the previous partition.
// Loopless algorithm.
// Cf. OEIS sequence A000009.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts
#ifndef PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[1000]; // > 10^21
#endif

private:  // have pointer data
    partition_odd_asc_subset_lex(const partition_odd_asc_subset_lex&);  // forbidden
    partition_odd_asc_subset_lex & operator = (const partition_odd_asc_subset_lex&);  // forbidden

public:
    explicit partition_odd_asc_subset_lex(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
#endif
        first();
    }

    ~partition_odd_asc_subset_lex()
    {
#ifndef PARTITION_ODD_ASC_SUBSET_LEX_FIXARRAYS
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
            m_ = 1;
            a_[0] = 1;  // use partitions of n=1 for n=0 internally
            a_[1] = 0;  // returned by both first_part() and last_part() with n==0
        }
        else
        {
            a_[0] = 1;  // sentinel: read (once) by test for right-extension

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
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Loopless algorithm.
    {
        ulong y = a_[m_-1];  // may read sentinel a[0]
        ulong z = a_[m_];

        if ( z >= 3*y )  // can extend to the right
        {  // [*, Y, Z] --> [*, Y, Y, Y, Z-2*Y]
            a_[m_] = y;
            a_[m_+1] = y;
            a_[m_+2] = z - 2 * y;
            m_ += 2;
            return  m_;
        }

        if ( m_ >= n_ )  // all-ones partition
        {
            if ( n_ <= 5 )  return 0;  // current is last

            //   [1, ..., 1, 1, 1, 1, 1, 1] -->  [1, ..., 3, 3]
            m_ -= 4;
            a_[m_] = 3;
            a_[m_-1] = 3;
            return m_;
        }

        ulong z2 = z - 2;
        ulong y2 = y + 2;

        if ( z2 >= y2 )  // add 2 units to the left
        {  // [*, Y, Z] --> [*, Y+2, Z-2]
            a_[m_-1] = y2;
            a_[m_] = z2;
            return  m_;
        }

        if ( m_==2 )  // current is last (happens only for n even)
            return 0;

        // here m >= 3;  add to second or third left:

        ulong x2 = a_[m_-2] + 2;
        ulong s = z + y - 2;

        if ( x2 <= z2 )  // add 2 units to third left, repeat part, put rest at end
        {  // [*, X, Y, Z] --> [*, X+2, X+2, Y+Z-2 -X-2]
            a_[m_-2] = x2;
            a_[m_-1] = x2;
            a_[m_] = s - x2;
            return  m_;
        }

        if ( m_==3 )  // current is last (happens only for n odd)
            return 0;

        // add 2 units to third left, combine rest into second left
        // [*, W, X, Y, Z] --> [*, W+2, X+Y+Z-2]
        a_[m_-3] += 2;
        a_[m_-2] += s;
        m_ -= 2;
        return  m_;
    }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // parts odd?
            if ( 0==(a_[j] & 1UL) )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_-(n_==0), dfz); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ODD_ASC_SUBSET_LEX_H__
