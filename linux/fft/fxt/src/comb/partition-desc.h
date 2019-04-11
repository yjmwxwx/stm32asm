#if !defined HAVE_PARTITION_DESC_H__
#define      HAVE_PARTITION_DESC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"

//#define PARTITION_DESC_FIXARRAYS  // default off


class partition_desc
// Integer partitions.
// Representation as list of parts in weakly descending order.
// Lexicographic order.
// Cf. OEIS sequence A000041.
{
public:
    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts
    ulong s_;  // position of downstep where we can add 1:
    // == position of first part == 1, or past end
#ifndef PARTITION_DESC_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions
#endif

private:  // have pointer data
    partition_desc(const partition_desc&);  // forbidden
    partition_desc & operator = (const partition_desc&);  // forbidden

public:
    explicit partition_desc(ulong n)
    {
        n_ = n;
#ifndef PARTITION_DESC_FIXARRAYS
        a_ = new ulong[n_+1 +(n==0)];
#endif
        a_[0] = n_ + 1;  // sentinel
        a_[1] = 0;  // first_part() for n==0

        first();
    }

    ~partition_desc()
    {
#ifndef PARTITION_DESC_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }
    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }


    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
        s_ = 1;
    }


    void last()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        if ( n_ != 0 )  a_[1] = n_;
        m_ = ( n_!=0 ? 1 : 0 );
        s_ = ( n_>1 ? 2 : 1 );
    }


    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong y = a_[m_-1];
#if 1 // massive speedup
        if ( y == 1 )  // easy case (very frequent)
        {
            a_[s_] += 1;
            ++s_;
            --m_;
            return  m_;
        }
#endif

#if 1  // slight speedup
        if ( s_ < m_ )
        {
            a_[s_] += 1;
            ++s_;
            m_ += y - 2;
            return m_;
        }
#endif

        ulong z = a_[m_];
#if 1  // slight speedup
        if ( m_ == 2 )
        {
            ++a_[1];
            a_[2] = 1;
            s_ = 2;
            m_ += z - 2;
            return m_;
        }
#endif

        a_[m_] = 1;
        ulong s = m_ - 1;

        while ( a_[s-1] == y )  // scan left to next descent
        {
            z += a_[s];
            a_[s] = 1;
            --s;
        }
        ++a_[s];
        s_ = s + 1;
        m_ = s + z - 1;

        return m_;
    }


    ulong prev()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ >= n_ )  return 0;  // current is last

        ulong z1 = a_[m_] - 1;
        if ( z1 != 0 )  // move one unit right
        {
            a_[m_] = z1;
//            a_[m_+1] = 1;  // already ==1
            m_ += 1;
            s_ = m_ - ( z1 == 1 );
            return m_;
        }

        // here z==1

        ulong t = a_[s_-1];
        if ( t == 2 )  // move one unit to end
        {
            a_[s_-1] = 1;
            s_ -= 1;
            m_ += 1;
//            a_[m_] = 1;  // already ==1
            return m_;
        }


        // decrement a_[s_-1] and spread out the rest:

        ulong j = s_ - 1;

        ulong p = a_[j] - 1;
        a_[j] = p;
        ulong w = m_ - j + 1;

        j += 1;
        while ( w >= p )  // write tail
        {
            a_[j] = p;
            w -= p;
            j += 1;
        }

        if ( w != 0 )
        {
            a_[j] = w;
            m_ = j;
        }
        else
        {
            m_ = j - 1;
        }

        s_ = m_ + (a_[m_] != 1);


        return m_;
    }


    ulong durfee_n()  const
    // Return side length of the Durfee square.
    {
        ulong d = 0;
        for (ulong j=1; j<=m_; ++j)
            if ( a_[j] >= j )  ++d;
            else  break;
        return d;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_aa()  const  // ASCII art
    { print_partition_desc_aa(data(), m_); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_desc_conj_aa(data(), m_); }

    bool OK()  const
    {
        if ( n_ != 0 )
        {
            if ( a_[s_] != 1 )  return false;
            if ( a_[s_-1] <= 1 )  return false;
        }

        return is_partition_desc(data(), num_parts(), n_);
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_DESC_H__
