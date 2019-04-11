#if !defined HAVE_PARTITION_ASC_SUBSET_LEX_H__
#define      HAVE_PARTITION_ASC_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-asc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"


//#define PARTITION_ASC_SUBSET_LEX_FIXARRAYS  // default off
// tiny speedup with GCC 4.9.0

class partition_asc_subset_lex
// Partitions of n into positive parts as weakly ascending list of parts.
// Subset-lex order.
// Only the two last parts at the end are different from the previous partition.
// Loopless algorithm.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
#ifndef PARTITION_ASC_SUBSET_LEX_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions
#endif
    ulong n_;   // partition of n
    ulong m_;   // current partition has m parts

private:  // have pointer data
    partition_asc_subset_lex(const partition_asc_subset_lex&);  // forbidden
    partition_asc_subset_lex & operator = (const partition_asc_subset_lex&);  // forbidden

public:
    explicit partition_asc_subset_lex(ulong n)
    {
        n_ = n;
#ifndef PARTITION_ASC_SUBSET_LEX_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        // sentinel a[0] set in first()
#endif
        first();
    }

    ~partition_asc_subset_lex()
    {
#ifndef PARTITION_ASC_SUBSET_LEX_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  {  return m_; }
    ulong first_part()  const  { return a_[1]; }  // returns 0 for n==0
    ulong last_part()  const  { return a_[m_]; }  // returns 0 for n==0

    void first()
    {
        a_[0] = 1;  // sentinel: read (once) by test for right-extension
        a_[1] = n_ + (n_==0);  // use partitions of n=1 for n=0 internally
        m_ = 1;
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Loopless algorithm.
    {
        ulong y = a_[m_-1];  // may read sentinel a[0]
        ulong z = a_[m_];

        if ( z >= 2*y )  // extend to the right:
        {  //   [*, Y, Z] --> [*, Y, Y, Z-Y]
            a_[m_] = y;
            a_[m_+1] = z - y;  // >= y
            ++m_;
            return  m_;
        }

        z -= 1;  y += 1;
        if ( z >= y )  // add one unit to the left:
        {  //   [*, Y, Z] --> [*, Y+1, Z-1]
            a_[m_-1] = y;
            a_[m_] = z;
            return  m_;
        }

        if ( z == 0 )  // all-ones partition
        {
            if ( n_ <= 3 )  return 0;  // current is last

            //   [1, ..., 1, 1, 1, 1] -->  [1, ..., 2, 2]
            m_ -= 2;
            a_[m_] = 2;  a_[m_-1] = 2;
            return m_;
        }

        // add one unit to second left, add rest to end:
        //   [*, X, Y, Z] --> [*, X+1, Y+Z-1]
        a_[m_-2] += 1;
        a_[m_-1] += z;
        m_ -= 1;
        m_ -= (m_ == 1);  // last if partition has one part
        return  m_;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_-(n_==0), dfz); }

    void print_aa()  const  // ASCII art
    { print_partition_asc_aa(data(), m_-(n_==0)); }

    void print_conj_aa()  const  // ASCII art
    { print_partition_asc_conj_aa(data(), m_-(n_==0)); }

    bool OK()  const
    { return is_partition_asc(data(), num_parts()-(n_==0), n_); }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_ASC_SUBSET_LEX_H__
