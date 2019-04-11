#if !defined HAVE_PERM_LEX_H__
#define      HAVE_PERM_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_lex
// Permutations in lexicographic order
{
public:
    ulong *p_;  // permutation in 0, 1, ..., n-1, sentinel at [-1]
    ulong n_;   // number of elements to permute
//    ulong ct_;   // number of elements to permute

private:  // have pointer data
    perm_lex(const perm_lex&);  // forbidden
    perm_lex & operator = (const perm_lex&);  // forbidden

public:
    explicit perm_lex(ulong n)
    // Must have n>=1
    {
        n_ = n;
        p_ = new ulong[n_+1];
        p_[0] = 0;  // sentinel
        ++p_;  // nota bene
        first();
    }

    ~perm_lex()
    {
        --p_;
        delete [] p_;
    }

    void first()
    {
        for (ulong i=0; i<n_; i++)  p_[i] = i;
//        ct_ = 0;
    }

    const ulong * data()  const  { return p_; }

    bool next()
    {
//        if ( (++ct_) & 1 )  // easy case: (slowdown!)
//        {
//            swap2(p_[n_-1], p_[n_-2]);
//            return true;
//        }
//        else  // Based on code by Glenn Rhoads (who attributes the algorithm to Dijkstra):
        {
            // find rightmost pair with p_[i] < p_[i+1]:
            const ulong n1 = n_ - 1;
            ulong i = n1;
            do  { --i; }  while ( p_[i] > p_[i+1] );  // can read sentinel
            if ( (long)i < 0 )  return false;  // last sequence is falling seq.

            // find rightmost element p[j] less than p[i]:
            ulong j = n1;
            while ( p_[i] > p_[j] )  { --j; }

            swap2(p_[i], p_[j]);

            // Here the elements p[i+1], ..., p[n-1] are a falling sequence.
            // Reverse order to the right:
            ulong r = n1;
            ulong s = i + 1;
            while ( r > s )  { swap2(p_[r], p_[s]);  --r;  ++s; }

            return true;
        }
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------



#endif  // !defined HAVE_PERM_LEX_H__
