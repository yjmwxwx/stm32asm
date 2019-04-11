#if !defined HAVE_PARTITION_ASC_H__
#define      HAVE_PARTITION_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


//#define PARTITION_ASC_FIXARRAYS  // default off
// small speedup with gcc 4.5.0, slowdown with gcc 4.8.0


class partition_asc
// Integer partitions.
// Representation as list of parts in weakly ascending order.
// Lexicographic order.
// Cf. OEIS sequence A000041.
{
public:
#ifndef PARTITION_ASC_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions
#endif

    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts

private:  // have pointer data
    partition_asc(const partition_asc&);  // forbidden
    partition_asc & operator = (const partition_asc&);  // forbidden

public:
    explicit partition_asc(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ASC_FIXARRAYS
        a_ = new ulong[n_+1 +(n==0)];
#endif
        a_[0] = 0;  // unused
        a_[1] = 0;  // last part for n==0
        first();
    }

    ~partition_asc()
    {
#ifndef PARTITION_ASC_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }

    void last()
    {
        if ( n_ != 0 )  a_[1] = n_;
        m_ = (n_ ? 1 : 0);
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current partition is the last.
    {
        // Based on
        //   Jerome Kelleher, Barry O'Sullivan:
        //   Generating All Partitions: A Comparison Of Two Encodings,
        //   arXiv:0909.2331v1 [cs.DS], (12-September-2009).

        if ( m_ <= 1 )  return 0;  // current is last

        // if Z-1 < Y+1, then  [*, Y, Z] --> [*, Y+Z], otherwise
        // [*, Y, Z] --> [*, Y+1, Y+1, ..., Y+1, W]
        // with at least one occurrence of Y+1, and Y+1 <= W < 2*(Y+1)

        ulong z1 = a_[m_] - 1;  // take one unit from last part
        m_ -= 1;
        const ulong y1 = a_[m_] + 1;  // add one unit to previous part

        while ( y1 <= z1 )  // can put part Y+1
        {
            a_[m_] = y1;
            z1 -= y1;
            m_ += 1;
        }
        a_[m_] = y1 + z1;  // add remaining units to last part

        return  m_;
    }

    ulong prev()
    // Return number of parts of generated partition.
    // Return zero if the current partition is the first.
    {
        if ( m_ == n_ )   return 0;  // current is first

        ulong z = a_[m_];
        ulong y = a_[m_-1];
        if ( z >= 2*y )  // can split off half of z
        {
            ulong t = z / 2;
            a_[m_] = t;
            a_[m_+1] = z - t;
            m_ += 1;
            return m_;
        }

        ulong x = a_[m_-2];
        y -= 1;
        z += 1;
        if ( y >= x )
        {
            if ( z >= y )  // can move one unit right
            {
                a_[m_-1] = y;
                a_[m_] = z;
                return m_;
            }
        }

        // scan for upstep:
        m_ -= 1;
        z += y;
        ulong w;
        while ( (w = a_[m_-1]) == x )
        {
            z += x;  // accumulate tail
            x = w;
            m_ -= 1;
        }

        a_[m_] = x - 1;
        a_[m_+1] = z - x + 1;
        m_ += 1;

        return  m_;
    }

    ulong durfee_n()  const
    // Return side length of the Durfee square.
    {
        ulong d = 0;
        for (ulong j=m_, s=1;  j>=1;  --j, ++s)
        {
            if ( a_[j] >= s )  ++d;
            else  break;
        }
        return d;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_aa()  const  // ASCII art
    { print_partition_asc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_asc_conj_aa(data(), m_); }

    bool OK()  const
    { return is_partition_asc(data(), num_parts(), n_); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_H__
