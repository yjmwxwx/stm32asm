#if !defined  HAVE_SETPART_H__
#define       HAVE_SETPART_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-setpart-rgs.h"

#include "fxttypes.h"


class setpart
// Set partitions of the set {1,2,3,...,n}
// By default in minimal-change order.
{
public:
    int n_;     // Number of elements of set (set = {1,2,3,...,n})
    int *p_;    // p[] contains set partitions of length 1,2,3,...,n
    int **pp_;  // pp[k] points to start of set partition k
    int *ns_;   // ns[k] Number of Sets in set partition k
    int *as_;   // element k attached At Set (0<=as[k]<=k) of set(k-1)
    int *d_;    // direction with recursion (+1 or -1)
    int *x_;    // current set partition (==pp[n])
    bool xdr_;  // whether to change direction in recursion (==> minimal-change order)
    int dr0_;   // dr0: starting direction in each recursive step:
    //   dr0=+1  ==> start with partition  {{1,2,3,...,n}}
    //   dr0=-1  ==> start with partition  {{1},{2},{3},...,{n}}}

private:  // have pointer data
    setpart(const setpart&);  // forbidden
    setpart & operator = (const setpart&);  // forbidden

public:
    explicit setpart(int n, bool xdr=true, int dr0=+1)
    {
        n_ = n;
        int np = (n_*(n_+1))/2;  // == \sum_{k=1}^{n}{k}
        p_ = new int[(ulong)np];  // jjcast

        const ulong n1 = (ulong)(n_+1);  // jjcast
        pp_ = new int *[n1];
        pp_[0] = 0;  // unused
        pp_[1] = p_;
        for (int k=2; k<=n_; ++k)  pp_[k] = pp_[k-1] + (k-1);

        ns_ = new int[n1];
        as_ = new int[n1];
        d_ = new int[n1];
        x_ = pp_[n_];

        first(xdr, dr0);
    }

    ~setpart()
    {
        delete [] p_;
        delete [] pp_;
        delete [] ns_;
        delete [] as_;
        delete [] d_;
    }

    void first(bool xdr, int dr0);

    bool next()  { return next_rec(n_); }

    const int* data()  const  { return x_; }


    int print()  const
    // Print current set partition
    // Return number of chars printed
    { return print_p(n_); }

    int print_p(int k)  const;
    void print_internal()  const;  // print internal state


//    bool OK()  const
//    { return is_setpart_rgs(data(), n_); }  // need ulong[]

protected:
    int cp_append(const int *src, int *dst, int k, int a);
    int next_rec(int k);
};
// -------------------------


#endif  // !defined HAVE_SETPART_H__
