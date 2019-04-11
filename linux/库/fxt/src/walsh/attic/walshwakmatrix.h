#if !defined  HAVE_WALSHWAKMATRIX_H__
#define       HAVE_WALSHWAKMATRIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux2/transpose2.h"
#include "aux0/swap.h"
#include "fxttypes.h"

template <typename Type>
void walsh_wak_matrix(Type *f, ulong ldn)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Algorithm of matrix-transform type.
{
    ulong ldc = (ldn>>1);
    ulong ldr = ldn-ldc;  // ldr>=ldc
    ulong nc = (1UL<<ldc);
    ulong nr = (1UL<<ldr);  // nrow >= ncol

    for (ulong r=0; r<nr; ++r)  walsh_wak_dif4(f+r*nc, ldc);
    transpose2(f, nr, nc);
    for (ulong c=0; c<nc; ++c)  walsh_wak_dif4(f+c*nr, ldr);
    transpose2(f, nc, nr);
}
// -------------------------

template <typename Type>
void walsh_wak_matrix_1(Type *f, ulong ldn, int is)
// Transform wrt. to Walsh-Kronecker basis (wak-functions).
// Algorithm of matrix-transform type.
// Special version for dyadic convolution.
{
    ulong ldc = (ldn>>1);
    ulong ldr = ldn-ldc;  // ldr>=ldc
    if ( is<0 )  swap2(ldr, ldc);  // inverse
    ulong nc = (1UL<<ldc);
    ulong nr = (1UL<<ldr);  // nrow >= ncol

    for (ulong r=0; r<nr; ++r)  walsh_wak_dif4(f+r*nc, ldc);
    transpose2(f, nr, nc);
    for (ulong c=0; c<nc; ++c)  walsh_wak_dif4(f+c*nr, ldr);
}
// -------------------------


#endif  // !defined HAVE_WALSHWAKMATRIX_H__
