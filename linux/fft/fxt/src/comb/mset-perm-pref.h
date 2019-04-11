#if !defined  HAVE_MSET_PERM_PREF_H__
#define       HAVE_MSET_PERM_PREF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/rotate.h"
#include "perm/reverse.h"
#include "aux0/swap.h"
#include "fxttypes.h"


// whether to determine length of longest non-increasing prefix
// in O(1) as given in the paper:
#define MSET_PERM_PREF_LEN  // default on (speedup)

class mset_perm_pref
// Multiset permutations via prefix shifts ("cool-lex" order).
//.
// See
// Aaron Williams:
//   "Loopless generation of multiset permutations by prefix shifts"
//   Symposium on Discrete Algorithms, New York, 2009.
{
public:
    ulong k_;    // number of different sorts of objects
    ulong *r_;   // number of elements '0' in r[0], '1' in r[1], ..., 'k-1' in r[k-1]
    ulong n_;    // number of objects
    ulong *ms_;  // multiset data in ms[0], ..., ms[n-1], sentinel at [n]
#ifdef MSET_PERM_PREF_LEN
    ulong ln_;   // length of the longest non-increasing prefix
#endif

private:  // have pointer data
    mset_perm_pref(const mset_perm_pref&);  // forbidden
    mset_perm_pref & operator = (const mset_perm_pref&);  // forbidden

public:
    explicit mset_perm_pref(const ulong *r, ulong k)
    {
        k_ = k;
        r_ = new ulong[k];
        for (ulong j=0; j<k_; ++j)  r_[j] = r[j];  // get buckets

        n_ = 0;
        for (ulong j=0; j<k_; ++j)  n_ += r_[j];
        ms_ = new ulong[n_+1];
        ms_[n_] = k_;  // sentinel (must be greater than all elements)

        first();
    }

    void first()
    {
        for (ulong j=0, i=0;  j<k_;  ++j)
            for (ulong h=r_[j];  h!=0;  --h, ++i)  ms_[i] = j;

        reverse(ms_, n_);   // non-increasing permutation
        rotate_right1(ms_, n_);  // ... shall be the last

#ifdef MSET_PERM_PREF_LEN
        ln_ = 1;
        if ( k_ == 1 )  ln_ = n_;  // only one type of object
#endif
    }

    ~mset_perm_pref()
    {
        delete [] ms_;
        delete [] r_;
    }

    const ulong * data()  const { return ms_; }

    ulong next()
    // Return length of rotated prefix, zero with last permutation.
    {
#ifdef MSET_PERM_PREF_LEN
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

#else  // MSET_PERM_PREF_LEN

        // scan for prefix (rather unsophisticated):
        ulong i = -1UL;
        do  { ++i; }  while ( ms_[i] >= ms_[i+1] );  // can read sentinel
        ++i;
        // here: i == length of longest non-increasing prefix
        if ( i >= n_-1 )
        {
            rotate_right1(ms_, n_);
            if ( i==n_ )  return 0;  // was last
            return n_;
        }
        else
        {
            // compare last of prefix with element 2 positions right:
            i += ( ms_[i+1] <= ms_[i-1] );
            ++i;
            rotate_right1(ms_, i);
            return i;
        }
#endif  // MSET_PERM_PREF_LEN
    }
};
// -------------------------

//#undef MSET_PERM_PREF_LEN  // leave defined


#endif  // !defined HAVE_MSET_PERM_PREF_H__
