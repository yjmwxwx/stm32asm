#if !defined HAVE_PARTITION_DIST_ASC_H__
#define      HAVE_PARTITION_DIST_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

//#include <cmath>


class partition_dist_asc
// Integer partitions into distinct parts.
// Representation as list of parts in increasing order.
// Lexicographic order.
// Cf. OEIS sequence A000009.
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts

private:  // have pointer data
    partition_dist_asc(const partition_dist_asc&);  // forbidden
    partition_dist_asc & operator = (const partition_dist_asc&);  // forbidden

public:
    explicit partition_dist_asc(ulong n)
    {
        n_ = n;

        // We need floor((sqrt(1+8*n)-1)/2) elements:
        ulong k = 1,  s = n_;
        while ( s >= ( k + (k+1) ) )  { s -= k;  k += 1; }
        a_ = new ulong[k+1];

        first();
    }

    ~partition_dist_asc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        a_[0] = 0;  // unused
        if ( n_ == 0 )  { m_=0;  return; }

        ulong k = 1;
        ulong s = n_;
        // split s into 1, 2, 3, 4, ..., k, z  where z >= k+1:
        while ( s >= ( k + (k+1) ) )
        {
            a_[k] = k;
            s -= k;
            k += 1;
        }

        a_[k] = s;
        m_ = k;
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong s = a_[m_] + a_[m_-1];
        ulong k = a_[m_-1] + 1;
        m_ -= 1;
        // split s into k, k+1, k+2, ..., y, z  where z >= y + 1:
        while ( s >= ( k + (k+1) ) )
        {
            a_[m_] = k;
            s -= k;
            k += 1;
            m_ += 1;
        }

        a_[m_] = s;

        return  m_;
    }


    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<m_; ++j)  // parts distinct?
            if ( a_[j] == a_[j+1] )
                return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_DIST_ASC_H__
