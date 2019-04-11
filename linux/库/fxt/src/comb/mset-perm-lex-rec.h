#if !defined  HAVE_MSET_PERM_LEX_REC_H__
#define       HAVE_MSET_PERM_LEX_REC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

class mset_perm_lex_rec
// Multiset permutations in lexicographic order, recursive algorithm.
{
public:
    ulong k_;    // number of different sorts of objects
    ulong *r_;   // number of elements '0' in r[0], '1' in r[1], ..., 'k-1' in r[k-1]
    ulong n_;    // number of objects
    ulong *ms_;  // multiset data in ms[0], ..., ms[n-1]
    ulong *nn_;  // position of next nonempty bucket
    // nn[k] points initially to the first bucket
    void (*visit_)(const mset_perm_lex_rec &);  // function to call with each permutation
    ulong ct_;  // count objects
    ulong rct_;  // count recursions (==work)

private:  // have pointer data
    mset_perm_lex_rec(const mset_perm_lex_rec&);  // forbidden
    mset_perm_lex_rec & operator = (const mset_perm_lex_rec&);  // forbidden

public:
    explicit mset_perm_lex_rec(ulong *r, ulong k)
    {
        k_ = k;
        r_ = new ulong[k];
        for (ulong j=0; j<k_; ++j)  r_[j] = r[j];  // get buckets

        n_ = 0;
        for (ulong j=0; j<k_; ++j)  n_ += r_[j];
        ms_ = new ulong[n_];

        nn_ = new ulong[k_+1];  // incl sentinel
        for (ulong j=0; j<k_; ++j)  nn_[j] = j+1;
        nn_[k] = 0;  // pointer to first nonempty bucket
    }

    ~mset_perm_lex_rec()
    {
        delete [] ms_;
        delete [] r_;
        delete [] nn_;
    }

    void generate(void (*visit)(const mset_perm_lex_rec &))
    {
        visit_ = visit;
        ct_ = 0;
        rct_ = 0;
        mset_perm_rec(0);
    }

private:
    void mset_perm_rec(ulong d);
};
// -------------------------


#endif  // !defined HAVE_MSET_PERM_LEX_REC_H__
