#if !defined HAVE_PARTITION_BINARY_ASC_H__
#define      HAVE_PARTITION_BINARY_ASC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "fxttypes.h"

//#include "jjassert.h"


class partition_binary_asc
// Binary partitions as weakly ascending list of parts
// (the parts are powers of 2).
// Lexicographic order.
// Cf. OEIS sequences A018819 and A000123.
{
public:
    ulong n_;   // binary integer partitions of n
    ulong m_;   // current partition has m parts
    ulong ml_;  // last m (== Hamming weight of n)
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    partition_binary_asc(const partition_binary_asc&);  // forbidden
    partition_binary_asc & operator = (const partition_binary_asc&);  // forbidden

public:
    explicit partition_binary_asc(ulong n)
    {
        n_ = n;
        ml_ = 0;
        while ( n )  { ml_ += n & 1UL; n>>=1; }
        a_ = new ulong[n_+1];
        first();
    }

    ~partition_binary_asc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        a_[0] = 0;  // sentinel
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ == ml_ )  return 0;  // current is last

        ulong j = m_;
        ulong z = a_[j];
        --j;
        if ( a_[j] == z )  // easy case:   [*, Z, Z] --> [*, 2*Z]
        {
            a_[j] = z + z;
            --m_;
            return  m_;
        }

        ulong sm = z;   // sum of elements scanned over
        while ( a_[j] != a_[j-1] )  // scan over rising part
        {
            sm += a_[j];
            --j;
        }

        --j;
        ulong w = a_[j] << 1;  // part on left of flat step is doubled
        sm += w;
        do  // write tail [*, w, w, w, ..., w]
        {
            a_[j] = w;
            ++j;
            sm -= w;
        }
        while ( sm != 0 );

        m_ = j - 1;
        return m_;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    bool OK()  const
    {
        if ( ! is_partition_asc(data(), num_parts(), n_) )  return false;

        for (ulong j=1; j<=m_; ++j)  // all parts powers of 2 ?
        {
            ulong v = a_[j];
            if ( !!(v&(v-1)) )  return false;
        }

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_BINARY_ASC_H__
