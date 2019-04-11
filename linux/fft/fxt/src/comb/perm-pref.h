#if !defined  HAVE_PERM_PREF_H__
#define       HAVE_PERM_PREF_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/rotate.h"
#include "perm/reverse.h"
#include "aux0/swap.h"
#include "fxttypes.h"


class perm_pref
// Permutations via prefix shifts ("cool-lex" order).
// Specialization of class mset_perm_pref.
{
public:
    ulong n_;    // number of objects
    ulong *ms_;  // permutation in ms[0], ..., ms[n-1], sentinel at [n]
    ulong ln_;   // length of the longest non-increasing prefix

private:  // have pointer data
    perm_pref(const perm_pref&);  // forbidden
    perm_pref & operator = (const perm_pref&);  // forbidden

public:
    explicit perm_pref(ulong n)
    {
        n_ = n;
        ms_ = new ulong[n_+1];
        ms_[n_] = n_;  // sentinel (must be greater than all elements)
        first();
    }

    ~perm_pref()
    {
        delete [] ms_;
    }

    void first()
    {
#if 1
        ms_[0] = 0;
        for (ulong j=1;  j<n_;  ++j)  ms_[j] = n_-j;
#else
        for (ulong j=0;  j<n_;  ++j)  ms_[j] = j;
        reverse(ms_, n_);   // non-increasing permutation
        rotate_right1(ms_, n_);  // ... shall be the last
#endif
        ln_ = 1;
    }

    const ulong * data()  const { return ms_; }

    ulong next()
    // Return length of rotated prefix, zero with last permutation.
    {
        const ulong i = ln_;
        ulong nr;  // number of elements rotated
        if ( i >= n_-1 )
        {
            nr = n_;
            rotate_right1(ms_, nr);
            if ( i==n_ )  return 0;  // was last
        }
        else
        {
            nr = ln_ + 1 + ( ms_[i+1] <= ms_[i-1] );
            rotate_right1(ms_,  nr);
        }

        const bool cmp = ( ms_[0] < ms_[1] );
        ln_ =   ( cmp ? 1 : ln_ + 1 );
        return nr;
    }
};
// -------------------------



#endif  // !defined HAVE_PERM_PREF_H__
