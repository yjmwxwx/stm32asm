#if !defined  HAVE_CAYLEY_PERM_H__
#define       HAVE_CAYLEY_PERM_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"
#include "aux0/swap.h"

#include "fxttypes.h"

//#include "jjassert.h"


class cayley_perm
// Cayley permutations:  Length-n words such that all elements
//   from 0 to the maximum value occur at least once.
// Same as: permutations of the (RGS for) set partitions of n.
// Same as: weak orders on n elements (weak orders are
//   relations that are transitive and complete).
// Same as: preferential arrangements of n labeled elements.
// Generation such that the major order is by content, and
//   the minor order is lexicographic.
// Cf. OEIS sequence A000670.
{
public:
    ulong n_;   // number of objects
    ulong m_;   // maximal value (digit) in current word
    ulong mx_;  // maximal allowed digit (== max value of m_)
    ulong mi_;  // minimum value of max digit (== min value of m_)
    ulong *a_;  // multiset data in a[0], ..., a[n-1], sentinels at [-1] and [-2]

private:  // have pointer data
    cayley_perm(const cayley_perm&);  // forbidden
    cayley_perm & operator = (const cayley_perm&);  // forbidden

public:
    explicit cayley_perm(ulong n)
    // Should have n>=1 (if n==0 then n==1 is used)
    {
        n_ = (n ? n : 1);  // make things work for n==0
        mx_ = n_ - 1;
        mi_ = 0;
        a_ = new ulong[n_+2];
        a_[0] = 0;  a_[1] = 1;  // sentinels: a[0] < a[1]
        a_ += 2;  // nota bene

        first();
    }

    ~cayley_perm()
    {
        a_ -= 2;
        delete [] a_;
    }

    void first()
    {
        for (ulong j=0; j<n_; ++j)  a_[j] = 0;
        m_ = mi_;
        ulong v = mi_,  j = n_ - 1;
//        jjassert( mi_ < 99999 );
        while ( v )  { a_[j] = v;  --j;  --v; }
    }

    void first(ulong mi, ulong mx)
    {
        if ( mi >= n_ )  mi = n_ - 1;
        if ( mx >= n_ )  mx = n_ - 1;
        if ( mi > mx )  mi = mx;
//        if ( n_==0 )  mi = mx = 0;
        mx_ = mx;
        mi_ = mi;

        first();
    }

private:
    bool next_perm()
    // Next permutation of the multiset in a[].
    {
        // find rightmost pair with a[i] < a[i+1]:
        const ulong n1 = n_ - 1;
        ulong i = n1;
        do  { --i; }  while ( a_[i] >= a_[i+1] );  // can read sentinel
//        jjassert( (long)i >= -2 );
        if ( (long)i < 0 )  return false;  // last sequence is falling seq.

        // find rightmost element p[j] less than p[i]:
        ulong j = n1;
        while ( a_[i] >= a_[j] )  { --j; }

        swap2(a_[i], a_[j]);

        // Here the elements a[i+1], ..., a[n-1] are a falling sequence.
        // Reverse order to the right:
        ulong r = n1;
        ulong s = i + 1;
        while ( r > s )  { swap2(a_[r], a_[s]);  --r;  ++s; }

        return true;
    }

public:
    bool next()
    {
        // try next permutation:
        if ( next_perm() )   return true;


        // try next content (smoothly increasing word with first digit zero):

        // reverse word:
        ulong i=0, k=n_-1;
        while ( i<k )  { swap2( a_[i], a_[k] );  ++i; --k; }

        ulong j = n_;
        while ( j )
        {
            --j;
            if ( a_[j-1] == a_[j] )  break;  // can read sentinel
        }

        if ( j==0 )  return false;  // current is last

        m_ = a_[j] + 1;
        if ( m_ > mx_ )  return  false;  // reached limit for max digit

        do
        {
            a_[j] = m_;
            ++j;
        }
        while ( j < n_ );

        return true;
    }

    const ulong * data()  const { return a_; }
    ulong max_digit()  const { return m_; }
    ulong num_parts()  const { return n_; }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_arrangement(const char *bla)  const;
};
// -------------------------



#endif  // !defined HAVE_CAYLEY_PERM_H__
