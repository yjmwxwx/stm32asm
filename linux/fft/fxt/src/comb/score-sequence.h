#if !defined  HAVE_SCORE_SEQUENCE_H__
#define       HAVE_SCORE_SEQUENCE_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// whether to use arrays instead of pointers:
#define SCORE_SEQUENCE_FIXARRAYS
// slight speedup with GCC 4.8.0


class score_sequence
// Score sequences: weakly increasing sequences a[0,1,...,n-1] where
// sum(j=0..k, a[j]) >= k*(k+1)/2 and sum(j=0..n-1, a[j]) = (n+1)*n/2.
// Lexicographic order.
// See OEIS sequence A000571.
{
public:
#ifndef SCORE_SEQUENCE_FIXARRAYS
    // In all arrays the first elemnt is a sentinel.
    ulong *a_;  // score sequence
    ulong *s_;  // cumulative sums of a[]
    ulong *t_;  // lower bounds on cumulative sums: t[k] = k*(k+1)/2
#else
    ulong a_[64];  // 4174352074885128631693099364115810 sequences
    ulong s_[64];
    ulong t_[64];
#endif
    ulong n_;   // Number of digits (paren pairs)

private:  // have pointer data
    score_sequence(const score_sequence&);  // forbidden
    score_sequence & operator = (const score_sequence&);  // forbidden

public:
    explicit score_sequence(ulong n)
    {
        n_ = (n > 0 ? n : 1);  // shall work for n==0
#ifndef SCORE_SEQUENCE_FIXARRAYS
        a_ = new ulong[n_ + 1];
        s_ = new ulong[n_ + 1];
        t_ = new ulong[n_ + 1];
#endif
        a_[0] = 0;  // sentinel
        s_[0] = 0;
        t_[0] = 0;


        ulong tj = 0;
        for (ulong j=0; j<=n_; ++j)
        {
            t_[j] = tj;
            tj += j;
        }
        // t[] = [ 0 0 1 3 6 10 15 ... ]

        first();
    }

    ~score_sequence()
    {
#ifndef SCORE_SEQUENCE_FIXARRAYS
        delete [] a_;
        delete [] s_;
        delete [] t_;
#endif
    }

    const ulong *data()  const  { return a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)
        {
            a_[k] = k - 1;
            s_[k] = s_[k-1] + a_[k];
        }
    }

private:
    bool try_write_tail(ulong st, ulong j, ulong aj)
    {
        aj += 1;
        ulong sj = s_[j-1];
        do
        {
            sj += aj;
            if ( t_[j] > sj )
            {
                ulong d = t_[j] - sj;
                aj += d;
                sj += d;
            }
            s_[j] = sj;
            a_[j] = aj;
            if ( st < aj )  return false;
            st -= aj;
            ++j;
        }
        while ( j < n_ );
        if ( st < aj )  return false;
        a_[n_] = st;
//        s_[n_] = sj + st;
        return true;
    }

public:
    ulong next()
    // Return 1 + position of leftmost change, zero with last.
    {
        const ulong an = a_[n_];
        if ( n_ <= 2 )   return 0;

        const ulong an1 = a_[n_-1];
        if ( an > an1 + 1 )  // easy case
        {
            a_[n_] = an - 1;
            a_[n_-1] = an1 + 1;
            s_[n_-1] += 1;
            return  n_ - 1;
        }

        ulong j = n_ - 2;
        ulong st = an + an1;  // sum of elements in tail
        while ( j != 0 )
        {
            ulong aj = a_[j];
            st += aj;
            if ( try_write_tail(st, j, aj) )  return j;
            --j;
        }

        return 0;  // current is last
    }


    bool OK()  const
    {
        ulong s = 0;
        for (ulong j=1; j<=n_; ++j)
        {
            if ( a_[j] < a_[j-1] )  return false;
            s += a_[j];
            if ( s != s_[j] )  return false;
            if ( s < t_[j] )  return false;
        }

        if ( s_[n_] != t_[n_] )  return false;

        return true;
    }

};
// -------------------------


#endif  // !defined HAVE_SCORE_SEQUENCE_H__
