#if !defined  HAVE_SHORTWALSHWAKDIF_H__
#define       HAVE_SHORTWALSHWAKDIF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/sumdiff.h"
#include "fxttypes.h"

//: walsh_wak_dif() for fixed array sizes

template <typename Type>
static inline void short_walsh_wak_dif_2(Type *f)
{
    sumdiff( f[0], f[1] );
}
// -------------------------

template <typename Type>
static inline void short_walsh_wak_dif_2(Type *f, ulong s)
{
    sumdiff( f[0], f[s] );
}
// -------------------------


template <typename Type>
static inline void short_walsh_wak_dif_4(Type *f)
{
    Type t0, t1, t2, t3;
    t0 = f[0];
    t1 = f[1];
    t2 = f[2];
    t3 = f[3];
    sumdiff( t0, t2 );
    sumdiff( t1, t3 );
    sumdiff( t0, t1 );
    sumdiff( t2, t3 );
    f[0] = t0;
    f[1] = t1;
    f[2] = t2;
    f[3] = t3;
}
// -------------------------

template <typename Type>
static inline void short_walsh_wak_dif_4(Type *f, ulong s)
{
    Type t0, t1, t2, t3;
    {
        ulong x = 0;
        t0 = f[x];  x += s;
        t1 = f[x];  x += s;
        t2 = f[x];  x += s;
        t3 = f[x];
    }
    sumdiff( t0, t2 );
    sumdiff( t1, t3 );
    sumdiff( t0, t1 );
    sumdiff( t2, t3 );
    {
        ulong x = 0;
        f[x] = t0;  x += s;
        f[x] = t1;  x += s;
        f[x] = t2;  x += s;
        f[x] = t3;
    }
}
// -------------------------


template <typename Type>
inline void short_walsh_wak_dif_8(Type *f)
{
    Type t0, t1, t2, t3, t4, t5, t6, t7;
    t0 = f[0];
    t1 = f[1];
    t2 = f[2];
    t3 = f[3];
    t4 = f[4];
    t5 = f[5];
    t6 = f[6];
    t7 = f[7];
    sumdiff( t0, t4 );
    sumdiff( t1, t5 );
    sumdiff( t2, t6 );
    sumdiff( t3, t7 );
    sumdiff( t0, t2 );
    sumdiff( t1, t3 );
    sumdiff( t4, t6 );
    sumdiff( t5, t7 );
    sumdiff( t0, t1 );
    sumdiff( t2, t3 );
    sumdiff( t4, t5 );
    sumdiff( t6, t7 );
    f[0] = t0;
    f[1] = t1;
    f[2] = t2;
    f[3] = t3;
    f[4] = t4;
    f[5] = t5;
    f[6] = t6;
    f[7] = t7;
}
// -------------------------


template <typename Type>
inline void short_walsh_wak_dif_8(Type *f, ulong s)
{
    Type t0, t1, t2, t3, t4, t5, t6, t7;
    {
        ulong x = 0;
        t0 = f[x];  x += s;
        t1 = f[x];  x += s;
        t2 = f[x];  x += s;
        t3 = f[x];  x += s;
        t4 = f[x];  x += s;
        t5 = f[x];  x += s;
        t6 = f[x];  x += s;
        t7 = f[x];
    }
    sumdiff( t0, t4 );
    sumdiff( t1, t5 );
    sumdiff( t2, t6 );
    sumdiff( t3, t7 );
    sumdiff( t0, t2 );
    sumdiff( t1, t3 );
    sumdiff( t4, t6 );
    sumdiff( t5, t7 );
    sumdiff( t0, t1 );
    sumdiff( t2, t3 );
    sumdiff( t4, t5 );
    sumdiff( t6, t7 );
    {
        ulong x = 0;
        f[x] = t0;  x += s;
        f[x] = t1;  x += s;
        f[x] = t2;  x += s;
        f[x] = t3;  x += s;
        f[x] = t4;  x += s;
        f[x] = t5;  x += s;
        f[x] = t6;  x += s;
        f[x] = t7;
    }
}
// -------------------------


