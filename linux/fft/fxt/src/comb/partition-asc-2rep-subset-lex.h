#if !defined HAVE_PARTITION_ASC_2REP_SUBSET_LEX_H__
#define      HAVE_PARTITION_ASC_2REP_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


//#define PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS  // default off
// speedup with gcc 4.5.0
// small speedup with gcc 4.8.0

class partition_asc_2rep_subset_lex
// Integer partitions where parts have multiplicity at most 2.
// Representation as weakly ascending list of parts.
// Subset-lex order.
// Loopless algorithm.
// Cf. OEIS sequence A000726.
{
public:
#ifndef PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions,  fixme: somewhat wasteful
#endif

    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts

private:  // have pointer data
    partition_asc_2rep_subset_lex(const partition_asc_2rep_subset_lex&);  // forbidden
    partition_asc_2rep_subset_lex & operator = (const partition_asc_2rep_subset_lex&);  // forbidden

public:
    explicit partition_asc_2rep_subset_lex(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[n_+1];  // fixme: somewhat wasteful
#endif
        first();
    }

    ~partition_asc_2rep_subset_lex()
    {
#ifndef PARTITION_ASC_2REP_SUBSET_LEX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        if ( n_ <= 1 )
        {
            a_[n_] = n_;
            m_ = n_;
        }
        else
        {
            a_[1] = 1;
            a_[2] = n_ - 1;
            m_ = 2;
        }
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current partition is the last.
    // Loopless algorithm.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong z = a_[m_];
        const ulong y = a_[m_-1];
        const ulong x = a_[m_-2];  // can read sentinel

        const ulong rq = (x==y);
        const ulong yt = y + rq;
        const ulong zt = z - yt;

        if ( zt > y )  // can extend to the right
        {
            // [*, X, Y, Z] --> [*, X, Y, Y', Z'] where
            // Y' = Y + rq,  Z' = Z - Y', and rq = (X==Y)
            // note that Y' + Z' = Z
            a_[m_] = yt;
            m_ += 1;
            a_[m_] = zt;
            return  m_;
        }

        const ulong z1 = z - 1;
        const ulong y1 = y + 1;
        if ( z1 >= y1 )  // one unit moves one position to the left
        { //   [*, Y, Z] --> [*, Y+1, Z-1]
            a_[m_-1] = y1;
            a_[m_] = z1;
            return  m_;
        }

        if ( x != 0 )  // one unit moves two positions, rest by one position
        { //   [*, X, Y, Z] --> [*, X+1, Y+Z-1]
            a_[m_-2] = x + 1;
            a_[m_-1] = y + z1;
            m_ -= 1;
            return  m_;
        }
        else  // next is partition into one part (happens just once)
        { //   [Y, Z] --> [Y+Z]
            a_[1] = y1 + z1;
            m_ = 1;
            return m_;
        }
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
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=2; j<=m_; ++j)  // multiplicity at most 2 ?
            if ( a_[j] == a_[j-2] )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_2REP_SUBSET_LEX_H__
