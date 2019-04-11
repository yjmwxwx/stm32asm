#if !defined HAVE_PARTITION_S_DESC_H__
#define      HAVE_PARTITION_S_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


class partition_s_desc
// S-partitions: integer partitions into parts 2^n-1.
// Representation as list of parts in weakly descending order.
// Lexicographic order.
// Cf. OEIS sequence A000929.
// Equinumerous to partitions such that 2*a[k] <= a[k-1],
//  cf. class partition_2fall_desc.
{
public:
    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts
    ulong s_;    // position of downstep where we can add 1:
    // == 1 + position of last part != 1
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_s_desc(const partition_s_desc&);  // forbidden
    partition_s_desc & operator = (const partition_s_desc&);  // forbidden

public:
    explicit partition_s_desc(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        first();
    }

    ~partition_s_desc()
    { delete [] a_; }

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
        if ( m_ <= 2 )  return 0;  // current is last

        ulong z = a_[m_-1] + a_[m_];  // sum of parts scanned over
        a_[m_] = 1;
        a_[m_-1] = 1;
        ulong j = m_ - 1;

#if 1 // substantial speedup
        if ( (z == 2) && (s_ < j)  )  // easy case (very frequent)
        {
            a_[s_] += 2;
            ++s_;
            m_ -= 2;
            return  m_;
        }
#endif

        while ( true )  // scan left to next descent
        {
            --j;
            if ( j==0 )  return 0;

            const ulong v = a_[j];
            if ( a_[j-1] != v )  // found downstep
            {
                const ulong i = v + 1;  // increment we need
                if ( z >= i )  // can increment
                {
                    a_[j] = v + i;
                    s_ = j + 1;
                    z -= i;
                    m_ = j + z;
                    // a[j+1], a[j+2], ... are already ==1
                    return m_;
                }
            }

            z += v;
            a_[j] = 1;
        }
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

    void print_aa()  const  // ASCII art
    { print_partition_desc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_desc_conj_aa(data(), m_); }

    bool OK()  const
    {
        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

        if ( n_ != 0 )
        {
            if ( a_[s_] != 1 )  return false;
            if ( a_[s_-1] <= 1 )  return false;
        }

        for (ulong j=1; j<=m_; ++j)
        {
            ulong x = a_[j];
            if ( !!(x & (x+1)) )  return false;
        }

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_S_DESC_H__
