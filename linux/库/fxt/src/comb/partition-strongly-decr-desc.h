#if !defined HAVE_PARTITION_STRONGLY_DECR_DESC_H__
#define      HAVE_PARTITION_STRONGLY_DECR_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "comb/is-nonsquashing.h"

#include "fxttypes.h"


class partition_strongly_decr_desc
// Strongly decreasing partitions as list of parts.
// A strongly decreasing partition of n is a partition
//   a[1] + a[2] + ... + a[m] = n  such that a[k] > sum(j=k+1..m, a[j] ).
// Lexicographic order.
// Cf. OEIS sequences A040039 and A033485.
{
public:
    ulong n_;   // strongly decreasing integer partition of n
    ulong m_;   // current partition has m parts
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_strongly_decr_desc(const partition_strongly_decr_desc&);  // forbidden
    partition_strongly_decr_desc & operator = (const partition_strongly_decr_desc&);  // forbidden

private:
    ulong write_tail(ulong s, ulong j)
    // Write lexicographically first partition of s, starting at index j.
    // Return last index written to.
    // Undefined for s == 0.
    {
        do
        {
//            ulong h = (s+1) / 2;  // non-squashing
            ulong h = s / 2 + 1;  // strongly decreasing
            a_[j] = h;
            ++j;
            s -= h;
        }
        while ( s );
        return  j - 1;
    }


public:
    explicit partition_strongly_decr_desc(ulong n)
    {
        n_ = n;
        ulong k = 0;
        while ( n )  { ++k;  n>>=1; }
        a_ = new ulong[k+1];
        a_[0] = 0;  // unused
        first();
    }

    ~partition_strongly_decr_desc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        m_ = 0;
        if ( n_!=0 )  m_ = write_tail(n_, 1);
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong z = a_[m_];
        if ( z==1 )  // easy case
        {
            ++a_[m_-1];
            --m_;
            return m_;
        }

        ++a_[m_-1];
        m_ = write_tail(z-1, m_);
        return m_;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    {
        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

#if 1
        if ( ! is_strongly_decreasing( data(), m_ ) )  return false;
#else
        ulong w = 0;
        for (ulong j=m_; j!=0; --j)  // strongly decreasing ?
        {
            ulong v = a_[j];
//            if ( w > v )  return false; // non-squashing, cf. A018819
            if ( w>=v )  return false; // strongly decreasing, cf. A040039
            w += v;
        }
#endif

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_STRONGLY_DECR_DESC_H__
