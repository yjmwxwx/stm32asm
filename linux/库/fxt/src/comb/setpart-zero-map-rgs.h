#if !defined  HAVE_SETPART_ZERO_MAP_RGS_H__
#define       HAVE_SETPART_ZERO_MAP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-zero-map-rgs.h"

#include "comb/print-zero-map-rgs.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class setpart_zero_map_rgs
// Restricted growth strings (RGS) for set partitions:
//   each digit a[k] is either zero or a[k] < k and a[a[k]] == 0.
// Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//   such that f(x) < x and f(f(x)) == 0.
// Lexicographic order.
// Cf. OEIS sequence A000110.
{
public:
    ulong *a_;  // RGS
    ulong n_;   // length of RGS

private:  // have pointer data
    setpart_zero_map_rgs(const setpart_zero_map_rgs&);  // forbidden
    setpart_zero_map_rgs & operator = (const setpart_zero_map_rgs&);  // forbidden

public:
    explicit setpart_zero_map_rgs(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+2];
        a_[0] = 0;
        a_[n+1] = 0;  // sentinel to stop scan

        first();
    }

    ~setpart_zero_map_rgs()
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
#if 1
        ulong j = n_;
        while ( j != 0 )
        {
            ulong aj = a_[j];
            do  { ++aj; }  while ( a_[aj] != 0 );  // A000110
//            do  { ++aj; }  while ( a_[a_[aj]] != 0 );  // A000000
//            do  { ++aj; }  while ( a_[a_[a_[aj]]] != 0 );  // A000000

//            if ( aj <= j )  // A005001 sum of Bell numbers
            if ( aj < j )  // Bell numbers
            {
                a_[j] = aj;
                return j;
            }

            a_[j] = 0;
            --j;
        }

        return 0;  // current is last

#else  // slight optimization:

        ulong j = n_;
        const ulong z = a_[n_];
        if ( j<=1 )  return 0;  // current is last

        ulong aj = a_[j];
        do  { ++aj; }  while ( a_[aj] != 0 );

        if ( aj < j )  // Bell numbers
        {
            a_[j] = aj;
            return j;
        }

        // skip over identical digits:
        do  { a_[j]=0;  --j; }  while ( a_[j]==z );
        if ( j==1 )  return 0;  // current is last

        aj = a_[j];
        do  { ++aj; }  while ( a_[aj] != 0 );

        a_[j] = aj;
        return j;
#endif
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }

    void print_fp_rgs(const char *bla, bool dfz=false, bool zb=true)  const
    { print_zero_map_rgs_as_fp_rgs(bla, data(), n_, dfz, zb); }

    void print_setpart(const char *bla, bool zb=false)  const
    { print_zero_map_rgs_setpart(bla, data(), n_, zb); }


    bool OK()  const
    { return is_zero_map_rgs(data(), n_); }
};
// -------------------------


#endif  // !defined HAVE_SETPART_ZERO_MAP_RGS_H__