template <typename Type>
inline void short_walsh_wak_dif_16(Type *f)
{
    Type t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;
    t0 = f[0];
    t1 = f[1];
    t2 = f[2];
    t3 = f[3];
    t4 = f[4];
    t5 = f[5];
    t6 = f[6];
    t7 = f[7];
    t8 = f[8];
    t9 = f[9];
    t10 = f[10];
    t11 = f[11];
    t12 = f[12];
    t13 = f[13];
    t14 = f[14];
    t15 = f[15];
    sumdiff( t0, t8 );
    sumdiff( t1, t9 );
    sumdiff( t2, t10 );
    sumdiff( t3, t11 );
    sumdiff( t4, t12 );
    sumdiff( t5, t13 );
    sumdiff( t6, t14 );
    sumdiff( t7, t15 );
    sumdiff( t0, t4 );
    sumdiff( t1, t5 );
    sumdiff( t2, t6 );
    sumdiff( t3, t7 );
    sumdiff( t8, t12 );
    sumdiff( t9, t13 );
    sumdiff( t10, t14 );
    sumdiff( t11, t15 );
    sumdiff( t0, t2 );
    sumdiff( t1, t3 );
    sumdiff( t4, t6 );
    sumdiff( t5, t7 );
    sumdiff( t8, t10 );
    sumdiff( t9, t11 );
    sumdiff( t12, t14 );
    sumdiff( t13, t15 );
    sumdiff( t0, t1 );
    sumdiff( t2, t3 );
    sumdiff( t4, t5 );
    sumdiff( t6, t7 );
    sumdiff( t8, t9 );
    sumdiff( t10, t11 );
    sumdiff( t12, t13 );
    sumdiff( t14, t15 );
    f[0] = t0;
    f[1] = t1;
    f[2] = t2;
    f[3] = t3;
    f[4] = t4;
    f[5] = t5;
    f[6] = t6;
    f[7] = t7;
    f[8] = t8;
    f[9] = t9;
    f[10] = t10;
    f[11] = t11;
    f[12] = t12;
    f[13] = t13;
    f[14] = t14;
    f[15] = t15;
}
// -------------------------


template <typename Type>
inline void short_walsh_wak_dif_16(Type *f, ulong s)
{
    Type t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;
    {
        ulong x = 0;
        t0 = f[x];  x += s;
        t1 = f[x];  x += s;
        t2 = f[x];  x += s;
        t3 = f[x];  x += s;
        t4 = f[x];  x += s;
        t5 = f[x];  x += s;
        t6 = f[x];  x += s;
        t7 = f[x];  x += s;
        t8 = f[x];  x += s;
        t9 = f[x];  x += s;
        t10 = f[x];  x += s;
        t11 = f[x];  x += s;
        t12 = f[x];  x += s;
        t13 = f[x];  x += s;
        t14 = f[x];  x += s;
        t15 = f[x];
    }
    sumdiff( t0, t8 );
    sumdiff( t1, t9 );
    sumdiff( t2, t10 );
    sumdiff( t3, t11 );
    sumdiff( t4, t12 );
    sumdiff( t5, t13 );
    sumdiff( t6, t14 );
    sumdiff( t7, t15 );
    sumdiff( t0, t4 );
    sumdiff( t1, t5 );
    sumdiff( t2, t6 );
    sumdiff( t3, t7 );
    sumdiff( t8, t12 );
    sumdiff( t9, t13 );
    sumdiff( t10, t14 );
    sumdiff( t11, t15 );
    sumdiff( t0, t2 );
    sumdiff( t1, t3 );
    sumdiff( t4, t6 );
    sumdiff( t5, t7 );
    sumdiff( t8, t10 );
    sumdiff( t9, t11 );
    sumdiff( t12, t14 );
    sumdiff( t13, t15 );
    sumdiff( t0, t1 );
    sumdiff( t2, t3 );
    sumdiff( t4, t5 );
    sumdiff( t6, t7 );
    sumdiff( t8, t9 );
    sumdiff( t10, t11 );
    sumdiff( t12, t13 );
    sumdiff( t14, t15 );
    {
        ulong x = 0;
        f[x] = t0;  x += s;
        f[x] = t1;  x += s;
        f[x] = t2;  x += s;
        f[x] = t3;  x += s;
        f[x] = t4;  x += s;
        f[x] = t5;  x += s;
        f[x] = t6;  x += s;
        f[x] = t7;  x += s;
        f[x] = t8;  x += s;
        f[x] = t9;  x += s;
        f[x] = t10;  x += s;
        f[x] = t11;  x += s;
        f[x] = t12;  x += s;
        f[x] = t13;  x += s;
        f[x] = t14;  x += s;
        f[x] = t15;
    }
}
// -------------------------


#endif  // !defined HAVE_SHORTWALSHWAKDIF_H__
