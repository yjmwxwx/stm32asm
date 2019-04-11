#if !defined HAVE_PARTITION_NONSQUASHING_DESC_H__
#define      HAVE_PARTITION_NONSQUASHING_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"
#include "comb/is-nonsquashing.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


class partition_nonsquashing_desc
// Non-squashing partitions as weakly descending list of parts.
// A non-squashing partition of n is a partition a[1] + a[2] + ... + a[m] = n
//   such that a[k] >= sum(j=k+1..m, a[j] ).
// With parameter sd = true generate strongly decreasing partitions:
//   partitions such that a[k] > sum(j=k+1..m, a[j] ).

// Lexicographic order.
// See:
//  N. J. A. Sloane, James A. Sellers: "On Non-Squashing Partitions",
//    arXiv:math/0312418 [math.CO], (22-December-2003).
// Cf. OEIS sequences A018819, A000123 (non-squashing), and A040039 (strongly decreasing).
{
public:
    ulong n_;   // non-squashing integer partition of n
    ulong m_;   // current partition has m parts
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong sd_;  // whether strongly decreasing (otherwise non-squashing)

private:  // have pointer data
    partition_nonsquashing_desc(const partition_nonsquashing_desc&);  // forbidden
    partition_nonsquashing_desc & operator = (const partition_nonsquashing_desc&);  // forbidden

private:
    ulong write_tail(ulong s, ulong j)
    // Write lexicographically first partition of s, starting at index j.
    // Return last index written to.
    // Undefined for s == 0.
    {
        do
        {
            ulong h;
            if ( sd_ )  h = s / 2 + 1;  // strongly decreasing: A040039
            else        h = (s+1) / 2;  // non-squashing: A018819
            a_[j] = h;
            ++j;
            s -= h;
        }
        while ( s );
        return  j - 1;
    }


public:
    explicit partition_nonsquashing_desc(ulong n, bool sd=false)
    {
        sd_ = sd;
        n_ = n;
        ulong k = 0;
        while ( n )  { ++k;  n>>=1; }
        a_ = new ulong[k+1];
        a_[0] = 0;  // unused
        first();
    }

    ~partition_nonsquashing_desc()
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

    void print_aa()  const  // ASCII art
    { print_partition_desc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_desc_conj_aa(data(), m_); }


    bool OK()  const
    {
        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

#if 1
        if ( ! is_nonsquashing( data(), m_ ) )  return false;
        if ( sd_  &&  ! is_strongly_decreasing( data(), m_ ) )  return false;
#else
        ulong w = 0;
        for (ulong j=m_; j!=0; --j)  // non-squashing ?
        {
            ulong v = a_[j];
            if ( w > v )  return false; // non-squashing, cf. A018819
//            if ( w>=v )  return false; // strongly decreasing, cf. A040039
            w += v;
        }
#endif
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_NONSQUASHING_DESC_H__
