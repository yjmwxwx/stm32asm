#if !defined HAVE_PARTITION_H__
#define      HAVE_PARTITION_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

class partition
// Integer partitions.
// Order is such that the conjugates are in Abramowitz/Stegun order.
// Representation as array of multiplicities of parts.
// Cf. OEIS sequence A000041.
{
public:
    ulong *c_;  // partition:  c[1]* 1 + c[2]* 2 + ... + c[n]* n == n
    ulong *s_;  // cumulative sums:  s[j+1] = c[1]* 1 + c[2]* 2 + ... + c[j]* j
    ulong n_;   // partitions of n

private:  // have pointer data
    partition(const partition&);  // forbidden
    partition & operator = (const partition&);  // forbidden

public:
    explicit partition(ulong n)
    {
        n_ = n;
        c_ = new ulong[n+1];
        s_ = new ulong[n+1];
        s_[0] = 0;  // unused
        c_[0] = 0;  // unused
        first();
    }

    ~partition()
    {
        delete [] c_;
        delete [] s_;
    }

    void first()
    {
        c_[1] = n_;
        for (ulong i=2; i<=n_; i++)  { c_[i] = 0; }
        if ( n_==0 )  c_[0] = 1;  // make things work for n==0
        s_[1] = 0;
        for (ulong i=2; i<=n_; i++)  { s_[i] = n_; }
    }

    void last()
    {
        for (ulong i=1; i<n_; i++)  { c_[i] = 0; }
        c_[n_] = 1;
        for (ulong i=1; i<=n_; i++)  { s_[i] = 0; }
    }

    const ulong * data()  const  { return c_; }  // one-based!

    bool next()
    {
        // This algorithm was given by Torsten Finke

        if ( c_[n_]!=0 )  return false;  // last == 1* n (c[n]==1)

        // Find first coefficient c[i], i>=2 that can be increased:
        ulong i = 2;
        while ( s_[i]<i )  ++i;

        ++c_[i];
        s_[i] -= i;
        ulong z = s_[i];
        // Now set c[1], c[2], ..., c[i-1] to the first partition
        // of z into i-1 parts, i.e. set to  z, 0, 0, ..., 0:
        while ( --i > 1 )
        {
            s_[i] = z;
            c_[i] = 0;
        }
        c_[1] = z;  // z* 1 == z
        // s_[1] unused

        return true;
    }


    bool prev()
    {
        if ( c_[1]==n_ )  return false;  // first == n* 1 (c[1]==n)

        // Find first nonzero coefficient c[i] where i>=2:
        ulong i = 2;
        while ( c_[i]==0 )  ++i;

        --c_[i];
        s_[i] += i;
        ulong z = s_[i];
        // Now set c[1], c[2], ..., c[i-1] to the last partition
        // of z into i-1 parts:
        while ( --i > 1  )
        {
//            ulong q = z/i;
            ulong q = (z>=i ? z/i : 0);  // == z/i; (optimized)
            c_[i] = q;
            s_[i+1] = z;
            z -= q*i;
        }
        c_[1] = z;
        s_[2] = z;
        // s_[1] unused

        return true;
    }

    ulong num_parts()  const
    // Return the number of parts (length).
    // Example: the partition
    // 6 ==  4* 1 + 1* 2 + 0 + 0 + 0 + 0 == 1 + 1 + 1 + 1 + 2
    // has 5 parts (four 1s and one 2).
    {
        ulong ct = 0;
        for (ulong k=1; k<=n_; ++k)  ct += c_[k];
        return ct;
    }

    ulong num_sorts()  const
    // Return the number of different parts.
    // Example: the partition
    // 6 ==  4* 1 + 1* 2 + 0 + 0 + 0 + 0 == 1 + 1 + 1 + 1 + 2
    // has two sorts (1s and 2).
    // Same as: number of sorts of the conjugate partition.
    {
        ulong ct = 0;
        for (ulong k=1; k<=n_; ++k)  ct += ( c_[k] != 0 );
        return ct;
    }

    bool is_dist_parts()  const
    // Return whether partition is into distinct parts
    // (that is, whether no part is repeated).
    // Same as: num_sorts() == num_parts()
    {
        for (ulong k=1; k<=n_; ++k)
            if ( c_[k] > 1 )  return false;
        return true;
    }

    bool is_into_odd_parts()  const
    // Return whether partition is into odd parts (only).
    {
        for (ulong k=2; k<=n_; k+=2)
            if ( c_[k] != 0 )  return false;
        return true;
    }

    bool is_into_even_parts()  const
    // Return whether partition is into even parts (only).
    {
        for (ulong k=1; k<=n_; k+=2)
            if ( c_[k] != 0 )  return false;
        return true;
    }

    ulong largest_part()  const
    // Return the largest part.
    // Example: the partition
    // 6 ==  4* 1 + 1* 2 + 0 + 0 + 0 + 0 == 1 + 1 + 1 + 1 + 2
    // has largest part 2.
    {
        ulong m = 0;
        for (ulong j=1; j<=n_; ++j)
            if ( c_[j] != 0 )  m = j;
        return m;
    }

    ulong smallest_part()  const
    // Return the smallest part.
    // Example: the partition
    // 6 ==  4* 1 + 1* 2 + 0 + 0 + 0 + 0 == 1 + 1 + 1 + 1 + 2
    // has smallest part 1.
    {
        for (ulong j=1; j<=n_; ++j)
            if ( c_[j] != 0 )  return j;
        return 0;
    }

    long rank()  const
    // Return Dyson's rank.
    {
        return  (long)(largest_part() - num_parts());  // jjcast
    }

    ulong num_of(ulong m)  const
    // Return number of parts m.
    // Example: the partition
    // 6 ==  4* 1 + 1* 2 + 0 + 0 + 0 + 0 == 1 + 1 + 1 + 1 + 2
    // has num_of(1)=4, num_of(2)=1, and num_of(m)=0 for m>=3.
    {
        return  c_[m];
    }

    bool OK()  const
    {
        ulong z = 0;
        for (ulong k=1; k<=n_; ++k)  z += k*c_[k];
        if ( z!=n_ )  return false;

        for (ulong k=0; k<n_; ++k)
            if ( s_[k+1] - s_[k] != k*c_[k] )  return false;

        return  true;
    }

    // comb/partition.cc:
    void print()  const;
    void print_falling()  const;

    void print_long(bool szq)  const;
};
// -------------------------

#endif  // !defined HAVE_PARTITION_H__
