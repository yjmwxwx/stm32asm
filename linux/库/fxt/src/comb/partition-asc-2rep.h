#if !defined HAVE_PARTITION_ASC_2REP_H__
#define      HAVE_PARTITION_ASC_2REP_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


//#define PARTITION_ASC_2REP_FIXARRAYS  // default off


class partition_asc_2rep
// Integer partitions where parts have multiplicity at most 2.
// Representation as weakly ascending list of parts.
// Lexicographic order.
// Cf. OEIS sequence A000726.
{
public:
#ifndef PARTITION_ASC_2REP_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions,  fixme: somewhat wasteful
#endif

    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts

private:  // have pointer data
    partition_asc_2rep(const partition_asc_2rep&);  // forbidden
    partition_asc_2rep & operator = (const partition_asc_2rep&);  // forbidden

public:
    explicit partition_asc_2rep(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ASC_2REP_FIXARRAYS
        a_ = new ulong[n_+1];  // fixme: somewhat wasteful
#endif
        first();
    }

    ~partition_asc_2rep()
    {
#ifndef PARTITION_ASC_2REP_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        ulong p = 0;
        ulong s = n_;
        ulong k = 1;
        ulong rq = 1;
        while ( s >= (p += rq) )
        {
            a_[k] = p;
            s -= p;
            rq = 1 - rq;
            k += 1;
        }

        k -= 1;
        a_[k] += s;

        m_ = k;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current partition is the last.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong z = a_[m_];
        ulong y = a_[m_-1];
        ulong x = a_[m_-2];  // can read sentinel

        ulong s = z + y;
        m_ -= 1;
        ulong p = a_[m_] + 1;
        ulong rq = 0;
        while ( s >= (p += rq) )
        {
            a_[m_] = p;
            s -= p;

//            rq = (p==a_[m_-1]);
            rq = (p==x);
            x = p;

            m_ += 1;
        }

        m_ -= 1;
        a_[m_] += s;

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
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=2; j<=m_; ++j)  // multiplicity at most 2 ?
            if ( a_[j] == a_[j-2] )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_2REP_H__
