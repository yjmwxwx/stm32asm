#if !defined  HAVE_PERM_REC_H__
#define       HAVE_PERM_REC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "perm/reverse.h"
//#include "perm/rotate.h"
#include "aux0/swap.h"
#include "fxttypes.h"

class perm_rec
// Permutations (and cyclic permutations).
// Recursive algorithm
{
public:
    ulong *x_;   // permutation
    ulong n_;    // number of elements
    void (*visit_)(const perm_rec &);  // function to call with each permutation

private:  // have pointer data
    perm_rec(const perm_rec&);  // forbidden
    perm_rec & operator = (const perm_rec&);  // forbidden

public:
    explicit perm_rec(ulong n)
    {
        n_ = n;
        x_ = new ulong[n_];
    }

    ~perm_rec()
    { delete [] x_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  x_[k] = k;
    }

    const ulong * data()  const  { return x_; }

    void generate(void (*visit)(const perm_rec &))
    {
        visit_ = visit;
        first();
        next_rec(0);
    }

    void generate_cyclic(void (*visit)(const perm_rec &))
    {
        visit_ = visit;
        first();
        next_cyclic_rec(0);
    }

private:
    void next_rec(ulong d)
    {
        if ( d==n_-1 )  visit_(*this);
        else
        {
            const ulong pd = x_[d];
            for (ulong k=d; k<n_; ++k)  // increasing order
//            for (ulong k=n_-1; (long)k>=(long)d; --k)  // decreasing order
            {
                ulong px = x_[k];
                x_[k] = pd;  x_[d] = px;  // =^= swap2(x_[d], x_[k]);

//                reverse(x_+d, n_-k);
//                rotate_right(x_+d, n_-d, 1);
                next_rec(d+1);
//                reverse(x_+d, n_-k);

                x_[k] = px;  x_[d] = pd;  // =^= swap2(x_[d], x_[k]);
            }
        }
    }

    void next_cyclic_rec(ulong d)
    {
        if ( d==n_-1 )  visit_(*this);
        else
        {
            const ulong pd = x_[d];
            for (ulong k=d+1; k<n_; ++k)
            {
                ulong px = x_[k];
                x_[k] = pd;  x_[d] = px;  // =^= swap2(x_[d], x_[k]);
                next_cyclic_rec(d+1);
                x_[k] = px;  x_[d] = pd;  // =^= swap2(x_[d], x_[k]);
            }
        }
    }
};
// -------------------------

#endif  // !defined HAVE_PERM_REC_H__
