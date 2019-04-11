#if !defined HAVE_COMPOSITION_NZ_MINC_H__
#define      HAVE_COMPOSITION_NZ_MINC_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_minc
// Compositions of n into positive parts with first part c and
//   each part <= f times its predecessor.
// For c=1 the same as: f-ary Huffman codes (canonical trees) with
//   (f-1)*n+1 terminal nodes, a[k] is the number of internal nodes of depth k.
// Such compositions (for f=2) are treated in
//   Henryk Minc: "A Problem in Partitions: Enumeration of Elements of a
//     given Degree in the free commutative entropic cyclic Groupoid",
//   Proceedings of the Edinburgh Mathematical Society (2),
//   vol.11, no.4, pp.223-224, (November-1959).
// The compositions for f=2 are also called "Cayley compositions", see
//   George E. Andrews, Peter Paule, Axel Riese, Volker Strehl:
//   "MacMahon's Partition Analysis V: Bijections, Recursions, and Magic Squares",
//   in: Algebraic Combinatorics and Applications, proceedings of Euroconference Alcoma 99,
//   September 12-19, 1999, Goessweinstein, Germany,
//   A. Betten, A. Kohnert, R. Laue, A. Wassermann eds., Springer-Verlag, pp.1-39, (2001).
// See also:
//   Christian Elsholtz, Clemens Heuberger, Helmut Prodinger:
//   "The number of Huffman codes, compact trees, and sums of unit fractions",
//   arXiv:1108.5964 [math.CO], (30-August-2011).
//
// Cf. OEIS sequences:
// f=2:  A002572 (c=1), A002573 (c=2), A002574 (c=3),
//       A049284 (c=4), A049285 (c=5).
// c=1:  A002572 (f=2), A176485 (f=3), A176503 (f=4),
//       A194628 (f=5), A194629 (f=6), A194630 (f=7),
//       A194631 (f=8), A194632 (f=9), A194633 (f=10).
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // composition of n
    ulong m_;   // current composition has m parts
    ulong f_;   // a[k] <= f * a[k-1]
    ulong c_;   // size of first part =a[1]

private:  // have pointer data
    composition_nz_minc(const composition_nz_minc&);  // forbidden
    composition_nz_minc & operator = (const composition_nz_minc&);  // forbidden

public:
    explicit composition_nz_minc(ulong n, ulong c, ulong f)
    {
        n_ = n;
        c_ = (c ? c : 1);  // disallow zero
        f_ = (f ? f : 1);  // disallow zero
        a_ = new ulong[n_+1+(n_==0)];
        a_[0] = 0;  // returned by last_part() when n==0
        if ( n_==0 )  a_[1] = 0;  // returned by first_part() when n==0
        first();
    }

    ~composition_nz_minc()
    { delete [] a_; }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }


    ulong num_parts()  const  {  return m_; }

    void first()
    {
        if ( n_ < c_ )
        {
            m_ = 0;
            return;
        }
        a_[1] = c_;
        ulong z = n_ - c_;
        for (ulong k=2; k<=n_; ++k)  a_[k] = 1;
        m_ = 1 + z;
    }


    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        ulong j = m_;
        ulong s = 0;  // sum of elements scanned over
        while ( j >= 3 )
        {
            s += a_[j];
            a_[j] = 1;
            ulong y = a_[j-1] + 1;
            ulong x = a_[j-2];
//            if ( y <= 2 * x )  // Minc (special case f==2)
            if ( y <= f_ * x )
            {
                a_[j-1] = y;
                m_ = j + s - 2;
                // all parts a[m+1], a[m+2], ..., a[n] are already ==1
                return  m_;
            }
            --j;
        }

        return  0;
    }

    bool OK()  const
    {
        if ( ! is_composition_nz(data(), num_parts(), n_) )  return false;

        if ( m_ == 0 )  return true;

        if ( a_[1] != c_ )  return false;

        for (ulong j=2; j<=m_; ++j)
            if ( a_[j] > f_ * a_[j-1] )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), m_, dfz); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), m_); }

    void print_unit_partition(const char *bla, bool dfz=false)  const;
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_MINC_H__
