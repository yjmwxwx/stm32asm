#if !defined HAVE_SHORTGRAYPERMUTE_H__
#define      HAVE_SHORTGRAYPERMUTE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


// cycles for gray_permute(), n<=64:
//
// 0000010=(  2,  3)  #1=2
//
// 0000100=(  4,  7,  5,  6)  #2=4
//
// 0001000=(  8, 15, 10, 12)  #3=4
// 0001001=(  9, 14, 11, 13)  #4=4
//
// 0010000=( 16, 31, 21, 25, 17, 30, 20, 24)  #5=8
// 0010010=( 18, 28, 23, 26, 19, 29, 22, 27)  #6=8
//
// 0100000=( 32, 63, 42, 51, 34, 60, 40, 48)  #7=8
// 0100001=( 33, 62, 43, 50, 35, 61, 41, 49)  #8=8
// 0100100=( 36, 56, 47, 53, 38, 59, 45, 54)  #9=8
// 0100101=( 37, 57, 46, 52, 39, 58, 44, 55)  #10=8


#define GP4  { Type t=f[2]; f[2]=f[3]; f[3]=t; }

#define GP8  { Type t=f[4]; f[4]=f[7]; f[7]=f[5]; f[5]=f[6]; f[6]=t; }

#define GP16 \
{ Type t=f[8]; f[8]=f[15]; f[15]=f[10]; f[10]=f[12]; f[12]=t; } \
{ Type t=f[9]; f[9]=f[14]; f[14]=f[11]; f[11]=f[13]; f[13]=t; }

#define GP32 \
{ Type t=f[16]; f[16]=f[31]; f[31]=f[21]; f[21]=f[25]; f[25]=f[17]; \
    f[17]=f[30]; f[30]=f[20]; f[20]=f[24]; f[24]=t; }               \
{ Type t=f[18]; f[18]=f[28]; f[28]=f[23]; f[23]=f[26]; f[26]=f[19]; \
    f[19]=f[29]; f[29]=f[22]; f[22]=f[27]; f[27]=t; }               \

#define GP64 \
{ Type t=f[32]; f[32]=f[63]; f[63]=f[42]; f[42]=f[51]; f[51]=f[34]; \
    f[34]=f[60]; f[60]=f[40]; f[40]=f[48]; f[48]=t; }               \
{ Type t=f[33]; f[33]=f[62]; f[62]=f[43]; f[43]=f[50]; f[50]=f[35]; \
    f[35]=f[61]; f[61]=f[41]; f[41]=f[49]; f[49]=t; }               \
{ Type t=f[36]; f[36]=f[56]; f[56]=f[47]; f[47]=f[53]; f[53]=f[38]; \
    f[38]=f[59]; f[59]=f[45]; f[45]=f[54]; f[54]=t; }               \
{ Type t=f[37]; f[37]=f[57]; f[57]=f[46]; f[46]=f[52]; f[52]=f[39]; \
    f[39]=f[58]; f[58]=f[44]; f[44]=f[55]; f[55]=t; }


template <typename Type>
inline void gray_permute_2(Type */*f*/)
// unrolled version for length 2
{
}
// -------------------------

template <typename Type>
inline void gray_permute_4(Type *f)
// unrolled version for length 4
{
    GP4;
}
// -------------------------

template <typename Type>
inline void gray_permute_8(Type *f)
// unrolled version for length 8
{
    GP4;
    GP8;
}
// -------------------------

template <typename Type>
inline void gray_permute_16(Type *f)
// unrolled version for length 16
{
    GP4;
    GP8;
    GP16;
}
// -------------------------

template <typename Type>
inline void gray_permute_32(Type *f)
// unrolled version for length 32
{
    GP4;
    GP8;
    GP16;
    GP32;
}
// -------------------------

template <typename Type>
inline void gray_permute_64(Type *f)
// unrolled version for length 64
{
    GP4;
    GP8;
    GP16;
    GP32;
    GP64;
}
// -------------------------


#undef  GP4
#undef  GP8
#undef  GP16
#undef  GP32
#undef  GP64


#define  IGP4  { Type t=f[3]; f[3]=f[2]; f[2]=t; }

#define  IGP8  { Type t=f[6]; f[6]=f[5]; f[5]=f[7]; f[7]=f[4]; f[4]=t; }

#define  IGP16 \
{ Type t=f[12]; f[12]=f[10]; f[10]=f[15]; f[15]=f[8]; f[8]=t; } \
{ Type t=f[13]; f[13]=f[11]; f[11]=f[14]; f[14]=f[9]; f[9]=t; }

#define  IGP32 \
{ Type t=f[24]; f[24]=f[20]; f[20]=f[30]; f[30]=f[17]; f[17]=f[25]; \
    f[25]=f[21]; f[21]=f[31]; f[31]=f[16]; f[16]=t; }               \
{ Type t=f[27]; f[27]=f[22]; f[22]=f[29]; f[29]=f[19]; f[19]=f[26]; \
    f[26]=f[23]; f[23]=f[28]; f[28]=f[18]; f[18]=t; }

#define  IGP64 \
{ Type t=f[48]; f[48]=f[40]; f[40]=f[60]; f[60]=f[34]; f[34]=f[51]; \
    f[51]=f[42]; f[42]=f[63]; f[63]=f[32]; f[32]=t; }               \
{ Type t=f[49]; f[49]=f[41]; f[41]=f[61]; f[61]=f[35]; f[35]=f[50]; \
    f[50]=f[43]; f[43]=f[62]; f[62]=f[33]; f[33]=t; }               \
{ Type t=f[54]; f[54]=f[45]; f[45]=f[59]; f[59]=f[38]; f[38]=f[53]; \
    f[53]=f[47]; f[47]=f[56]; f[56]=f[36]; f[36]=t; }               \
{ Type t=f[55]; f[55]=f[44]; f[44]=f[58]; f[58]=f[39]; f[39]=f[52]; \
    f[52]=f[46]; f[46]=f[57]; f[57]=f[37]; f[37]=t; }



template <typename Type>
inline void inverse_gray_permute_2(Type */*f*/)
// unrolled version for length 2
{
}
// -------------------------

template <typename Type>
inline void inverse_gray_permute_4(Type *f)
// unrolled version for length 4
{
    IGP4;
}
// -------------------------

template <typename Type>
inline void inverse_gray_permute_8(Type *f)
// unrolled version for length 8
{
    IGP4;
    IGP8;
}
// -------------------------

template <typename Type>
inline void inverse_gray_permute_16(Type *f)
// unrolled version for length 16
{
    IGP4;
    IGP8;
    IGP16;
}
// -------------------------

template <typename Type>
inline void inverse_gray_permute_32(Type *f)
// unrolled version for length 32
{
    IGP4;
    IGP8;
    IGP16;
    IGP32;
}
// -------------------------

template <typename Type>
inline void inverse_gray_permute_64(Type *f)
// unrolled version for length 64
{
    IGP4;
    IGP8;
    IGP16;
    IGP32;
    IGP64;
}
// -------------------------


#undef  IGP4
#undef  IGP8
#undef  IGP16
#undef  IGP32
#undef  IGP64


#endif  // !defined HAVE_SHORTGRAYPERMUTE_H__
