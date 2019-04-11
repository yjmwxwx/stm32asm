#if !defined  HAVE_MAP23_RGS_H__
#define       HAVE_MAP23_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/comb-print.h"

#include "fxttypes.h"


class map23_rgs
// Restricted growth strings (RGS) for maps
// f: [n] -> [n] with f(x)<=x and f(f(x)) == f(f(f(x))).
// Lexicographic order.
// Cf. OEIS sequence A187761.
{
public:
    ulong *a_;  // digits of the RGS: a_[k] <= a[k-1] + 1
    ulong n_;   // Number of digits (paren pairs)

private:  // have pointer data
    map23_rgs(const map23_rgs&);  // forbidden
    map23_rgs & operator = (const map23_rgs&);  // forbidden

public:
    explicit map23_rgs(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_];
        first();
    }

    ~map23_rgs()
    { delete [] a_; }

    void first()
    { for (ulong k=0; k<n_; ++k)  a_[k] = 0; }


    ulong next()
    // Return position of leftmost change, zero with last.
    {
        ulong j = n_;
        while ( j-- != 0 )
        {
            ulong f1 = a_[j];
            while ( ++f1 <= j )
            {
                a_[j] = f1;
                ulong f2 = a_[f1];  // f(f(x))
//                ulong f2 = f1;  // f(f(x))  // ==> A000110 (Bell numbers)
                ulong f3 = a_[f2];  // f(f(f(x)))  // A187761
//                f2 = a_[f3];  // f^3 == f^4: fourth column of A179455
                if ( f2 == f3 )  return j;
            }
            a_[j] = 0;
        }

        return 0;  // current is last
    }

    const ulong *data()  const  { return a_; }

    void print(const char *bla, bool dfz=false)
    { print_vec(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_MAP23_RGS_H__
