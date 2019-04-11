#if !defined  HAVE_MSET_PERM_LEX_H__
#define       HAVE_MSET_PERM_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "aux0/swap.h"
#include "fxttypes.h"


class mset_perm_lex
// Multiset permutations in lexicographic order, iterative algorithm.
{
public:
    ulong k_;    // number of different sorts of objects
    ulong *r_;   // number of elements '0' in r[0], '1' in r[1], ..., 'k-1' in r[k-1]
    ulong n_;    // number of objects
    ulong *ms_;  // multiset data in ms[0], ..., ms[n-1], sentinels at [-1] and [-2]

private:  // have pointer data
    mset_perm_lex(const mset_perm_lex&);  // forbidden
    mset_perm_lex & operator = (const mset_perm_lex&);  // forbidden

public:
    explicit mset_perm_lex(const ulong *r, ulong k)
    {
        k_ = k;
        r_ = new ulong[k];
        for (ulong j=0; j<k_; ++j)  r_[j] = r[j];  // get buckets

        n_ = 0;
        for (ulong j=0; j<k_; ++j)  n_ += r_[j];
        ms_ = new ulong[n_+2];
        ms_[0] = 0; ms_[1] = 1;  // sentinels:  ms[0] < ms[1]
        ms_ += 2;  // nota bene

        first();
    }

    void first()
    {
        for (ulong j=0, i=0;  j<k_;  ++j)
            for (ulong h=r_[j];  h!=0;  --h, ++i)
                ms_[i] = j;
    }

    ~mset_perm_lex()
    {
        ms_ -= 2;
        delete [] ms_;
        delete [] r_;
    }

    const ulong * data()  const { return ms_; }

    ulong next()
    // Return position of leftmost change,
    // return n with last permutation.
    {
        // find rightmost pair with ms[i] < ms[i+1]:
        const ulong n1 = n_ - 1;
        ulong i = n1;
        do  { --i; }  while ( ms_[i] >= ms_[i+1] );  // can read sentinel
        if ( (long)i < 0 )  return n_;  // last sequence is falling seq.

        // find rightmost element ms[j] less than ms[i]:
        ulong j = n1;
        while ( ms_[i] >= ms_[j] )  { --j; }

        swap2(ms_[i], ms_[j]);

        // Here the elements ms[i+1], ..., ms[n-1] are a falling sequence.
        // Reverse order to the right:
        ulong r = n1;
        ulong s = i + 1;
        while ( r > s )  { swap2(ms_[r], ms_[s]);  --r;  ++s; }

        return i;
    }

    ulong num_parts()  const { return n_; }
    ulong num_sorts()  const { return k_; }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_MSET_PERM_LEX_H__
