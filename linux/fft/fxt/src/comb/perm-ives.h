#if !defined  HAVE_PERM_IVES_H__
#define       HAVE_PERM_IVES_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"
#include "fxttypes.h"

// whether to use arrays instead of pointers, gives a small speedup:
//#define PERM_IVES_FIXARRAYS  // default is off

// whether to treat "easy case" extra:
//#define PERM_IVES_OPT  // default is off (slowdown with pointers)

// whether to use alternative branch:
#define PERM_IVES_OPT2  // default is on (but: slowdown with arrays)

class perm_ives
// Permutation in an order given by Ives.
// The permutations are the order c of
//   F. M. Ives: {Permutation enumeration: four new permutation algorithms},
//   Communications of the ACM, vol.19, no.2, pp.68-72,  February-1976.
// The inverse permutations are Ives' order a.
{
public:
#ifndef PERM_IVES_FIXARRAYS
    ulong *p_;   // permutation
    ulong *ip_;  // inverse permutation
#else
    ulong p_[32];
    ulong ip_[32];
#endif
    ulong n_;    // permutations of n elements
#ifdef PERM_IVES_OPT
    ulong ctm_;   // aux: counter for easy case
    ulong ctm0_;  // aux: start value of ctm == n*(n-1)-1
#endif

private:  // have pointer data
    perm_ives(const perm_ives&);  // forbidden
    perm_ives & operator = (const perm_ives&);  // forbidden

public:
    explicit perm_ives(ulong n)
    // Must have: n >= 2
    {
        n_ = n;
#ifndef PERM_IVES_FIXARRAYS
        p_ = new ulong[n_];
        ip_ = new ulong[n_];
#endif
#ifdef PERM_IVES_OPT
        ctm0_ = n_ * (n_ - 1) - 1;
#endif
        first();
    }

    ~perm_ives()
    {
#ifndef PERM_IVES_FIXARRAYS
        delete [] p_;
        delete [] ip_;
#endif
    }

    const ulong *data()  const { return p_; }
    const ulong *invdata()  const { return ip_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  p_[k] = k;
        for (ulong k=0; k<n_; ++k)  ip_[k] = k;
#ifdef PERM_IVES_OPT
        ctm_ = ctm0_;
#endif
    }

    bool next()
    {
#ifdef PERM_IVES_OPT
        if ( ctm_-- )  // easy case
        {
            const ulong i1 = ip_[0];  // e1 == 0
            const ulong i2 = (i1==n_-1 ? 0 : i1+1);
            const ulong e2 = p_[i2];
            p_[i1] = e2;  p_[i2] = 0;
            ip_[0] = i2;  ip_[e2] = i1;
            return true;
        }
        ctm_ = ctm0_;
#endif  // PERM_IVES_OPT

        ulong e1 = 0,  u = n_ - 1;
        do
        {
            const ulong i1 = ip_[e1];
            const ulong i2 = (i1==u ? e1 : i1+1 );
            const ulong e2 = p_[i2];
            p_[i1] = e2;  p_[i2] = e1;
            ip_[e1] = i2;  ip_[e2] = i1;

#ifdef PERM_IVES_OPT2
            if ( (p_[e1]^e1) | (p_[u]^u) )  return true;
#else
            if ( (p_[e1]!=e1) || (p_[u]!=u) )  return true;
#endif
            ++e1;
            --u;
        }
        while ( u > e1 );

        return false;
    }

    void print(const char *bla, bool dfz)  const
    // If dfz is true then Dots are printed For Zeros.
    {
        print_perm(bla, data(), n_, dfz);
    }

     void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }
};
// -------------------------

//#undef PERM_IVES_FIXARRAYS
//#undef PERM_IVES_OPT
//#undef PERM_IVES_OPT2

#endif  // !defined HAVE_PERM_IVES_H__
