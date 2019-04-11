#if !defined HAVE_ACYCLIC_MAP_H__
#define      HAVE_ACYCLIC_MAP_H__
// This file is part of the FXT library.
// Copyright (C) 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"


class acyclic_map
// Acyclic maps: maps from {1, 2, 3, .., n} to {0, 1, 2, 3, ..., n} where
//  each element is ultimately mapped to 0.
// Lexicographic order.
// See OEIS sequence A000272 (n^(n-2)).
{
public:
    ulong *a_;  // digits
    ulong *m_;  // max allowed values in map
    ulong n_;  // Number of elements
    ulong j_;  // leftmost position of last change

private:  // have pointer data
    acyclic_map(const acyclic_map&);  // forbidden
    acyclic_map & operator = (const acyclic_map&);  // forbidden

public:
    explicit acyclic_map(ulong n, ulong m)
    {
        n_ = n;

        a_ = new ulong[n_+1+(n_==0)];
        m_ = new ulong[n_+1+(n_==0)];

        a_[0] = 0;  // only used for following trajectories
        m_[0] = 0;  // unused

        for (ulong j=1; j<=n_; ++j)  m_[j] = m;

        first();
    }

    ~acyclic_map()
    {
        delete [] a_;
        delete [] m_;
    }

    const ulong * data()  const  { return a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        j_ = 0;
    }

private:
    bool check_pos(ulong j)  const
    {
        // this function is the performance bottleneck
        ulong v = a_[j];

        for (ulong i=0; i<n_/2; ++i) // follow trajectory
        {
            v = a_[v];
            v = a_[v];
            if ( v==0 )  return true;
        }
        return ( v==0 );  // need test with empty loop (n==1)
    }

public:
    bool next()
    {
        ulong j = n_;
        while ( j != 0 )
        {
            ulong d = a_[j];  // can read sentinel
            while ( true )
            {
                d += 1;
                d += (d==j);  // no fixed point
                if ( d > m_[j] )  break;

                a_[j] = d;
                if ( check_pos(j) )
                {
                    j_ = j;
                    return true;
                }
            }

            a_[j] = 0;
            --j;
        }

        return false;  // current is last
    }


    ulong pos()  const  { return j_; }  // position of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_vec(bla, data(), n_, dfz); }

    bool OK()  const
    {
        for (ulong j=1; j<=n_; ++j)
            if ( a_[j] > m_[j] )  return false;

        if ( a_[0] != 0 )  return false;

        for (ulong j=1; j<=n_; ++j)  // is acyclic?
            if ( ! check_pos(j) )  return false;

        return true;
    }
};
// -------------------------



#endif  // !defined HAVE_ACYCLIC_MAP_H__
