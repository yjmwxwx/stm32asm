#if !defined HAVE_PERM_STAR_H__
#define      HAVE_PERM_STAR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

// define to also compute inverse:
#define PERM_STAR_WITH_INVERSE

#define PERM_STAR_FIXARRAYS  // speedup

class perm_star
// Permutations in star-transposition order (a Gray code).
// Algorithm of Gideon Ehrlich, as given by Knuth
{
public:
    ulong n_;    // number of elements
    ulong swp_;  // index of element that was swapped (with index 0)
#ifndef PERM_STAR_FIXARRAYS
    ulong *a_;   // current permutation
    ulong *b_;   // auxiliary array
    ulong *c_;   // auxiliary array: mixed radix number in rising factorial base
#ifdef PERM_STAR_WITH_INVERSE
    ulong *ia_;   // inverse permutation
#endif
#else
    ulong a_[32];   // current permutation
    ulong b_[32];   // auxiliary array
    ulong c_[32];   // auxiliary array: mixed radix number in rising factorial base
#ifdef PERM_STAR_WITH_INVERSE
    ulong ia_[32];   // inverse permutation
#endif
#endif

private:  // have pointer data
    perm_star(const perm_star&);  // forbidden
    perm_star & operator = (const perm_star&);  // forbidden

public:
    explicit perm_star(ulong n)
    {
        n_ = n;
#ifndef PERM_STAR_FIXARRAYS
        a_ = new ulong[n_];
        b_ = new ulong[n_];
        c_ = new ulong[n_+1];
#ifdef PERM_STAR_WITH_INVERSE
        ia_ = new ulong[n_];
#endif
#endif
        first();
    }

    ~perm_star()
    {
#ifndef PERM_STAR_FIXARRAYS
        delete [] a_;
        delete [] b_;
        delete [] c_;
#ifdef PERM_STAR_WITH_INVERSE
        delete [] ia_;
#endif
#endif
    }

    void first()
    {
//        swp_ = n_ - 1;
        swp_ = 0;
        for (ulong k=0; k<n_; ++k)  a_[k] = b_[k] = k;
        for (ulong k=0; k<=n_; ++k)  c_[k] = 0;
#ifdef PERM_STAR_WITH_INVERSE
        for (ulong k=0; k<n_; ++k)  ia_[k] = k;
#endif
    }

    bool next()
    {
        ulong k = 1;
        while ( c_[k]==k )  { c_[k]=0;  ++k; }

        if ( k == n_ )   return false;

        ++c_[k];

        swp_ = b_[k];
        swap2(a_[0], a_[swp_]);
#ifdef PERM_STAR_WITH_INVERSE
        swap2(ia_[a_[0]], ia_[a_[swp_]]);
#endif

        ulong j = 1;
        --k;
        while ( j < k )  // < 0.18 iterations per call
        {
            swap2(b_[j], b_[k]);
            ++j;
            --k;
        }

        return  true;
    }

    ulong get_swap()  const  { return swp_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=0; s2=swp_; }


    const ulong * data()  const  { return a_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }

#ifdef PERM_STAR_WITH_INVERSE
    const ulong *invdata()  const  { return ia_; }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }
#endif
};
// -------------------------



#endif  // !defined HAVE_PERM_STAR_H__
