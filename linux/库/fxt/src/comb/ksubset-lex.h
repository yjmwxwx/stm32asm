#if !defined HAVE_KSUBSET_LEX_H__
#define      HAVE_KSUBSET_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


class ksubset_lex
// Nonempty subsets of the set {0,1,2,...,n-1} with at most k elements.
// Representation as list of parts.
// Subset-lex order.
// Loopless generation.
// See OEIS sequence A117670.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong n_;  // number of elements in set, should have n>=1
    ulong j_;  // number of elements in subset
    ulong m_;  // max number of elements in subsets
    ulong *x_;  // x[0...j-1]:  subset of {0,1,2,...,n-1}

private:  // have pointer data
    ksubset_lex(const ksubset_lex&);  // forbidden
    ksubset_lex & operator = (const ksubset_lex&);  // forbidden

public:
    explicit ksubset_lex(ulong n, ulong k)
    // Should have n>=1 and k>=1,
    // for n==0 one set with one element is generated.
    {
        n_ = n;
        if ( k > n )  k = n_;
        m_ = k;
        x_ = new ulong[m_ + (m_==0)];
        first();
    }

    ~ksubset_lex()
    {
        delete [] x_;
    }

    ulong first()
    {
        j_ = 1;
        x_[0] = 0;
        return  j_;
    }

    ulong last()
    {
        j_ = 1;
        x_[0] = n_ - 1;
        return  j_;
    }

    ulong next()
    // Generate next subset.
    // Return number of elements in subset.
    // Return zero if current is last.
    // Loopless algorithm.
    {
        ulong j1 = j_ - 1;
        ulong z1 = x_[j1] + 1;
        if ( z1 < n_ )  // last element is not max
        {
            if ( j_ < m_ )  // append element
            {
                x_[j_] = x_[j1] + 1;
                ++j_;
                return  j_;
            }

            x_[j1] = z1;  // increment last element
            return j_;
        }
        else  // last element is max
        {
            if ( j1 == 0 )  return 0; // current is last

            --j_;
            x_[j_-1] += 1;
            return j_;
        }
    }

    ulong prev()
    // Generate previous subset.
    // Return number of elements in subset.
    // Return zero if current is first.
    // Loopless algorithm.
    {
        if ( j_ == 1 )  // only one element ?
        {
            if ( x_[0]==0 )  return 0;  // current is first

            x_[0] -= 1;  // decrement last (and only) element
            if ( j_ < m_ )  // can append max element
            {
                x_[1] = n_ - 1;  // append maximal element
                ++j_;
            }
            return j_;
        }
        else  // j >= 2
        {
            ulong z = x_[j_-1];
            ulong y = x_[j_-2];
            if ( z - 1 > y )  // can lower last element
            {
                x_[j_-1] -= 1;
                if ( j_ < m_ )  // can append max element
                {
                    x_[j_] = n_ - 1;
                    ++j_;
                }
                return j_;
            }
            else  // detach last element
            {
                --j_;
                return j_;
            }
        }
    }

    ulong num_parts()  const  {  return  j_; }

    const ulong * data()  const  { return x_; }

    bool OK()  const
    {
        if ( x_[j_-1] >= n_ )  return false;
        if ( j_ > m_ )  return false;
        return true;
    }
};
// -------------------------



#endif  // !defined HAVE_KSUBSET_LEX_H__
