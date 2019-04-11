#if !defined HAVE_PARTITION_ODD_DESC_H__
#define      HAVE_PARTITION_ODD_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "fxttypes.h"


class partition_odd_desc
// Integer partitions into odd parts.
// Representation as list of parts in weakly descending order.
// Lexicographic order.
// Cf. OEIS sequence A000009.
{
public:
    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts
    ulong s_;  // position of downstep where we can add 2:
    // == 1 + position of last part != 1
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_odd_desc(const partition_odd_desc&);  // forbidden
    partition_odd_desc & operator = (const partition_odd_desc&);  // forbidden

public:
    explicit partition_odd_desc(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+2];
        a_[0] = 0;  // sentinel solely for n==0
        ++a_;  // nota bene
        first();
    }

    ~partition_odd_desc()
    {
        --a_;
        delete [] a_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = n_ + 1;  // sentinel
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
        s_ = 1;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        ulong z = a_[m_];
        a_[m_] = 1;

        ulong j = m_ - 1;
        if ( z==1 )  // need one more part
        {
            if ( m_<=2 )  return 0;

            const ulong y = a_[m_-1];
            z += y;
            a_[m_-1] = 1;
            --j;
        }

        if ( m_ <= 1 )  return 0;  // current is last

#if 1  // great speedup
        if ( s_ < j )
        {
            a_[s_] += 2;
            z -= 2;
            s_ += 1;
            m_ += z - 2;
            return m_;
        }
#endif

        const ulong a1 = a_[j];
        ulong s = j;
        while ( a_[s-1] == a1 )  // scan left to next descent
        {
            z += a_[s];
            a_[s] = 1;
            --s;
        }
        a_[s] += 2;
        s_ = s + 1;
        m_ = s + z - 2;

        return m_;
    }

    ulong durfee_n()  const
    // Return side length of the Durfee square.
    {
        ulong d = 0;
        for (ulong j=1; j<=m_; ++j)
            if ( a_[j] >= j )  ++d;
            else  break;
        return d;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    {
        if ( n_ != 0 )
        {
            if ( a_[s_] != 1 )  return false;
            if ( a_[s_-1] <= 1 )  return false;
        }

        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

        for (ulong j=1; j<=m_; ++j)  // odd parts?
            if ( 0==(a_[j] & 1UL) )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ODD_DESC_H__
