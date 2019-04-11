#if !defined  HAVE_SQUARE_WAVE_TRANSFORM_H__
#define       HAVE_SQUARE_WAVE_TRANSFORM_H__
// This file is part of the FXT library.
// Copyright (C) 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/sumdiff.h"  // diffsum(), sumdiff_r()
#include "fxttypes.h"

#include <cmath>  // sqrt()

//: Square wave transform

template <typename Type>
void square_wave_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis vector for the square wave transform.
// The vectors are not mutually orthogonal.
{
    const ulong nh = n / 2;
    if ( k < nh )
    {
        ++k;
        ulong j = 0;
        while ( j < k )  { f[j] = +1; ++j; }
        while ( j < k+nh )  { f[j] = -1; ++j; }
        while ( j < n )  { f[j] = +1; ++j; }
        return;
    }

    if ( k==n-1 )
    {
        for (ulong j=0; j<n; ++j)  f[j] = +1;
        return;
    }

    square_wave_basis(f, nh, k-nh);
    square_wave_basis(f+nh, nh, k-nh);
}
// -------------------------


template <typename Type>
void swt_normalize(Type *f, ulong n)
// Normalization for the square wave transform.
{
    const double s2 = sqrt(0.5);
    if ( n<=2 )
    {
        if ( n==2 )
        {
            f[n-2] *= s2;
            f[n-1] *= s2;
        }
        return;
    }

    double s = 0.5;
    for (ulong nh=n/2; nh>=4; nh/=2)
    {
        const ulong off = n - 2 * nh;
        for (ulong j=off; j<off+nh; ++j)  f[j] *= s;
        s *= s2;
    }
    f[n-4] *= s;
    f[n-3] *= s;
    f[n-2] *= s;
    f[n-1] *= s;
}
// -------------------------


template <typename Type>
void square_wave_transform(Type *f, ulong ldn, bool nq=true)
// Square wave transform.
// The transform of a delta-pulse has norm 1 (if nq==true).
// Algorithm is O(n) where n is the length of the sequence f[].
//
// This transform (with nq==false) is multiplication
// with the following matrix ('+':=+1, '-':=-1):
// (i.e., the rows are the basis functions)
//   0: [ + - - - - - - - - - - - - - - - - + + + + + + + + + + + + + + + ]
//   1: [ + + - - - - - - - - - - - - - - - - + + + + + + + + + + + + + + ]
//   2: [ + + + - - - - - - - - - - - - - - - - + + + + + + + + + + + + + ]
//   3: [ + + + + - - - - - - - - - - - - - - - - + + + + + + + + + + + + ]
//   4: [ + + + + + - - - - - - - - - - - - - - - - + + + + + + + + + + + ]
//   5: [ + + + + + + - - - - - - - - - - - - - - - - + + + + + + + + + + ]
//   6: [ + + + + + + + - - - - - - - - - - - - - - - - + + + + + + + + + ]
//   7: [ + + + + + + + + - - - - - - - - - - - - - - - - + + + + + + + + ]
//   8: [ + + + + + + + + + - - - - - - - - - - - - - - - - + + + + + + + ]
//   9: [ + + + + + + + + + + - - - - - - - - - - - - - - - - + + + + + + ]
//  10: [ + + + + + + + + + + + - - - - - - - - - - - - - - - - + + + + + ]
//  11: [ + + + + + + + + + + + + - - - - - - - - - - - - - - - - + + + + ]
//  12: [ + + + + + + + + + + + + + - - - - - - - - - - - - - - - - + + + ]
//  13: [ + + + + + + + + + + + + + + - - - - - - - - - - - - - - - - + + ]
//  14: [ + + + + + + + + + + + + + + + - - - - - - - - - - - - - - - - + ]
//  15: [ + + + + + + + + + + + + + + + + - - - - - - - - - - - - - - - - ]
//  16: [ + - - - - - - - - + + + + + + + + - - - - - - - - + + + + + + + ]
//  17: [ + + - - - - - - - - + + + + + + + + - - - - - - - - + + + + + + ]
//  18: [ + + + - - - - - - - - + + + + + + + + - - - - - - - - + + + + + ]
//  19: [ + + + + - - - - - - - - + + + + + + + + - - - - - - - - + + + + ]
//  20: [ + + + + + - - - - - - - - + + + + + + + + - - - - - - - - + + + ]
//  21: [ + + + + + + - - - - - - - - + + + + + + + + - - - - - - - - + + ]
//  22: [ + + + + + + + - - - - - - - - + + + + + + + + - - - - - - - - + ]
//  23: [ + + + + + + + + - - - - - - - - + + + + + + + + - - - - - - - - ]
//  24: [ + - - - - + + + + - - - - + + + + - - - - + + + + - - - - + + + ]
//  25: [ + + - - - - + + + + - - - - + + + + - - - - + + + + - - - - + + ]
//  26: [ + + + - - - - + + + + - - - - + + + + - - - - + + + + - - - - + ]
//  27: [ + + + + - - - - + + + + - - - - + + + + - - - - + + + + - - - - ]
//  28: [ + - - + + - - + + - - + + - - + + - - + + - - + + - - + + - - + ]
//  29: [ + + - - + + - - + + - - + + - - + + - - + + - - + + - - + + - - ]
//  30: [ + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - + - ]
//  31: [ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + ]
// If nq==true then norm of all row vectors is sqrt(n).
// If nq==true then the norm of the row vectors is
//  sqrt(1) for the last 4,  sqrt(2) for the prior 4 (again 4),
//  sqrt(4) for the prior 8,  sqrt(8) for the prior 16,
//  sqrt(16) for the prior 32,  etc.
{
    const ulong n = 1UL << ldn;
    if ( n<=2 )
    {
        if ( n==2 )
        {
            diffsum(f[n-2], f[n-1]);
            if ( nq )  swt_normalize(f, n);
        }
        return;
    }

    // first pass: diffsum of halves
    ulong nh = n / 2;
    for (ulong j=0; j<nh; ++j)  diffsum(f[j], f[nh+j]);

    ulong off = 0;
    // remaining passes: cyclic diff left, diffsum right
    while ( nh >= 4 )
    {
        // cyclic differences left:
        const Type t = f[off];  // will be added to last
        for (ulong j=off; j<off+nh-1; ++j)  f[j] -= f[j+1];
        f[off+nh-1] += t;

        // diffsum right:
        ulong n4 = nh / 2;
        for (ulong j=off+nh; j<off+nh+n4; ++j)  diffsum(f[j], f[n4+j]);

        off += nh;
        nh /= 2;
    }

    diffsum(f[n-4], f[n-3]);
    diffsum(f[n-2], f[n-1]);

    if ( nq )  swt_normalize(f, n);
}
// -------------------------


