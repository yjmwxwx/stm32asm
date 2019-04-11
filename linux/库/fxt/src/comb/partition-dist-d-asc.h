#if !defined HAVE_PARTITION_DIST_D_ASC_H__
#define      HAVE_PARTITION_DIST_D_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

class partition_dist_d_asc
// Integer partitions such that parts differ by at least d.
// Representation as list of parts in increasing order.
// Lexicographic order.
// Cf. OEIS sequences
//  A000041 (all partitions; d=0), A000009 (distinct parts; d=1),
//  A003114 (d=2), A025157 (d=3), A025158 (d=4), A025159 (d=5),
//  A025160 (d=6), A025161 (d=7), and A025162 (d=8).
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts
    ulong d_;   // minimal difference of parts

private:  // have pointer data
    partition_dist_d_asc(const partition_dist_d_asc&);  // forbidden
    partition_dist_d_asc & operator = (const partition_dist_d_asc&);  // forbidden

public:
    explicit partition_dist_d_asc(ulong n, ulong d)
    {
        n_ = n;
        d_ = d;

        // Compute how many elements we need:
        ulong k = 1,  s = n_, j = 1;
        while ( s >= ( k + (k+d_) ) )  { s -= k;  k += d_; j += 1; }
        a_ = new ulong[j+1];

        first();
    }

    ~partition_dist_d_asc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        if ( n_ == 0 )  { m_=0;  return; }

        ulong k = 1;
        ulong j = 1;
        ulong s = n_;
        // split s into 1, 1+d, 1+2*d, 1+3*d, ..., y, z  where z >= y + d
        while ( s >= ( k + (k+d_) ) )
        {
            a_[j] = k;
            j += 1;
            s -= k;
            k += d_;
        }

        a_[j] = s;
        m_ = j;
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong s = a_[m_] + a_[m_-1];
        ulong k = a_[m_-1] + 1;
        m_ -= 1;
        // split s into k, k+d, k+2*d, k+3*d, ..., y, z  where z >= y + d
        while ( s >= ( k + (k+d_) ) )
        {
            a_[m_] = k;
            s -= k;
            k += d_;
            m_ += 1;
        }

        a_[m_] = s;

        return  m_;
    }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<m_; ++j)  // min difference d?
            if ( a_[j+1] - a_[j] < d_ )
                return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_DIST_D_ASC_H__
