#if !defined HAVE_PARTITION_BINARY_DESC_H__
#define      HAVE_PARTITION_BINARY_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

//#include "jjassert.h"


class partition_binary_desc
// Binary partitions as weakly descending list of parts.
// Lexicographic order.
// Cf. OEIS sequences A018819 and A000123.
{
public:
    ulong n_;   // binary integer partitions of n
    ulong m_;   // current partition has m parts
    ulong s_;   // position of downstep where we can add:
    // == 1 + position of last part != 1
    // s == 1 for the first partition
    ulong ml_;  // last m (== Hamming weight of n)
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_binary_desc(const partition_binary_desc&);  // forbidden
    partition_binary_desc & operator = (const partition_binary_desc&);  // forbidden

public:
    explicit partition_binary_desc(ulong n)
    {
        n_ = n;
        ml_ = 0;
        while ( n )  { ml_ += n & 1UL; n>>=1; }
        a_ = new ulong[n_+1];
        first();
    }

    ~partition_binary_desc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = 0;  // sentinel
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
        s_ = 1;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ == ml_ )  return 0;  // current is last

        if ( s_ < m_ - 1 )  // easy case: at least two trailing ones (very frequent)
        {
            a_[s_] += 1;  // one unit is moved to position s
            ++s_;         // s moves one postion to the right
            --m_;         // one part less
            return  m_;
        }

        // scan to rightmost down-step (can be first position):
        ulong j = m_;
        ulong sm = 0;   // sum of elements(-1) scanned over
        // scan over falling part, terminates because in all
        // but the last partition there is a flat part:
        while ( a_[j] < a_[j-1] )
        {
            sm += a_[j] - 1;
            a_[j] = 1;
            --j;
        }

        // scan to end of flat part:
        while ( a_[j] == a_[j-1] )  // may read sentinel a[0]
        {
            sm += a_[j] - 1;
            a_[j] = 1;
            --j;
        }

        ulong z = a_[j];
        a_[j] += z;  // part is doubled
        s_ = j + 1;  // all parts past increased part are 1
        m_ += sm - z;

        return m_;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    {
        if ( ! is_partition_desc(data(), num_parts(), n_) )  return false;

        if ( n_ != 0 )
        {
            if ( m_ != n_ )  // unless first partition
            {
                if ( a_[s_] != 1 )  return false;
                if ( a_[s_-1] <= 1 )  return false;
            }
        }

        for (ulong j=1; j<=m_; ++j)  // powers of 2 ?
        {
            ulong v = a_[j];
            if ( !!(v&(v-1)) )  return false;
        }

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_BINARY_DESC_H__
