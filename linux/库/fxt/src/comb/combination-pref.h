#if !defined HAVE_COMBINATION_PREF_H__
#define      HAVE_COMBINATION_PREF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class combination_pref
// Combinations via prefix shifts ("cool-lex" order) as delta sets.
//.
//  Algorithm as in
//  Frank Ruskey, Aaron Williams:
//    "Generating combinations by prefix shifts"
//    Lecture Notes in Computer Science, vol.3595, 2005.
//    Extended Abstract for COCOON 2005.
{
public:
    ulong *b_;  // data as delta set
    ulong s_, t_, n_;  // combination (n choose k) where n=s+t, k=t.
private:
    ulong x, y;  // aux

private:  // have pointer data
    combination_pref(const combination_pref&);  // forbidden
    combination_pref & operator = (const combination_pref&);  // forbidden

public:
    explicit combination_pref(ulong n, ulong k)
    // Must have: n>=2, k>=1  (i.e. s!=0 and t!=0)
    {
        s_ = n - k;
        t_ = k;
        n_ = s_ + t_;
        b_ = new ulong[n_];
        first();
    }

    ~combination_pref()
    {
        delete [] b_;
    }

    void first()
    {
        for (ulong j=0; j<n_; ++j)  b_[j] = 0;
        for (ulong j=0; j<t_; ++j)  b_[j] = 1;
        x = 0;  y = 0;
    }

    bool next()
    {
        if ( x==0 )  { x=1;  b_[t_]=1;  b_[0]=0;  return true; }
        else
        {
            if ( x>=n_-1 )  return false;
            else
            {
                b_[x] = 0; ++x;  b_[y] = 1; ++y;  // X(s,t)
                if ( b_[x]==0 )
                {
                    b_[x] = 1;  b_[0] = 0;       // Y(s,t)
                    if ( y>1 )  x = 1;           // Z(s,t)
                    y = 0;
                }
                return true;
            }
        }
    }

    const ulong * data()  const  { return b_; }
    ulong size()  const  { return n_; }
};
// -------------------------


#endif  // !defined HAVE_COMBINATION_PREF_H__
