#if !defined HAVE_PARTITION_RGS_LEX_H__
#define      HAVE_PARTITION_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "comb/is-partition-rgs.h"
#include "fxttypes.h"


class partition_rgs_lex
// Restricted growth strings (RGS) for partitions as descending lists,
// lexicographic order.
// Same as: least Young tableau (as RGS) with fixed shape (partition).
// Cf. OEIS sequence A000041.
{
public:
    ulong *a_;  // RGS
    ulong *st_; // stats (a partition of n)
    ulong n_;   // length of the RGS.

private:  // have pointer data
    partition_rgs_lex(const partition_rgs_lex&);  // forbidden
    partition_rgs_lex & operator = (const partition_rgs_lex&);  // forbidden

public:
    explicit partition_rgs_lex(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_ + 1 + (n_==0)];

        first();
    }

    ~partition_rgs_lex()
    {
        delete [] a_;
    }

    const ulong * data()  const  { return a_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        if ( n_<=1 )  a_[1] = 1;  // sentinel for n<=1
    }

    ulong next()
    // Return position of leftmost change.
    // Return zero if current RGS is last.
    {
        if ( a_[1] == 1 )  return 0;  // current is last

        ulong j = n_ - 1;

#if 1   // easy case (rather rare, still a small speedup)
        ulong v = a_[j];
        ulong v1 = v + 1;
        if ( v == a_[j-1] )
        {
            a_[j] = v1;
            return j;
        }
#endif

        // find smallest part with multiplicity >= 2:
#if 1
        while ( a_[j] != a_[j-1] )  --j;
#else
        // small slowdown
        ulong t = a_[j];
        do { --t; --j; }  while ( a_[j]==t );
        ++j;
#endif
        ulong vj = a_[j];

        ulong i;  // start position for copying
        if ( vj == 0 )  i = 0;
        else
        {
            i = j - 1;
            while ( a_[i]==vj )  --i;
            ++i;
        }

        ulong ret = j;

        do  // copy with increment
        {
            a_[j] = a_[i] + 1;
            ++i;
            ++j;
        }
        while ( j != n_ );

        return ret;
    }


    bool OK()  const
    {
        if ( ! is_partition_rgs(a_, n_, true) )  return false;

        return  true;
    }

    void print(const char *bla, bool dfz)  const
    { print_vec(bla, a_, n_, dfz); }

    void print_sym(const char *bla)  const
    { print_sym_vec(bla, a_, n_); }

    void print_partition(const char *bla)  const;
};
// -------------------------


#endif  // !defined HAVE_PARTITION_RGS_LEX_H__
