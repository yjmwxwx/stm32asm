#if !defined HAVE_SUBSET_LEX_H__
#define      HAVE_SUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

// If defined, an array is used instead of a pointer:
//#define SUBSET_LEX_MAX_ARRAY_LEN 64  // default is off

class subset_lex
// Nonempty subsets of the set {0,1,2,...,n-1} in subset-lex order.
// Representation as list of parts.
// Loopless generation.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong n_;   // number of elements in set, should have n>=1
    ulong k_;   // index of last element in subset
    ulong n1_;  // == n - 1 for n >=1, and == 0 for n==0
    // Number of elements in subset == k+1
#ifndef SUBSET_LEX_MAX_ARRAY_LEN
    ulong *x_;  // x[0...k-1]:  subset of {0,1,2,...,n-1}
#else
    ulong x_[SUBSET_LEX_MAX_ARRAY_LEN];
#endif

private:  // have pointer data
    subset_lex(const subset_lex&);  // forbidden
    subset_lex & operator = (const subset_lex&);  // forbidden

public:
    explicit subset_lex(ulong n)
    // Should have n>=1,
    // for n==0 one set with the element zero generated.
    {
        n_ = n;
        n1_ = (n_ ? n_ - 1 : 0 );
#ifndef SUBSET_LEX_MAX_ARRAY_LEN
        x_ = new ulong[n_ + (n_==0)];
#endif
        first();
    }

    ~subset_lex()
    {
#ifndef SUBSET_LEX_MAX_ARRAY_LEN
        delete [] x_;
#endif
    }


    ulong first()
    {
        k_ = 0;
        x_[0] = 0;
        return  k_ + 1;
    }

    ulong last()
    {
        k_ = 0;
        x_[0] = n1_;
        return  k_ + 1;
    }

    ulong next()
    // Generate next subset.
    // Return number of elements in subset.
    // Return zero if current is last.
    // Loopless algorithm.
    {
        if ( x_[k_] == n1_ )  // last element is max?
        {
            if ( k_==0 )  return 0;

            --k_;      // remove last element
            x_[k_] += 1;  // increment last element
        }
        else  // add next element from set:
        {
            ++k_;
            x_[k_] = x_[k_-1] + 1;
        }

        return  k_ + 1;
    }

    ulong prev()
    // Generate previous subset.
    // Return number of elements in subset.
    // Return zero if current is first.
    // Loopless algorithm.
    {
        if ( k_ == 0 )  // only one element ?
        {
            if ( x_[0]==0 )  return 0;

            x_[0] -= 1;  // decrement last (and only) element
            ++k_;
            x_[k_] = n1_;  // append maximal element
        }
        else
        {
            if ( x_[k_] == x_[k_-1] + 1 )  --k_;  // remove last element
            else
            {
                x_[k_] -= 1;  // decrement last element
                ++k_;
                x_[k_] = n1_;  // append maximal element
            }
        }

        return  k_ + 1;
    }

    ulong num_parts()  const  {  return  k_ + 1; }

    const ulong * data()  const  { return x_; }
};
// -------------------------


//#undef SUBSET_LEX_MAX_ARRAY_LEN  // better leave in


#endif  // !defined HAVE_SUBSET_LEX_H__
