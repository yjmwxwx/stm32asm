#if !defined HAVE_PARTITION_DIST_ASC_LEN_H__
#define      HAVE_PARTITION_DIST_ASC_LEN_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"

#include "fxttypes.h"

//#include <cmath>


class partition_dist_asc_len
// Integer partitions into distinct parts.
// Representation as list of parts in increasing order.
// Major order by number of parts, minor order lexicographic.
// Cf. OEIS sequence A000009.
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts
    ulong mm_;   // max number of parts

private:  // have pointer data
    partition_dist_asc_len(const partition_dist_asc_len&);  // forbidden
    partition_dist_asc_len & operator = (const partition_dist_asc_len&);  // forbidden

public:
    explicit partition_dist_asc_len(ulong n)
    {
        n_ = n;

        // We need floor((sqrt(1+8*n)-1)/2) elements:
        ulong k = 1,  s = n_;
        while ( s >= ( k + (k+1) ) )  { s -= k;  k += 1; }
        a_ = new ulong[k+1];

        mm_ = k;

        first();
    }

    ~partition_dist_asc_len()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }
    ulong max_num_parts()  const  {  return mm_; }

    bool first(ulong m=1)
    {
        a_[0] = 0;  // unused

        m_ = 0;
        if ( n_ == 0 )  { return true; }

        if ( mm_ < m )  return false;

        ulong k = 1;
        ulong s = n_;
        // split s into 1, 2, 3, 4, ..., k, z  where z >= k+1:
        while ( k < m )
        {
            a_[k] = k;
            s -= k;
            k += 1;
        }

        a_[k] = s;
        m_ = k;

        return true;
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ > 1 )
        {
#if 1 // speedup
            if ( a_[m_] - a_[m_-1] > 2 )  // easy case
            {
                a_[m_] -= 1;
                a_[m_-1] += 1;

                return m_;
            }
#endif

            ulong j = m_;
            ulong d = 0;  // sum of differences
            ulong s = 0;  // sum of parts (from right)
            ulong k = 1;  // min sum of differences for update
            do
            {
                k += 1;
                ulong z = a_[j];
                d += (z - a_[j-1]);
                s += z;

                if ( d > k )
                {
                    ulong p = a_[j-1] + 1;
                    a_[j-1] = p;  // part to add
                    s -= 1;

                    // make tail lex-min:
                    while ( j < m_ )
                    {
                        p += 1;
                        a_[j] = p;
                        s -= p;
                        ++j;
                    }
                    a_[j] = s;

                    return m_;
                }
            }
            while ( --j > 1 );

        }

        return ( first(m_ + 1) ? m_ : 0 );
    }


    bool OK()  const
    {
        if ( m_ > mm_ )  return false;

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


#endif  // !defined HAVE_PARTITION_DIST_ASC_LEN_H__
