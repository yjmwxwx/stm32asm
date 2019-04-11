#if !defined HAVE_PARTITION_DIST_ASC_SUBSET_LEX_H__
#define      HAVE_PARTITION_DIST_ASC_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/is-partition-asc.h"

#include "fxttypes.h"

//#include <cmath>


class partition_dist_asc_subset_lex
// Integer partitions into distinct parts.
// Representation as list of parts in increasing order.
// Subset-lex order.
// The length of consecutive partitions changes by at most one.
// Only the last two positions in a partition at the end change.
// Loopless algorithm.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // integer partitions of n
    ulong m_;   // current partition has m parts

private:  // have pointer data
    partition_dist_asc_subset_lex(const partition_dist_asc_subset_lex&);  // forbidden
    partition_dist_asc_subset_lex & operator = (const partition_dist_asc_subset_lex&);  // forbidden

public:
    explicit partition_dist_asc_subset_lex(ulong n)
    {
        n_ = n;

        // We need floor((sqrt(1+8*n)-1)/2) elements:
        ulong k = 1,  s = n_;
        while ( s >= ( k + (k+1) ) )  { s -= k;  k += 1; }
        a_ = new ulong[k+1];
        a_[0] = 0;  // sentinel: read (once) by test for right-extension

        first();
    }

    ~partition_dist_asc_subset_lex()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }

    void first()
    {
        if ( n_ == 0 )  { m_=0;  return; }
        a_[1] = n_;
        m_ = 1;
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Loopless algorithm.
    {
        ulong y = a_[m_-1];  // may read sentinel a[0]
        ulong z = a_[m_];

        if ( z >= 2*y + 3 )  // can extend to the right
        {  // [*, Y, Z] --> [*, Y, Y+1, Z-1]
            y += 1;
            a_[m_] = y;
            a_[m_+1] = z - y;  // >= y
            ++m_;
            return  m_;
        }
        else  // add to the left
        {
            z -= 1;  y += 1;

            if ( z > y )  // add one unit to the left
            {  // [*, Y, Z] --> [*, Y+1, Z-1]

                if ( m_<=1 )  return 0;  // current is last

                a_[m_-1] = y;
                a_[m_] = z;
                return  m_;
            }
            else  // add to one unit second left and combine last with second last
            {  // [*, X, Y, Z] --> [*, X+1, Y+Z]

                if ( m_<=2 )  return 0;  // current is last

                a_[m_-2] += 1;
                a_[m_-1] += z;
                --m_;
                return  m_;
            }
        }
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


#endif  // !defined HAVE_PARTITION_DIST_ASC_SUBSET_LEX_H__
