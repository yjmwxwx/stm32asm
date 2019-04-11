#if !defined HAVE_COMPOSITION_NZ_SUPERDIAGONAL_H__
#define      HAVE_COMPOSITION_NZ_SUPERDIAGONAL_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_superdiagonal
// Superdiagonal compositions: compositions a[1] + a[2] + ... + a[m] = n
//   such that a[k] >= k.
// Lexicographic order.
// Same as: superdiagonal bargraphs, see
//   Emeric Deutsch, Emanuele Munarini, Simone Rinaldi:
//   "Skew Dyck paths, area, and superdiagonal bargraphs",
//   Journal of Statistical Planning and Inference,
//   vol.140, no.6, pp.1550-1562, (June-2010).
// Cf. OEIS sequence A219282.
{
public:
    ulong n_;   // composition of n
    ulong m_;   // current partition has m parts
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n

private:  // have pointer data
    composition_nz_superdiagonal(const composition_nz_superdiagonal&);  // forbidden
    composition_nz_superdiagonal & operator = (const composition_nz_superdiagonal&);  // forbidden

private:
    ulong write_tail(ulong s, ulong j)
    // Write lexicographically first partition of s,
    //   starting at index j (if s >=j, otherwise j-1).
    // Return last index written to.
    // -1 is returned for s==0.
    {
        while ( s >= j )
        {
            a_[j] = j;
            s -= j;
            ++j;
        }
        --j;
        a_[j] += s;
        return j;
    }

public:
    explicit composition_nz_superdiagonal(ulong n)
    {
        n_ = n;
        ulong s = n_,  k = 1;
        while ( s >= k )  { s -= k;  ++k; }
        a_ = new ulong[k+1];
        a_[0] = 0;  // unused
        first();
    }

    ~composition_nz_superdiagonal()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong num_parts()  const  { return m_; }

    void first()
    {
        m_ = 0;
        if ( n_!=0 )  m_ = write_tail(n_, 1);
    }

    ulong next()
    // Return number of parts of generated partition.
    // Return zero if the current is the last partition.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong z = a_[m_];
#if 0  // default off (slowdown)
        if ( z==1 )  // easy case
        {
            ++a_[m_-1];
            --m_;
            return m_;
        }
#endif
        ++a_[m_-1];
        m_ = write_tail(z-1, m_);
        return m_;
    }


    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), num_parts(), dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), m_); }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        if ( m_ > n_ )  return false;

        for (ulong j=1; j<=m_; ++j)  // a[k] >= k
            if ( a_[j] < j )  return false;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_SUPERDIAGONAL_H__
