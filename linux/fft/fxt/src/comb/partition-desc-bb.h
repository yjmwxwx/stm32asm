#if !defined HAVE_PARTITION_DESC_BB_H__
#define      HAVE_PARTITION_DESC_BB_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-partition-desc.h"

#include "comb/comb-print.h"
#include "comb/print-partition-aa.h"

#include "fxttypes.h"

//#include "jjassert.h"
//#include "fxtio.h"

//#define PARTITION_DESC_BB_FIXARRAYS  // default off


class partition_desc_bb
// Integer partitions as weakly descending list of parts,
//   with bounds for size of parts and number of parts.
// Lexicographic order.
{
public:
    ulong n_;  // integer partitions of n
    ulong m_;  // current partition has m parts
    ulong s_;  // position of downstep where we can add 1:
    // == position of first part == 1, or past end
    ulong ba_;  // bound for size of parts
    ulong bm_;  // bound for number of parts

#ifndef PARTITION_DESC_BB_FIXARRAYS
    ulong *a_;  // partition: a[1] + a[2] + ... + a[m] = n
#else
    ulong a_[448];  // > 2^66 partitions
#endif

private:  // have pointer data
    partition_desc_bb(const partition_desc_bb&);  // forbidden
    partition_desc_bb & operator = (const partition_desc_bb&);  // forbidden

public:
    explicit partition_desc_bb(ulong n, ulong ba, ulong bm)
    {
        n_ = n;
#ifndef PARTITION_DESC_BB_FIXARRAYS
        a_ = new ulong[n_+1 +(n==0)];
#endif
        a_[0] = n_ + 5;  // sentinel, must have a[0] > n and a[0] > 1
        a_[1] = 0;  // first_part() for n==0

        ba_ = ba;
        if ( ba_ > n_ )  ba_ = n_;
        ba_ = (ba_ ? ba_ : n_);  // take bound == 0 for "no bound"

        bm_ = bm;
        if ( bm_ > n_ )  bm_ = n_;
        bm_ = (bm_ ? bm_ : n_ );  // take bound == 0 for "no bound"

//        jjassert( bm_ <= n_ + 1 );

        first();
    }

    ~partition_desc_bb()
    {
#ifndef PARTITION_DESC_BB_FIXARRAYS
        delete [] a_;
#endif
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }
    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }


private:
    ulong write_tail(ulong j, ulong s)
    // Write lex-min partition of s, starting from position j,
    // return last position written to.
    // Must have s >= 1,  j <= bm_
    {
//        jjassert( s >= 1 );
        const ulong t = bm_ + 1 - j;  // max length of tail

#if 1  // optimize for long tail
        if ( s <= t )  return j + s - 1;
#endif
#if 0  // optimize for short tail
        if ( t <= 2 )
        {
            if ( t==1 )
            {
                a_[j] = s;
                return j;
            }
            else // t==2
            {
                ulong h = s / 2;  // smaller half
                s -= h;  // bigger half
                a_[j] = s;
                if ( h != 0 )
                {
                    j += 1;
                    a_[j] = h;
                }
                return j;
            }
        }
#endif

        // expensive div/mod case:
        const ulong q = s / t;  // smaller part to be written, larger is q+1
        ulong r = s % t;  // how often larger parts need to be written
        const ulong q1 = q + 1;
        while ( r )  {  a_[j] = q1;  s -= q1;  r -= 1;  ++j; }
        while ( s )  {  a_[j] = q;  s -= q; ++j; }
        return  j - 1;
    }

public:
    bool first()
    // Return whether such a partition exists
    {
        if ( n_ != 0 )
        {
            if ( ba_ * bm_ < n_ )   return false;

            // set currently unused elements to 1:
            for (ulong j=1; j<=bm_; ++j)  a_[j] = 1;

            if ( n_ > bm_ )
                m_ = write_tail(1, n_);
            else  // optimize for long tail
                m_ = n_;

            // find first part == 1:
            s_ = m_;
            while ( a_[s_] == 1 )  s_ -= 1;
            s_ += 1;
        }
        else
        {
            m_ = 0;
            s_ = 1;
        }

        return true;
    }


#if 0
    void last()
    // Todo: implement
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        if ( n_ != 0 )  a_[1] = n_;
        m_ = ( n_!=0 ? 1 : 0 );
        s_ = ( n_>1 ? 2 : 1 );
    }
#endif

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        const ulong y = a_[m_-1];
#if 1 // speedup
        if ( y == 1 )  // easy case (very frequent)
        {
            ulong as = a_[s_] + 1;
            if ( as > ba_ )  return 0;  // current is last
            a_[s_] = as;
            ++s_;
            --m_;
            return  m_;
        }
#endif

        ulong z = a_[m_];

        a_[m_] = 1;
        ulong j = m_ - 1;

        while ( a_[j-1] == y )  // scan left to next descent
        {
            z += a_[j];
            a_[j] = 1;
            --j;
        }
        ulong as = a_[j] + 1;
        if ( as > ba_ )  return 0;  // current is last
        a_[j] = as;

        m_ = j + z - 1;
        j += 1;
        if ( z > 1 )  m_ = write_tail(j, z - 1);
//        m_ = write_tail(j, z - 1);  // OK with long tail optimization

        if ( a_[m_] == 1 )
        {
            s_ = m_;
            while ( a_[s_-1] == 1 )  s_ -= 1;
        }
        else  s_ = j;

        return m_;
    }


#if 0
    ulong prev()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    // Todo: implement
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
#endif

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
            if ( a_[s_-1] <= 1 )  return false;

            if ( a_[m_] == 1 )
                if ( a_[s_] != 1 )  return false;
        }

        return is_partition_desc(data(), num_parts(), n_);
    }
};
// -------------------------


#endif  // !defined HAVE_PARTITION_DESC_BB_H__
