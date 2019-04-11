#if !defined HAVE_PARTITION_ODD_NONSQUASHING_DESC_H__
#define      HAVE_PARTITION_ODD_NONSQUASHING_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "comb/is-nonsquashing.h"

#include "fxttypes.h"


class partition_odd_nonsquashing_desc
// Non-squashing partitions into odd parts as weakly descending list of parts.
// A non-squashing partition of n is a partition a[1] + a[2] + ... + a[m] = n
//   such that a[k] >= sum(j=k+1..m, a[j] ).
// Lexicographic order.
// Cf. OEIS sequence A187821.
{
public:
    ulong n_;   // non-squashing integer partition of n
    ulong m_;   // current partition has m parts
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_odd_nonsquashing_desc(const partition_odd_nonsquashing_desc&);  // forbidden
    partition_odd_nonsquashing_desc & operator = (const partition_odd_nonsquashing_desc&);  // forbidden

private:
    ulong write_tail(ulong s, ulong j)
    // Write lexicographically first partition of s, starting at index j.
    // Return last index written to.
    // Undefined for s == 0.
    {
        do
        {
            ulong h = ((s+1) / 4) * 2 + 1 ;  // non-squashing, odd parts
//            ulong h = ??;  // strongly decreasing, odd parts; need to edit next() as well (?)
//            ulong h = (s+1) / 2;  // non-squashing (all parts)
//            ulong h = s / 2 + 1;  // strongly decreasing (all parts)
            a_[j] = h;
            ++j;
            s -= h;
        }
        while ( s );
        return  j - 1;
    }


public:
    explicit partition_odd_nonsquashing_desc(ulong n)
    {
        n_ = n;
        ulong k = 0;
        while ( n )  { ++k;  n>>=1; }
        a_ = new ulong[k+1];  // slightly wasteful
        a_[0] = 0;  // unused
        first();
    }

    ~partition_odd_nonsquashing_desc()
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

        ulong j = m_;
        ulong z = a_[j];
        if ( z==1 )
        {
            --j;
            z += a_[j];
//            if ( j==0 )  return 0;
        }

        if ( z==2 )  // easy case
        {
            --j;
            a_[j] += 2;
            m_ = j;
            return m_;
        }

        if ( j==1 )  return 0;

        a_[j-1] += 2;
        m_ = write_tail(z-2, j);
        return m_;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    {
        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

#if 1
        if ( ! is_nonsquashing( data(), m_ ) )  return false;
#else
        ulong w = 0;
        for (ulong j=m_; j!=0; --j)  // non-squashing ?
        {
            ulong v = a_[j];
            if ( w > v )  return false; // non-squashing
//            if ( w>=v )  return false; // strongly decreasing
            w += v;
        }
#endif

        for (ulong j=1; j<=m_; ++ j)  // odd parts ?
            if ( 0==(a_[j] & 1) )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ODD_NONSQUASHING_DESC_H__
