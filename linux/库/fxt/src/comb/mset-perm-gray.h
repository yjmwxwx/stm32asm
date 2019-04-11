#if !defined  HAVE_MSET_PERM_GRAY_H__
#define       HAVE_MSET_PERM_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux0/swap.h"


class mset_perm_gray
// Multiset permutations in minimal-change order (Fred Lunnon's Gray code).
//.
// Adaptation of Java code by Fred Lunnon.
// Original documentation at end of file.
{
public:
    ulong *ms_;  // permuted elements (Lunnon's R_[])
    ulong *P_;   // permutation
    ulong *Q_;   // inverse permutation
    ulong *D_;   // direction
    ulong k_;    // number of different sorts of objects
    ulong n_;    // number of objects
    ulong sw1_, sw2_;  // positions swapped with last update
    ulong *r_;   // number of elements '1' in r[0], '2' in r[1], ..., 'k' in r[k-1]

private:  // have pointer data
    mset_perm_gray(const mset_perm_gray&);  // forbidden
    mset_perm_gray & operator = (const mset_perm_gray&);  // forbidden

public:
    explicit mset_perm_gray(const ulong *r, ulong k)
    {
        k_ = k;
        r_ = new ulong[k_];
        for (ulong j=0; j<k_; ++j)  r_[j] = r[j];
        n_ = 0;
        for (ulong j=0; j<k_; ++j)  n_ += r_[j];

        // one sentinel at index 0,
        // three sentinels at indices n+1, n+2, n+3:
        ms_ = new ulong[n_+4];
        P_ = new ulong[n_+4];
        Q_ = new ulong[n_+4];
        D_ = new ulong[n_+4];

        first();
    }

    ~mset_perm_gray()
    {
        delete [] r_;
        delete [] ms_;
        delete [] P_;
        delete [] Q_;
        delete [] D_;
    }

    const ulong * data()  const { return ms_+1; }
    void get_swaps(ulong &sw1, ulong &sw2)  const { sw1=sw1_;  sw2=sw2_; }

    void first()
    {
        sw1_ = sw2_ = 0;

        for (ulong j=0, i=1;  j<k_;  ++j)
            for (ulong h=r_[j];  h!=0;  --h, ++i)  ms_[i] = j + 1;

        const ulong n = n_;
        for (ulong j=1;  j<=n;  ++j)  { P_[j] = j;  Q_[j] = j;  D_[j] = +1UL; }

        // sentinels:
        ms_[0] = 0;  P_[0] = 0;  Q_[0] = 0;  D_[0] = 0;
        ulong j;
        j = n+1;  ms_[j] = 0;     P_[j] = 0;    Q_[j] = n+2;  D_[j] = 0;
        j = n+2;  ms_[j] = k_+1;  P_[j] = n+1;  Q_[j] = n+3;  D_[j] = +1;
        j = n+3;  ms_[j] = k_+2;  P_[j] = n+2;  Q_[j] = 0;    D_[j] = +1;
    }

    bool next()
    {
        // locate earliest unblocked element at j, starting at blocked element 0
        ulong j = 0, i = 0, d = 0, l = 0;  // init of l not needed
        while ( ms_[j] >= ms_[i] )
        {
            D_[j] = -d;  // blocked at j; reverse drift d pre-emptively

            // next element at j, neighbor at i:
            j = Q_[P_[j]+1];
            d = D_[j];
            i = j+d;

            if ( ms_[j-1] != ms_[j] )  l = j;  // save left end of run in l
            else
            {
                if ( (long)d < 0)  i = l-1;
            }
        }

        if ( j > n_ )  return false;  // current permutation is last

        // restore left end at head of run
        // shift run of equal rank from i-d,i-2d,...,l to i,i-d,...,l+d
        if ( (long)d < 0 )  l = j;
        ulong e = D_[i],  p = P_[i];  // save neighbor drift e and identifier p

        for (ulong k=i;  k!=l;  k-=d)
        {
            P_[k] = P_[k-d];
            Q_[P_[k]] = k;
            D_[k] = -1UL;  // reset drifts of run tail elements
        }

        sw1_ = i - 1;  sw2_ = l - 1;  // save positions swapped
        swap2(ms_[i], ms_[l]);

        D_[l] = e;  D_[i] = d;  // restore drifts of head and neighbor
        P_[l] = p;  Q_[p] = l;  // wrap neighbor around to other end

        return  true;
    }
};
// -------------------------

/*
Original documentation by Fred Lunnon:

 Generate bag-permutations of m elements, ordered by nearly adjacent
 transposition; generator value = m+1 on termination; assumes 0
 <= n <= m, m > 0; 4 sentinels; no pre-initialisation.

 A "run" is defined to be a sequence of equally ranked elements in
 consecutive locations (and with consecutive identifiers), such that all
 but the righthand end (highest location) are drifting right (d = +1).
 The drift of the righthand element at j determines that of the entire run.
 A run is "blocked" when the element adjacent in its direction of drift at i
 has equal or lower rank. The element adjacent to a run at its lefthand end
 is of different rank; at its righthand end may be another of equal rank.
 Generator employs Steinhaus-Johnson-Trotter adjacent transposition strategy
 to exchange the earliest (by identifier) unblocked run at j with the single
 element at i. Individual elements within a run behave as though under the
 action of a combination generator by nearly-adjacent transpositions;
 all permutations of the user bag of ranks are transpositions, most of
 which are actually adjacent.
 Once an unblocked element is found, the attached run is shifted one place
 along direction d, the end elements transposed, and all but the rightmost
 drift set leftwards; the drift of all earlier elements is reversed.
 In order to avoid unnecesary and nested loops, reversal takes place during
 search, and the left end of a run is retained in l for future reference.
 Spatial blocking sentinels ranked lowest are installed at either end, and
 temporal termination sentinels ranked highest placed off the righthand end.

 Each element has unique identifier p, lower p drifting more frequently;
 R_[k] = rank (positive integer user symbol) of element at k;
 P_[k] = identifier p of element at k, 0 <= p < m+3;
 Q_[p] = location k of element p, 0 <= k < m+3;
 D_[k] = current drift direction d of element at k, -1 <= d <= +1.
 i,j,k,l locate elements in current permutation;
 d,e = direction of element at j,i; l holds left end of current run.
 Arrays are extended by sentinels indexed 0 at left, m+1,m+2,m+3 at right;
 all subscripts run from 0 to array.length;
*/



#endif  // !defined HAVE_MSET_PERM_GRAY_H__
