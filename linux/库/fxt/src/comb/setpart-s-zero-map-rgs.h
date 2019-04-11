#if !defined  HAVE_SETPART_S_ZERO_MAP_RGS_H__
#define       HAVE_SETPART_S_ZERO_MAP_RGS_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-zero-map-rgs.h"

#include "comb/print-zero-map-rgs.h"
#include "comb/comb-print.h"

#include "fxtalloca.h"
#include "fxttypes.h"


class setpart_s_zero_map_rgs
// Set partitions into sets of size <= s+1 represented as
// restricted growth strings (RGS):
//   each digit a[k] is either zero or the (one-based) index
//   of a zero in the prefix and there are at most s digits pointing
//   to the same zero in the prefix.
// Same as: maps from {1, 2, 3, ..., n} to {0, 1, 2, 3, ..., n}
//   such that f(x) < x and f(f(x)) == 0 and there are at most s
//   values t such that f(t) = f(x).
// Lexicographic order.
// Cf. OEIS sequences A000085 (for s=1), A001680 (s=2), A001681 (s=3),
//   A110038 (s=4), and A000110 (for s>=n-1).
{
public:
    ulong *a_;  // RGS
    ulong *z_;  // for non-zero values y: number of x with f(x)=y
    ulong n_;   // length of RGS
    ulong s_;   // at most s places x with f(x)=y (y!=0) in RGS

private:  // have pointer data
    setpart_s_zero_map_rgs(const setpart_s_zero_map_rgs&);  // forbidden
    setpart_s_zero_map_rgs & operator = (const setpart_s_zero_map_rgs&);  // forbidden

public:
    explicit setpart_s_zero_map_rgs(ulong n, ulong s)
    {
        n_ = n;
        s_ = s;

        a_ = new ulong[n_+1];
        z_ = new ulong[n_+1];
        if ( n_ != 0 )
        {
            a_[0] = 0;  // unused
            z_[0] = 0;  // write-only
        }

        first();
    }

    ~setpart_s_zero_map_rgs()
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
            --z_[aj];
            while ( ++aj < j )
            {
                if ( (a_[aj] == 0) && (z_[aj] < s_) )
                {
                    a_[j] = aj;
                    ++z_[aj];
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

    void print_fp_rgs(const char *bla, bool dfz=true, bool zb=true)  const
    { print_zero_map_rgs_as_fp_rgs(bla, data(), n_, dfz, zb); }

    void print_setpart(const char *bla, bool zb=false)  const
    { print_zero_map_rgs_setpart(bla, data(), n_, zb); }


    bool OK()  const
    {
        ALLOCA(ulong, t, n_);
        return is_zero_map_rgs(data(), n_, s_, t);
    }
};
// -------------------------


#endif  // !defined HAVE_SETPART_S_ZERO_MAP_RGS_H__
