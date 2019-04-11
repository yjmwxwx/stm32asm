#if !defined HAVE_TRANSPOSE_H__
#define      HAVE_TRANSPOSE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"
#include "fxttypes.h"
#include "restrict.h"
//#include "bits/bitsperlong.h"

//#include "aux0/swap.h"


template <typename Type>
void transpose_square(Type **f, ulong nrc)
// In-place transposition of an nr x nc array (nr = nc = nrc)
// that lies at nr rows of length nc
{
    const ulong nr = nrc,  nc = nrc;
    for (ulong r=0; r<nr; ++r)
    {
        for (ulong c=r+1; c<nc; ++c)
        {
            // swap2(f[r][c], f[c][r]):
            Type  t = f[r][c];
            f[r][c] = f[c][r];
            f[c][r] = t;
        }
    }
}
// -------------------------

template <typename Type>
void transpose_square(Type *f, ulong nrc)
// In-place transposition of an nr x nc array (nr = nc = nrc)
// that lies in contiguous memory
{
    const ulong nr = nrc,  nc = nrc;
    for (ulong r=0; r<nr; r++)
    {
        for (ulong c=r+1; c<nc; c++)
        {
            // swap2(f[r][c], f[c][r]):
            ulong k1 = nc * r + c;
            ulong k2 = nc * c + r;
            Type  t = f[k1];
            f[k1] = f[k2];
            f[k2] = t;
        }
    }
}
// -------------------------

template <typename Type>
void transpose(const Type * restrict f, Type * restrict g, ulong nr, ulong nc)
// Transpose nr x nc matrix f[]  into an nc x nr matrix g[].
{
    for (ulong r=0; r<nr; r++)
    {
        ulong isrc = r * nc;
        ulong idst = r;
        for (ulong c=0; c<nc; c++)
        {
            g[idst] = f[isrc];
            isrc += 1;
            idst += nr;
        }
    }
}
// -------------------------


//#define  XL unsigned long long

//#define  SRC(k)  ((k*nc)%n1)  // note: overflow if k*nc >= 2^BITS_PER_LONG
#define  SRC(k)  (((unsigned long long)(k)*nc)%n1)  // note: overflow if k*nc >= 2^64

//#define  DST(k)  (((k)*nr)%n1)


template <typename Type>
void transpose(Type *f, ulong nr, ulong nc, bitarray *B=0)
// In-place transposition of an  nr X nc  array
// that lies in contiguous memory.
//.
// Use bitarray for tagging moved elements.
{
    if ( 1>=nr )  return;
    if ( 1>=nc )  return;

    if ( nr==nc )  transpose_square(f, nr);
    else
    {
        const ulong n1 = nr * nc - 1;

        bitarray *tB = 0;
        if ( 0==B )  tB = new bitarray(n1);
        else         tB = B;
        tB->clear_all();

        for (ulong k=1;  k<n1;  k=tB->next_clear(++k) )  //  0 and n1 are fixed points
        {
            // do a cycle:
            ulong ks = SRC(k);
            ulong kd = k;
            tB->set(kd);
            Type t = f[kd];
            while ( ks != k )
            {
                f[kd] = f[ks];
                kd = ks;
                tB->set(kd);
                ks = SRC(ks);
            }
            f[kd] = t;
        }

        if ( 0==B )  delete tB;
    }
}
// -------------------------
#undef SRC
#undef DST




//#define  SRC(k)  (((k)*nc)%n1)  // note: overflow if k*nc >= 2^BITS_PER_LONG
//#define  SRC(k)  (((unsigned long long)(k)*nc)%n1)  // note: overflow if k*nc >= 2^64
//#define  DST(k)  (((k)*nr)%n1)

//template <typename Type>
//void transpose(Type *f, ulong nr, ulong nc)
//// In-place transposition of a  nr x nc  array.
//{
//    if ( 1>=nr )  return;
//    if ( 1>=nc )  return;
//
//    if ( nr==nc )
//    {
//        transpose_square(f, nr);
//        return;
//    }
//
//    const ulong n1 = nr * nc - 1;
//    unsigned ct = 2;  // count moves for better detection when finished
//    // big improvement if there are only a few cycles
//
//    for (ulong k=1; k<n1; k++)  //  0 and n1 are fixed points
//    {
//        ulong ks  = SRC(k);
//        if ( ks==k )
//        {
//            ct++;
//            continue;  // fixed point
//        }
//
//        // scan cycle:
//        while ( ks != k )
//        {
//            if ( ks<k )  goto next;  // from previous cycle
//            ks = SRC(ks);
//        }
//
//        {  // do a cycle:
//            ks = SRC(k);
//            ulong kd = k;
//            Type t = f[kd];
//            while ( ks != k )
//            {
//                ++ct;
//                f[kd] = f[ks];
//                kd = ks;
//                ks = SRC(ks);
//            }
//            ++ct;
//            f[kd] = t;
//        }
//
//        if ( ct>=n1 )  return;
//
//    next: ;
//    }
//}
//// -------------------------
//
//#undef SRC
//#undef DST


#endif  // !defined HAVE_TRANSPOSE_H__
