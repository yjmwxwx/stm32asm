#if !defined HAVE_ORDERED_TREE_BRANCHES_H__
#define      HAVE_ORDERED_TREE_BRANCHES_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"


//#define ORDERED_TREE_BRANCHES_FIXARRAYS  // default off
// small speedup with GCC 4.9.1


class ordered_tree_branches
// Ordered trees with n non-root nodes by branches:
// branch lengths are a composition of n (array a[]) and
// branch heights (height of base of branch, array b[]) are such that
// b[j] < a[j-1] + b[j-1] for j>=2 (and b[1]=0).
{
public:
#ifndef ORDERED_TREE_BRANCHES_FIXARRAYS
    ulong *a_;  // branch lengths (limbs): a composition a[1] + a[2] + ... + a[m] = n
    ulong *b_;  // branch heights (absolute, above root)
#else
    ulong a_[64];
    ulong b_[64];
#endif
    ulong n_;   // number of non-root nodes
    ulong m_;   // number of branches (composition has m parts)

private:  // have pointer data
    ordered_tree_branches(const ordered_tree_branches&);  // forbidden
    ordered_tree_branches & operator = (const ordered_tree_branches&);  // forbidden

public:
    explicit ordered_tree_branches(ulong n)
    {
        n_ = n;  // number of non-root nodes
#ifndef ORDERED_TREE_BRANCHES_FIXARRAYS
        a_ = new ulong[n_+1+(n_==0)];
        b_ = new ulong[n_+1+(n_==0)];
#endif
        b_[0] = 0;  b_[1] = 0;
        a_[0] = 0;  a_[1] = 0;
        first();
    }

    ~ordered_tree_branches()
    {
#ifndef ORDERED_TREE_BRANCHES_FIXARRAYS
        delete [] a_;
        delete [] b_;
#endif
    }

    const ulong * length_data()  const  { return  a_ + 1; }
    const ulong * height_data()  const  { return  b_ + 1; }

    ulong num_branches()  const  {  return m_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 1;
        m_ = n_;
        for (ulong k=1; k<=n_; ++k)  b_[k] = 0;
    }

    ulong next()
    {
        ulong j = m_;
        while ( j >= 2 )
        {
            const ulong t = a_[j-1] + b_[j-1];
            const ulong bj = b_[j] + 1;
            if ( bj < t )  { b_[j] = bj;  return j; }
            b_[j] = 0;
            --j;
        }

        if ( m_ <= 1 )  return 0;  // current is last

        // next composition:
        // [*, Y, Z] --> [*, Y+1, 1, 1, 1, ..., 1]  (Z-1 trailing ones)
        a_[m_-1] += 1;
        const ulong z = a_[m_];
        a_[m_] = 1;
        // all parts a[m+1], a[m+2], ..., a[n] are already ==1
        m_ += z - 2;

        return  m_;
    }


    bool OK()  const
    {
        if ( a_[0] != 0 )  return false;
        if ( b_[0] != 0 )  return false;

        if ( ! is_composition_nz(length_data(), num_branches(), n_) )  return false;

        if ( n_ >= 2 )
            if ( b_[1] != 0 )  return false;

        for (ulong j=2; j<=num_branches(); ++j)
            if ( b_[j] >= a_[j-1] + b_[j-1] )  return false;

        return true;
    }

    void print(const char *bla)  const
    {
        print_vec(bla, length_data(), num_branches(), false);
        cout << endl;
        print_vec(bla, height_data(), num_branches(), false);
    }

    void print_level_seq(const char *bla)  const;

    void print_aa()  const;  // ASCII art
};
// -------------------------


#endif  // !defined HAVE_ORDERED_TREE_BRANCHES_H__
