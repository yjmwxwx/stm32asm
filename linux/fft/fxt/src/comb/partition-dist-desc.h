#if !defined HAVE_PARTITION_DIST_DESC_H__
#define      HAVE_PARTITION_DIST_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

//#include "jjassert.h"

//#include <cmath>


class partition_dist_desc
// Partitions into distinct parts as decreasing list of parts.
// Lexicographic order.
// Cf. OEIS sequence A000009.
{
public:
    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts
    ulong n1_;  // number of elements in first partition ( == floor((sqrt(1+8*n)-1)/2) )
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_dist_desc(const partition_dist_desc&);  // forbidden
    partition_dist_desc & operator = (const partition_dist_desc&);  // forbidden

private:
//    ulong first_elem(ulong s)
//    // Return first element in first partition of s
//    {
//        double ds = (double)s;
//        double dp = floor( 0.5 + sqrt(2.0*ds) );  // cf. A002024
//        return (ulong)dp;
//    }

    ulong num_tr_le(ulong s, ulong &tr)
    // Return number of triangular numbers <= s,
    // Set tr to the largest triangular number <= s.
    {
        ulong k = 0,  t = 1;  // t is a triangular number
        while ( s >= t )  { ++k;  t+=(k+1); }
        t -= k+1;
        tr = t;
        return k;
    }

    ulong first_partition(ulong s, ulong j)
    // Write first partition of s into a[j], a[j+1], ...
    // Return index of last element written.
    {
        ulong t;
        ulong p  = num_tr_le(s, t);
        ulong d = s - t;
        // first d parts are  (p+1), (p-1+1), (p-2+1), (p-3+1), ...
        // last (p-d) parts are  ..., 4, 3, 2, 1

//        jjassert( d <= p );

        while ( d != 0 )
        {
            a_[j] = p + 1;
            ++j;
            --d;
            --p;
        }

        while ( p != 0 )
        {
            a_[j] = p;
            ++j;
            --p;
        }

        return  j - 1;
    }

public:
    explicit partition_dist_desc(ulong n)
    {
        n_ = n;
        ulong t;  // dummy
        n1_ = num_tr_le(n_, t);

        a_ = new ulong[n1_+1];
        a_[0] = n_ + 2;  // sentinel, must be > n+1

        first();
    }

    ~partition_dist_desc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

public:
    void first()
    {
        if ( n_ == 0 )  { m_=0;  return; }

        m_ = first_partition(n_, 1);
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong sm = a_[m_];  // sum of parts scanned over
        ulong j = m_ - 1;
        while ( a_[j-1] == a_[j] + 1 )  // can read sentinel a[0]
        {
            sm += a_[j];
            --j;
        }

        ++a_[j];
        --sm;

        if ( sm==0 )
        {
            m_ = j;
            return m_;
        }

        ++j;
        if ( sm <= 2 )
        {
            m_ = j;
            a_[j] = sm;
        }
        else
        {
            m_ = first_partition(sm, j);
        }

        return m_;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    {
        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

        for (ulong j=2; j<=m_; ++j)  // distinct parts ?
            if ( a_[j-1] <= a_[j] )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_DIST_DESC_H__
