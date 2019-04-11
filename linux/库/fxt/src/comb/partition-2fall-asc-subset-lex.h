#if !defined HAVE_PARTITION_2FALL_ASC_SUBSET_LEX_H__
#define      HAVE_PARTITION_2FALL_ASC_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


//#define PARTITION_2FALL_ASC_SUBSET_LEX_FIXARRAYS  // default on
// speedup with GCC 4.9.0


class partition_2fall_asc_subset_lex
// Partitions of n is a partition a[1] + a[2] + ... + a[m] = n
//   such that a[k] >= 2 * a[k-1].
// Representation as weakly ascending list of parts.
// Subset-lex order.
// Loopless algorithm.
// Cf. OEIS sequence A000929.
// Equinumerous to s-partitions (partitions into Mersenne numbers),
//  cf. class partition_s_desc.
{
public:
    ulong n_;   // integer partition of n
    ulong m_;   // current partition has m parts
#ifndef PARTITION_2FALL_ASC_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[62];
#endif

private:  // have pointer data
    partition_2fall_asc_subset_lex(const partition_2fall_asc_subset_lex&);  // forbidden
    partition_2fall_asc_subset_lex & operator = (const partition_2fall_asc_subset_lex&);  // forbidden


private:
    ulong mers_t(ulong s)
    // Return greatest t such that 2^t-1 <= s.
    {
        ulong t = 0;
        ulong b = 1;
        while ( s+1 > b )  { ++t;  b <<= 1; }

        if ( s < b-1 )  { --t;  b >>= 1; }

        return t;
    }

public:
    explicit partition_2fall_asc_subset_lex(ulong n)
    {
        n_ = n;
        ulong k = 1;
        if ( n_ != 0 )  k += mers_t(n_);
#ifndef PARTITION_2FALL_ASC_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[k];
#endif
        first();
    }

    ~partition_2fall_asc_subset_lex()
    {
#ifndef PARTITION_2FALL_ASC_SUBSET_LEX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_ - (n_==0); }

    void first()
    {
        a_[0] = 0;  // read once
        if ( n_ == 0 )
        {
            m_ = 1;
            a_[1] = 1;
            return;
        }

        m_ = 1;
        a_[1] = n_;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Loopless algorithm.
    {
        ulong y = a_[m_-1];  // reads sentinel with m_ <= 1
        ulong y2 = ( m_==1 ? 1 : 2 * y );
        ulong z = a_[m_];
        ulong s = z - y2;
        if ( s >= 2 * y2 )
        {
            a_[m_] = y2;
            ++m_;
            a_[m_] = s;
            return m_;
        }

        y += 1;
        z -= 1;
        a_[m_-1] = y;
        if ( z >= 2 * y )
        {
            a_[m_] = z;
            return m_;
        }
        else
        {
            --m_;
            if ( m_ <= 1 )  return 0;  // current is last

            a_[m_-1] += 1;
            a_[m_] = z + y - 1;
            return m_;
        }
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_aa()  const  // ASCII art
    { print_partition_asc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_asc_conj_aa(data(), m_); }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=2; j<=m_; ++j)  // a[j] >= 2 * a[j-1] ?
            if ( a_[j] < 2 * a_[j-1] )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_2FALL_ASC_SUBSET_LEX_H__
