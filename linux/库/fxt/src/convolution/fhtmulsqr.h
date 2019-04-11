#if !defined HAVE_FHTMULSQR_H__
#define      HAVE_FHTMULSQR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "complextype.h"

//: Auxiliary routines for FHT based convolutions.

template <typename Type>
static inline  void fht_sqr(Type &xi, Type &xj, double v)
// xi <-- v*( 2*xi*xj + xi*xi - xj*xj )
// xj <-- v*( 2*xi*xj - xi*xi + xj*xj )
{
    Type a = xi,  b = xj;
    Type s1 = (a + b) * (a - b);
    a *= b;
    a += a;
    xi = (a+s1) * v;
    xj = (a-s1) * v;
}
// -------------------------

template <typename Type>
static inline  void fht_mul(Type xi, Type xj, Type &yi, Type &yj, double v)
// yi <-- v*( (yi + yj)*xi + (yi - yj)*xj )   == v*( (xi + xj)*yi + (xi - xj)*yj )
// yj <-- v*( (-yi + yj)*xi + (yi + yj)*xj )  == v*( (-xi + xj)*yi + (xi + xj)*yj )
{
    Type h1p = xi,  h1m = xj;
    Type s1 = h1p + h1m,  d1 = h1p - h1m;
    Type h2p = yi,  h2m = yj;
    yi = (h2p * s1 + h2m * d1) * v;
    yj = (h2m * s1 - h2p * d1) * v;
}
// -------------------------

#endif  // !defined HAVE_FHTMULSQR_H__
