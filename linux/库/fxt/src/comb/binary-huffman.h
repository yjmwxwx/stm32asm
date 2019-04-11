#if !defined HAVE_BINARY_HUFFMAN_H__
#define      HAVE_BINARY_HUFFMAN_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/comb-print.h"

#include "fxttypes.h"


class binary_huffman
// Partitions of 1 into n powers of 1/2:
//   1 == a[0]/1 + a[1]/2 + a[2]/4 + a[3]/8 + ... a[m]/(2^m)  (for n>=1),
//   n == a[0] + a[1] + a[2] + a[3] + ... + a[m].
// Same as: binary Huffman codes (canonical trees) with n terminal nodes,
//   a[k] is the number of terminal nodes of depth k.
// Reversed lexicographic order.
// See:
//   Christian Elsholtz, Clemens Heuberger, Helmut Prodinger:
//   "The number of Huffman codes, compact trees, and sums of unit fractions",
//   arXiv:1108.5964 [math.CO], (30-August-2011).
//
// Cf. OEIS sequence A002572.
{
public:
    ulong *a_;  // partition:
    // 1 == a[0]/1 + a[1]/2 + a[2]/4 + a[3]/8 + ... a[m]/(2^m)  (for n>=1)
    // n == a[0] + a[1] + a[2] + a[3] + ... + a[m]
    ulong n_;   // partitions into n parts
    ulong m_;   // last nonzero position (m==0 for n==0)

private:  // have pointer data
    binary_huffman(const binary_huffman&);  // forbidden
    binary_huffman & operator = (const binary_huffman&);  // forbidden

public:
    explicit binary_huffman(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+(n_==0)];
        a_[0] = 0;
        first();
    }

    ~binary_huffman()
    { delete [] a_; }

    const ulong * data()  const  { return  a_; }

private:
    ulong write_tail(ulong s, ulong j)
    // Write [ *, 1, 1, 1, 2], starting with position j.
    // Return last position written to.
    // Undefined for s==0.
    {
        while ( s > 2 )
        {
            a_[j] = 1;
            --s;
            ++j;
        }
        a_[j] = s;
        return j;
    }

public:
    void first()
    {
        for (ulong j=0; j<n_; ++j)  a_[j] = 0;
        if ( n_ <= 1 )
        {
            m_ = 0;  // for n==0 we have one part ==0
            a_[0] = n_;
        }
        else
        {
            m_ = write_tail(n_, 1);
        }
    }


    ulong next()
    // Return number of parts of generated composition.
    // Return zero if the current is the last composition.
    {
        ulong j = m_;

        ulong s = 0;  // sum of elements scanned over
        ulong w = 0;  // weighted sum (increment)
        while ( j >= 3 )
        {
            ulong z = a_[j];

            w += z;
            w >>= 1;

            s += z;

            if ( a_[j-2] != 0 )
            {
                --a_[j-2];  // borrow from left

                ulong i = w + (w==1);
                a_[j-1] += i + 1;  // +1 borrowed from left
                a_[j] = z - i;
                s -= i;

                if ( s == 0 )
                {
                    --m_;
                    return  m_;
                }
                else
                {
                    m_ = write_tail(s, j);
                    return  m_;
                }
            }

            a_[j] = 0;
            --j;
        }

        return  0;
    }

    bool OK()  const
    {

        if ( m_ == 0 )  return true;
        if ( m_ > n_ )  return false;

        ulong s = 0;  // check that sum is n
        for (ulong j=0; j<=m_; ++j)  s += a_[j];
        if ( s != n_ )  return false;

        // check that sum of fractions is 1:
        double s1 = 0.0, p2 = 1.0;
        for (ulong j=0; j<=m_; ++j)
        {
            s1 += p2 * (double)a_[j];
            p2 *= 0.5;
        }
        s1 -= 1.0;
        if ( s1 < 0.0 )  s1 = -s1;
        if ( s1 > 1e-11 )  return false;

        return true;
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), n_, dfz); }

    void print_unit_sum(const char *bla)  const;
};
// -------------------------


#endif  // !defined HAVE_BINARY_HUFFMAN_H__