template <typename Type>
void inverse_square_wave_transform(Type *f, ulong ldn, bool nq=true)
// Inverse of the square wave transform (if nq==true in both transforms).
// Algorithm is O(n) where n is the length of the sequence f[].
//
// This transform (with nq==false) is multiplication
// with the following matrix ('+':=+1, '-':=-1, ' ':=0):
//
//   0: [ +                             + +             + +     + + + + + ]
//   1: [ - +                             - +             - +     - + - + ]
//   2: [   - +                             - +             - +   - - + + ]
//   3: [     - +                             - +             - + + - - + ]
//   4: [       - +                             - +       -     - + + + + ]
//   5: [         - +                             - +     + -     - + - + ]
//   6: [           - +                             - +     + -   - - + + ]
//   7: [             - +                             - +     + - + - - + ]
//   8: [               - +               -             - +     + + + + + ]
//   9: [                 - +             + -             - +     - + - + ]
//  10: [                   - +             + -             - +   - - + + ]
//  11: [                     - +             + -             - + + - - + ]
//  12: [                       - +             + -       -     - + + + + ]
//  13: [                         - +             + -     + -     - + - + ]
//  14: [                           - +             + -     + -   - - + + ]
//  15: [                             - +             + -     + - + - - + ]
//  16: [ -                             - +             + +     + + + + + ]
//  17: [ + -                             - +             - +     - + - + ]
//  18: [   + -                             - +             - +   - - + + ]
//  19: [     + -                             - +             - + + - - + ]
//  20: [       + -                             - +       -     - + + + + ]
//  21: [         + -                             - +     + -     - + - + ]
//  22: [           + -                             - +     + -   - - + + ]
//  23: [             + -                             - +     + - + - - + ]
//  24: [               + -               -             - +     + + + + + ]
//  25: [                 + -             + -             - +     - + - + ]
//  26: [                   + -             + -             - +   - - + + ]
//  27: [                     + -             + -             - + + - - + ]
//  28: [                       + -             + -       -     - + + + + ]
//  29: [                         + -             + -     + -     - + - + ]
//  30: [                           + -             + -     + -   - - + + ]
//  31: [                             + -             + -     + - + - - + ]
// If nq==false then the norm all row vectors is sqrt(2*n).  (?? to check)
// If nq==true then the norm all row vectors is 1.
//
{
    const ulong n = 1UL << ldn;
    if ( n<=2 )
    {
        if ( n==2 )
        {
            sumdiff_r(f[n-2], f[n-1]);
            if ( nq )  swt_normalize(f, n);
        }
        return;
    }

    if ( nq )  swt_normalize(f, n);


    sumdiff_r(f[n-4], f[n-3]);
    sumdiff_r(f[n-2], f[n-1]);

    // first passes: inverse cyclic differences left, diffsum right
    for (ulong nh=4; nh < n; nh*=2 )
    {
        ulong off = n - 2 * nh;

        // inverse cyclic differences left:
        Type s = 0;
        for (ulong j=off; j<off+nh; ++j)  s += f[j];
        for (ulong j=off; j<off+nh; ++j)
        {
            Type d = f[j];
            f[j] = s;
            s -= (d + d);
        }

        // inverse diffsum right:
        ulong n4 = nh / 2;
        for (ulong j=off+nh; j<off+nh+n4; ++j)  sumdiff_r(f[j], f[n4+j]);
    }

    // last pass: inverse diffsum of halves
    ulong nh = n >> 1;
    for (ulong j=0; j<nh; ++j)  sumdiff_r(f[j], f[nh+j]);
}
// -------------------------


#endif  // !defined HAVE_SQUARE_WAVE_TRANSFORM_H__
