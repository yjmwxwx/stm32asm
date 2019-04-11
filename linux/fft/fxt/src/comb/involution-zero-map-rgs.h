#if !defined  HAVE_INVOLUTION_ZERO_MAP_RGS_H__
#define       HAVE_INVOLUTION_ZERO_MAP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-zero-map-rgs.h"

#include "comb/print-zero-map-rgs.h"
#include "comb/comb-print.h"

#include "fxtalloca.h"
#include "fxttypes.h"


class involution_zero_map_rgs
// Restricted growth strings (RGS):
//   each digit a[k] is either zero or a[k] < k, a[a[k]] == 0,
//   and there is at most one digit a[k] in the RGS.
// Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//   such that f(x) < x and f(f(x)) == 0 and there is no t!=x with f(t) = f(x).
// Lexicographic order.
// Cf. OEIS sequence A000085.
{
public:
    ulong *a_;  // RGS
    ulong *z_;  // for non-zero values y: number of x with f(x)=y
    ulong n_;   // length of RGS

private:  // have pointer data
    involution_zero_map_rgs(const involution_zero_map_rgs&);  // forbidden
    involution_zero_map_rgs & operator = (const involution_zero_map_rgs&);  // forbidden

public:
    explicit involution_zero_map_rgs(ulong n)
    {
        n_ = n;

        a_ = new ulong[n_+1];
        z_ = new ulong[n_+1];
        a_[0] = 0;  // unused
        z_[0] = 0;  // write-only

        first();
    }

    ~involution_zero_map_rgs()
    {
        delete [] a_;
        delete [] z_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        for (ulong k=1; k<=n_; ++k)  z_[k] = 0;
    }

    ulong next()
    {
        ulong j = n_;
        while ( j != 0 )
        {
            ulong aj = a_[j];
            z_[aj] = 0;
            while ( ++aj < j )
            {
                if ( (a_[aj] == 0) & (z_[aj] == 0) )
//                if ( z_[aj] == 0 )  // when z[j]!=0 also for a[j]!=0 ==> A000110
                {
                    a_[j] = aj;

                    z_[aj] = 1;

//                    z_[j] = 1;  // z[j]!=0 also for a[j]!=0

                    return j;
                }
            }
            a_[j] = 0;
//            z_[j] = 0;  // z[j]!=0 also for a[j]!=0
            --j;
        }
        return 0;  // current is last
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }

    void print_fp_rgs(const char *bla, bool dfz=true, bool zb=true)  const
    { print_zero_map_rgs_as_fp_rgs(bla, data(), n_, dfz, zb); }

    void print_fp_dist_rgs(const char *bla, bool dfz=true, bool zb=true)  const
    { print_zero_map_rgs_as_fp_dist_rgs(bla, data(), n_, dfz, zb); }

    void print_zero_dist_rgs(const char *bla, bool dfz=true)  const
    { print_zero_map_rgs_as_zero_dist_rgs(bla, data(), n_, dfz); }

    void print_involution(const char *bla, bool zb=true)  const
    { print_zero_map_rgs_setpart(bla, data(), n_, zb, true); }

    bool OK()  const
    {
//        return is_zero_map_rgs(data(), n_);  // does not check multiplicity
        ALLOCA(ulong, t, n_);
        return is_zero_map_rgs(data(), n_, 1, t);
    }
};
// -------------------------


#endif  // !defined HAVE_INVOLUTION_ZERO_MAP_RGS_H__
