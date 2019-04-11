#if !defined HAVE_SETPART_CCF_RGS_LEX_H__
#define      HAVE_SETPART_CCF_RGS_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"

#include "fxttypes.h"


class setpart_ccf_rgs_lex
// Restricted growth strings (RGS) for set partitions:
//   each digit a[k] < k and a[k-1] != 0 implies a[k] <= a[k-1].
// The RGS correspond to permutations in canonical cycle form (CCF)
//   that are valid set partitions.
// Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//   such that f(x) < x and f(x-1) != 0 implies f(x) <= f(x-1).
// Lexicographic order.
{
public:
    ulong *a_;  // RGS
    ulong n_;   // length of RGS

private:  // have pointer data
    setpart_ccf_rgs_lex(const setpart_ccf_rgs_lex&);  // forbidden
    setpart_ccf_rgs_lex & operator = (const setpart_ccf_rgs_lex&);  // forbidden

public:
    explicit setpart_ccf_rgs_lex(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+1];
        a_[0] = 0;

        first();
    }

    ~setpart_ccf_rgs_lex()
    {
        delete [] a_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
    }

    ulong next()
    {
        ulong j = n_;
        while ( j != 0 )
        {
            ulong d1 = a_[j-1];
            ulong d = a_[j] + 1;
            if ( d1 == 0 )  // f(x-1) == 0
            {
//                if ( d <= j+2 )  // A045501 (third diagonal of A121207)
//                if ( d <= j+1 )  // A040027 (second diagonal of A121207)
//                if ( d <= j )  // A000110(n+1) (first diagonal of A121207)
                if ( d < j )  // f(x) < x  // A000110(n) (first diagonal of A121207)
                {
                    a_[j] = d;
                    return j;
                }
            }
            else  // f(x-1) != 0
            {
                if ( d <= d1 )  // f(x) <= f(x-1)
                {
                    a_[j] = d;
                    return j;
                }
            }

            a_[j] = 0;
            --j;
        }

        return 0;  // current is last
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }


    bool OK()  const
    {
        // check that  a[j] <= j:
        for (ulong j=0; j<=n_; ++j)
            if ( a_[j] > j )  return false;

        // check that  a[j-1] != 0 implies a[j] <= a[j-1]:
        for (ulong j=1; j<=n_; ++j)
            if ( (a_[j-1] != 0) && (a_[j] > a_[j-1]) )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_SETPART_CCF_RGS_LEX_H__
