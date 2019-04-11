#if !defined  HAVE_PAREN_PREF_H__
#define       HAVE_PAREN_PREF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


// whether to use one-based array:
#define PAREN_PREF_BASE1  // default on (faster)

// use arrays instead of pointers (slight speedup):
//#define PAREN_PREF_FIXARRAYS  // default off (must have s+t<=63)


class paren_pref
// All strings of t ones and s zeros (t>=s>0) where the number of
// zeros in any prefix does not exceed the number of ones.
// For t==s: well-formed parentheses strings by prefix shifts.
//.
// Loopless algorithm as given in
//   Frank Ruskey, Aaron Williams:
//   "Generating Balanced Parentheses and Binary Trees by Prefix Shifts"
//   CATS 2008, Computing: The Australasian Theory Symposium,
//   Wollongong, Australia, (2008)
{
public:
    const ulong t_, s_;  // t: number of ones, s: number of zeros
    const ulong nq_;  // aux
    ulong x_, y_;  // aux
#ifdef PAREN_PREF_FIXARRAYS
    ulong b_[64];  // array of t ones and s zeros
#else
    ulong *b_;     // array of t ones and s zeros
#endif

private:  // have pointer data
    paren_pref(const paren_pref&);  // forbidden
    paren_pref & operator = (const paren_pref&);  // forbidden

public:
    explicit paren_pref(ulong t, ulong s)
        // Must have: t >= s > 0
        : t_(t), s_(s), nq_(s+t-(s==t))
    {
//        t_ = t;
//        s_ = s;
//        nq_ = s+t-(s==t);

#ifndef PAREN_PREF_FIXARRAYS
#ifdef PAREN_PREF_BASE1
        b_ = new ulong[s_+t_+1];  // element [0] unused
#else
        b_ = new ulong[s_+t_];
#endif
#endif
        first();
    }

    ~paren_pref()
    {
#ifndef PAREN_PREF_FIXARRAYS
        delete [] b_;
#endif
    }


#ifdef PAREN_PREF_BASE1
    const ulong * data()  const  { return b_+1; }
#else
    const ulong * data()  const  { return b_; }
#endif

    void first()
    {
#ifdef PAREN_PREF_BASE1
        for (ulong j=0; j<=t_; ++j)  b_[j] = 1;
        for (ulong j=t_+1; j<=s_+t_; ++j)  b_[j] = 0;
        x_ = y_ = t_;
#else
        for (ulong j=0; j<t_; ++j)  b_[j] = 1;
        for (ulong j=t_; j<s_+t_; ++j)  b_[j] = 0;
        x_ = y_ = t_ - 1;
#endif
    }

    bool next()
    {
#ifdef PAREN_PREF_BASE1
        if ( x_ >= nq_ )  return false;  // was last
        b_[x_] = 0;
        b_[y_] = 1;
        ++x_;
        ++y_;
        if ( b_[x_] == 0 )
        {
            if ( x_ == 2*y_ - 2 )  ++x_;  // { Case (c) }
            else
            {
                b_[x_] = 1;  // { Case (b) }
                b_[2] = 0;
                x_ = 3;
                y_ = 2;
            }
        }  // { else Case (a) }
        return true;
#else
        if ( x_+1 >= nq_ )  return false;  // was last
        b_[x_] = 0;
        b_[y_] = 1;
        ++x_;
        ++y_;
        if ( b_[x_] == 0 )
        {
            if ( x_+1 == 2*y_ )  ++x_;  // { Case (c) }
            else
            {
                b_[x_] = 1;  // { Case (b) }
                b_[1] = 0;
                x_ = 2;
                y_ = 1;
            }
        }  // { else Case (a) }
        return true;
#endif
    }

    bool OK()  const
    {
        ulong s = 0,  t = 0;
        const ulong *x = data();
        for (ulong j=0; j<s_+t_; ++j)  if ( x[j]==1 )  ++t;  else  ++s;
        if  (s!=s_)  return false;
        if  (t!=t_)  return false;
        long u = 0;
        for (ulong j=0; j<s_+t_; ++j)
        {
            if ( x[j] == 1 )  ++u;  else  --u;
            // GCC 4.9.1 with -Wstrict-overflow=5 issues the warning
            // "assuming signed overflow does not occur when ..."
            // This is a false positive.
            if ( u < 0 )  return false;
        }
        return true;
    }
};
// -------------------------

#undef PAREN_PREF_BASE1
//#undef PAREN_PREF_FIXARRAYS  // better leave in


#endif  // !defined HAVE_PAREN_PREF_H__
