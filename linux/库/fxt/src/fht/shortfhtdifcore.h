#if !defined HAVE_SHORTFHTDIFCORE_H__
#define      HAVE_SHORTFHTDIFCORE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "aux0/sumdiff.h"
#include "aux0/constants.h"
#include "aux0/cmult.h"
//#include "cmath.h"

template <typename Type>
inline void fht_dif_core_2(Type *f)
// unrolled version for length 2
{
    sumdiff(f[0], f[1]);
}
// -------------------------
// opcount by generator:  #mult=0=0/pt   #add=2=1/pt

template <typename Type>
inline void fht_dif_core_4(Type *f)
// unrolled version for length 4
{
    {  // start initial loop
        {  // fi = 0
            Type f0, f1, f2, f3;
            sumdiff(f[0], f[2], f0, f1);
            sumdiff(f[1], f[3], f2, f3);
            sumdiff(f0, f2, f[0], f[1]);
            sumdiff(f1, f3, f[2], f[3]);
        }
    }  // end initial loop
}
// -------------------------
// opcount by generator:  #mult=0=0/pt   #add=8=2/pt

template <typename Type>
inline void fht_dif_core_8(Type *f)
// unrolled version for length 8
{
    {  // start initial loop
        {  // fi = 0  gi = 1
            Type g0, f0, f1, g1;
            sumdiff(f[0], f[4], f0, g0);
            sumdiff(f[2], f[6], f1, g1);
            sumdiff(f0, f1);
            sumdiff(g0, g1);
            Type s1, c1, s2, c2;
            sumdiff(f[1], f[5], s1, c1);
            sumdiff(f[3], f[7], s2, c2);
            sumdiff(s1, s2);
            sumdiff(f0, s1, f[0], f[1]);
            sumdiff(f1, s2, f[2], f[3]);
            c1 *= SQRT2;
            c2 *= SQRT2;
            sumdiff(g0, c1, f[4], f[5]);
            sumdiff(g1, c2, f[6], f[7]);
        }
    }  // end initial loop
}
// -------------------------
// opcount by generator:  #mult=2=0.25/pt   #add=22=2.75/pt

template <typename Type>
inline void fht_dif_core_16(Type *f)
// unrolled version for length 16
{
    {  // start initial loop
        {  // fi = 0
            Type f0, f1, f2, f3;
            sumdiff(f[0], f[8], f0, f1);
            sumdiff(f[4], f[12], f2, f3);
            sumdiff(f0, f2, f[0], f[4]);
            sumdiff(f1, f3, f[8], f[12]);
        }
        {  // fi = 4
            Type f0, f1, f2, f3;
            sumdiff(f[2], f[10], f0, f1);
            sumdiff(f[6], f[14], f2, f3);
            sumdiff(f0, f2, f[2], f[6]);
            sumdiff(f1, f3, f[10], f[14]);
        }
        {  // fi = 8
            Type f0, f1, f2, f3;
            sumdiff(f[1], f[9], f0, f1);
            sumdiff(f[5], f[13], f2, f3);
            sumdiff(f0, f2, f[1], f[5]);
            sumdiff(f1, f3, f[9], f[13]);
        }
        {  // fi = 12
            Type f0, f1, f2, f3;
            sumdiff(f[3], f[11], f0, f1);
            sumdiff(f[7], f[15], f2, f3);
            sumdiff(f0, f2, f[3], f[7]);
            sumdiff(f1, f3, f[11], f[15]);
        }
    }  // end initial loop

    {  // -------- ldk=2  k4=16
        Type f0, f1, f2, f3;
        // do loop:
        sumdiff(f[0], f[2], f0, f1);
        sumdiff(f[1], f[3], f2, f3);
        sumdiff(f0, f2, f[0], f[1]);
        sumdiff(f1, f3, f[2], f[3]);
        sumdiff(f[4], f[6], f0, f1);
        f3 = SQRT2 * f[7];
        f2 = SQRT2 * f[5];
        sumdiff(f0, f2, f[4], f[5]);
        sumdiff(f1, f3, f[6], f[7]);
    }

    {  // kh=2
        Type a, b, g0, f0, f1, g1, f2, g2, f3, g3;
        {  // ---- i=1
            double c1=.923879532511286756128183189397;  // == cos(Pi*1/8) == cos(Pi*1/8)
            double s1=.382683432365089771728459984029;  // == sin(Pi*1/8) == sin(Pi*1/8)
            // c2 = s2 = sqrt(1/2)
            // do loop II:
            sumdiff(f[10], f[14], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[8], a, f0, f1);
            sumdiff(f[12], b, g0, g1);
            sumdiff(f[11], f[15], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[9], a, f2, f3);
            sumdiff(f[13], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[8], f[9]);
            sumdiff(g1, b, f[14], f[15]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[12], f[13]);
            sumdiff(f1, b, f[10], f[11]);
        }
    }
}
// -------------------------
// opcount by generator:  #mult=14=0.875/pt   #add=70=4.375/pt

template <typename Type>
inline void fht_dif_core_32(Type *f)
// unrolled version for length 32
{
    {  // start initial loop
        {  // fi = 0  gi = 1
            Type g0, f0, f1, g1;
            sumdiff(f[0], f[16], f0, g0);
            sumdiff(f[8], f[24], f1, g1);
            sumdiff(f0, f1);
            sumdiff(g0, g1);
            Type s1, c1, s2, c2;
            sumdiff(f[4], f[20], s1, c1);
            sumdiff(f[12], f[28], s2, c2);
            sumdiff(s1, s2);
            sumdiff(f0, s1, f[0], f[4]);
            sumdiff(f1, s2, f[8], f[12]);
            c1 *= SQRT2;
            c2 *= SQRT2;
            sumdiff(g0, c1, f[16], f[20]);
            sumdiff(g1, c2, f[24], f[28]);
        }
        {  // fi = 8  gi = 9
            Type g0, f0, f1, g1;
            sumdiff(f[2], f[18], f0, g0);
            sumdiff(f[10], f[26], f1, g1);
            sumdiff(f0, f1);
            sumdiff(g0, g1);
            Type s1, c1, s2, c2;
            sumdiff(f[6], f[22], s1, c1);
            sumdiff(f[14], f[30], s2, c2);
            sumdiff(s1, s2);
            sumdiff(f0, s1, f[2], f[6]);
            sumdiff(f1, s2, f[10], f[14]);
            c1 *= SQRT2;
            c2 *= SQRT2;
            sumdiff(g0, c1, f[18], f[22]);
            sumdiff(g1, c2, f[26], f[30]);
        }
        {  // fi = 16  gi = 17
            Type g0, f0, f1, g1;
            sumdiff(f[1], f[17], f0, g0);
            sumdiff(f[9], f[25], f1, g1);
            sumdiff(f0, f1);
            sumdiff(g0, g1);
            Type s1, c1, s2, c2;
            sumdiff(f[5], f[21], s1, c1);
            sumdiff(f[13], f[29], s2, c2);
            sumdiff(s1, s2);
            sumdiff(f0, s1, f[1], f[5]);
            sumdiff(f1, s2, f[9], f[13]);
            c1 *= SQRT2;
            c2 *= SQRT2;
            sumdiff(g0, c1, f[17], f[21]);
            sumdiff(g1, c2, f[25], f[29]);
        }
        {  // fi = 24  gi = 25
            Type g0, f0, f1, g1;
            sumdiff(f[3], f[19], f0, g0);
            sumdiff(f[11], f[27], f1, g1);
            sumdiff(f0, f1);
            sumdiff(g0, g1);
            Type s1, c1, s2, c2;
            sumdiff(f[7], f[23], s1, c1);
            sumdiff(f[15], f[31], s2, c2);
            sumdiff(s1, s2);
            sumdiff(f0, s1, f[3], f[7]);
            sumdiff(f1, s2, f[11], f[15]);
            c1 *= SQRT2;
            c2 *= SQRT2;
            sumdiff(g0, c1, f[19], f[23]);
            sumdiff(g1, c2, f[27], f[31]);
        }
    }  // end initial loop

    {  // -------- ldk=3  k4=32
        Type f0, f1, f2, f3;
        // do loop:
        sumdiff(f[0], f[2], f0, f1);
        sumdiff(f[1], f[3], f2, f3);
        sumdiff(f0, f2, f[0], f[1]);
        sumdiff(f1, f3, f[2], f[3]);
        sumdiff(f[4], f[6], f0, f1);
        f3 = SQRT2 * f[7];
        f2 = SQRT2 * f[5];
        sumdiff(f0, f2, f[4], f[5]);
        sumdiff(f1, f3, f[6], f[7]);
    }

    {  // kh=4
        Type a, b, g0, f0, f1, g1, f2, g2, f3, g3;
        {  // ---- i=1
            double c1=.980785280403230449126182236134;  // == cos(Pi*1/16) == cos(Pi*1/16)
            double s1=.195090322016128267848284868476;  // == sin(Pi*1/16) == sin(Pi*1/16)
            double c2=.923879532511286756128183189397;  // == cos(Pi*2/16) == cos(Pi*1/8)
            double s2=.382683432365089771728459984029;  // == sin(Pi*2/16) == sin(Pi*1/8)
            // do loop II:
            cmult(s2, c2, f[18], f[30], b, a);
            sumdiff(f[16], a, f0, f1);
            sumdiff(f[28], b, g0, g1);
            cmult(s2, c2, f[19], f[31], b, a);
            sumdiff(f[17], a, f2, f3);
            sumdiff(f[29], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[16], f[17]);
            sumdiff(g1, b, f[30], f[31]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[28], f[29]);
            sumdiff(f1, b, f[18], f[19]);
        }
        {  // ---- i=2
            double c1=.923879532511286756128183189397;  // == cos(Pi*2/16) == cos(Pi*1/8)
            double s1=.382683432365089771728459984029;  // == sin(Pi*2/16) == sin(Pi*1/8)
            // c2 = s2 = sqrt(1/2)
            // do loop II:
            sumdiff(f[10], f[14], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[8], a, f0, f1);
            sumdiff(f[12], b, g0, g1);
            sumdiff(f[11], f[15], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[9], a, f2, f3);
            sumdiff(f[13], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[8], f[9]);
            sumdiff(g1, b, f[14], f[15]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[12], f[13]);
            sumdiff(f1, b, f[10], f[11]);
        }
        {  // ---- i=3
            double c1=.831469612302545237078788377618;  // == cos(Pi*3/16) == cos(Pi*3/16)
            double s1=.555570233019602224742830813947;  // == sin(Pi*3/16) == sin(Pi*3/16)
            double c2=.382683432365089771728459984032;  // == cos(Pi*6/16) == cos(Pi*3/8)
            double s2=.923879532511286756128183189396;  // == sin(Pi*6/16) == sin(Pi*3/8)
            // do loop II:
            cmult(s2, c2, f[26], f[22], b, a);
            sumdiff(f[24], a, f0, f1);
            sumdiff(f[20], b, g0, g1);
            cmult(s2, c2, f[27], f[23], b, a);
            sumdiff(f[25], a, f2, f3);
            sumdiff(f[21], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[24], f[25]);
            sumdiff(g1, b, f[22], f[23]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[20], f[21]);
            sumdiff(f1, b, f[26], f[27]);
        }
    }
}
// -------------------------
// opcount by generator:  #mult=54=1.6875/pt   #add=174=5.4375/pt

template <typename Type>
inline void fht_dif_core_64(Type *f)
// unrolled version for length 64
{
    {  // start initial loop
        {  // fi = 0
            Type f0, f1, f2, f3;
            sumdiff(f[0], f[32], f0, f1);
            sumdiff(f[16], f[48], f2, f3);
            sumdiff(f0, f2, f[0], f[16]);
            sumdiff(f1, f3, f[32], f[48]);
        }
        {  // fi = 4
            Type f0, f1, f2, f3;
            sumdiff(f[8], f[40], f0, f1);
            sumdiff(f[24], f[56], f2, f3);
            sumdiff(f0, f2, f[8], f[24]);
            sumdiff(f1, f3, f[40], f[56]);
        }
        {  // fi = 8
            Type f0, f1, f2, f3;
            sumdiff(f[4], f[36], f0, f1);
            sumdiff(f[20], f[52], f2, f3);
            sumdiff(f0, f2, f[4], f[20]);
            sumdiff(f1, f3, f[36], f[52]);
        }
        {  // fi = 12
            Type f0, f1, f2, f3;
            sumdiff(f[12], f[44], f0, f1);
            sumdiff(f[28], f[60], f2, f3);
            sumdiff(f0, f2, f[12], f[28]);
            sumdiff(f1, f3, f[44], f[60]);
        }
        {  // fi = 16
            Type f0, f1, f2, f3;
            sumdiff(f[2], f[34], f0, f1);
            sumdiff(f[18], f[50], f2, f3);
            sumdiff(f0, f2, f[2], f[18]);
            sumdiff(f1, f3, f[34], f[50]);
        }
        {  // fi = 20
            Type f0, f1, f2, f3;
            sumdiff(f[10], f[42], f0, f1);
            sumdiff(f[26], f[58], f2, f3);
            sumdiff(f0, f2, f[10], f[26]);
            sumdiff(f1, f3, f[42], f[58]);
        }
        {  // fi = 24
            Type f0, f1, f2, f3;
            sumdiff(f[6], f[38], f0, f1);
            sumdiff(f[22], f[54], f2, f3);
            sumdiff(f0, f2, f[6], f[22]);
            sumdiff(f1, f3, f[38], f[54]);
        }
        {  // fi = 28
            Type f0, f1, f2, f3;
            sumdiff(f[14], f[46], f0, f1);
            sumdiff(f[30], f[62], f2, f3);
            sumdiff(f0, f2, f[14], f[30]);
            sumdiff(f1, f3, f[46], f[62]);
        }
        {  // fi = 32
            Type f0, f1, f2, f3;
            sumdiff(f[1], f[33], f0, f1);
            sumdiff(f[17], f[49], f2, f3);
            sumdiff(f0, f2, f[1], f[17]);
            sumdiff(f1, f3, f[33], f[49]);
        }
        {  // fi = 36
            Type f0, f1, f2, f3;
            sumdiff(f[9], f[41], f0, f1);
            sumdiff(f[25], f[57], f2, f3);
            sumdiff(f0, f2, f[9], f[25]);
            sumdiff(f1, f3, f[41], f[57]);
        }
        {  // fi = 40
            Type f0, f1, f2, f3;
            sumdiff(f[5], f[37], f0, f1);
            sumdiff(f[21], f[53], f2, f3);
            sumdiff(f0, f2, f[5], f[21]);
            sumdiff(f1, f3, f[37], f[53]);
        }
        {  // fi = 44
            Type f0, f1, f2, f3;
            sumdiff(f[13], f[45], f0, f1);
            sumdiff(f[29], f[61], f2, f3);
            sumdiff(f0, f2, f[13], f[29]);
            sumdiff(f1, f3, f[45], f[61]);
        }
        {  // fi = 48
            Type f0, f1, f2, f3;
            sumdiff(f[3], f[35], f0, f1);
            sumdiff(f[19], f[51], f2, f3);
            sumdiff(f0, f2, f[3], f[19]);
            sumdiff(f1, f3, f[35], f[51]);
        }
        {  // fi = 52
            Type f0, f1, f2, f3;
            sumdiff(f[11], f[43], f0, f1);
            sumdiff(f[27], f[59], f2, f3);
            sumdiff(f0, f2, f[11], f[27]);
            sumdiff(f1, f3, f[43], f[59]);
        }
        {  // fi = 56
            Type f0, f1, f2, f3;
            sumdiff(f[7], f[39], f0, f1);
            sumdiff(f[23], f[55], f2, f3);
            sumdiff(f0, f2, f[7], f[23]);
            sumdiff(f1, f3, f[39], f[55]);
        }
        {  // fi = 60
            Type f0, f1, f2, f3;
            sumdiff(f[15], f[47], f0, f1);
            sumdiff(f[31], f[63], f2, f3);
            sumdiff(f0, f2, f[15], f[31]);
            sumdiff(f1, f3, f[47], f[63]);
        }
    }  // end initial loop

    {  // -------- ldk=2  k4=16
        Type f0, f1, f2, f3;
        // do loop:
        sumdiff(f[0], f[8], f0, f1);
        sumdiff(f[4], f[12], f2, f3);
        sumdiff(f0, f2, f[0], f[4]);
        sumdiff(f1, f3, f[8], f[12]);
        sumdiff(f[16], f[24], f0, f1);
        f3 = SQRT2 * f[28];
        f2 = SQRT2 * f[20];
        sumdiff(f0, f2, f[16], f[20]);
        sumdiff(f1, f3, f[24], f[28]);
        // do loop:
        sumdiff(f[2], f[10], f0, f1);
        sumdiff(f[6], f[14], f2, f3);
        sumdiff(f0, f2, f[2], f[6]);
        sumdiff(f1, f3, f[10], f[14]);
        sumdiff(f[18], f[26], f0, f1);
        f3 = SQRT2 * f[30];
        f2 = SQRT2 * f[22];
        sumdiff(f0, f2, f[18], f[22]);
        sumdiff(f1, f3, f[26], f[30]);
        // do loop:
        sumdiff(f[1], f[9], f0, f1);
        sumdiff(f[5], f[13], f2, f3);
        sumdiff(f0, f2, f[1], f[5]);
        sumdiff(f1, f3, f[9], f[13]);
        sumdiff(f[17], f[25], f0, f1);
        f3 = SQRT2 * f[29];
        f2 = SQRT2 * f[21];
        sumdiff(f0, f2, f[17], f[21]);
        sumdiff(f1, f3, f[25], f[29]);
        // do loop:
        sumdiff(f[3], f[11], f0, f1);
        sumdiff(f[7], f[15], f2, f3);
        sumdiff(f0, f2, f[3], f[7]);
        sumdiff(f1, f3, f[11], f[15]);
        sumdiff(f[19], f[27], f0, f1);
        f3 = SQRT2 * f[31];
        f2 = SQRT2 * f[23];
        sumdiff(f0, f2, f[19], f[23]);
        sumdiff(f1, f3, f[27], f[31]);
    }

    {  // kh=2
        Type a, b, g0, f0, f1, g1, f2, g2, f3, g3;
        {  // ---- i=1
            double c1=.923879532511286756128183189397;  // == cos(Pi*1/8) == cos(Pi*1/8)
            double s1=.382683432365089771728459984029;  // == sin(Pi*1/8) == sin(Pi*1/8)
            // c2 = s2 = sqrt(1/2)
            // do loop II:
            sumdiff(f[40], f[56], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[32], a, f0, f1);
            sumdiff(f[48], b, g0, g1);
            sumdiff(f[44], f[60], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[36], a, f2, f3);
            sumdiff(f[52], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[32], f[36]);
            sumdiff(g1, b, f[56], f[60]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[48], f[52]);
            sumdiff(f1, b, f[40], f[44]);
            // do loop II:
            sumdiff(f[42], f[58], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[34], a, f0, f1);
            sumdiff(f[50], b, g0, g1);
            sumdiff(f[46], f[62], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[38], a, f2, f3);
            sumdiff(f[54], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[34], f[38]);
            sumdiff(g1, b, f[58], f[62]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[50], f[54]);
            sumdiff(f1, b, f[42], f[46]);
            // do loop II:
            sumdiff(f[41], f[57], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[33], a, f0, f1);
            sumdiff(f[49], b, g0, g1);
            sumdiff(f[45], f[61], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[37], a, f2, f3);
            sumdiff(f[53], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[33], f[37]);
            sumdiff(g1, b, f[57], f[61]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[49], f[53]);
            sumdiff(f1, b, f[41], f[45]);
            // do loop II:
            sumdiff(f[43], f[59], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[35], a, f0, f1);
            sumdiff(f[51], b, g0, g1);
            sumdiff(f[47], f[63], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[39], a, f2, f3);
            sumdiff(f[55], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[35], f[39]);
            sumdiff(g1, b, f[59], f[63]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[51], f[55]);
            sumdiff(f1, b, f[43], f[47]);
        }
    }

    {  // -------- ldk=4  k4=64
        Type f0, f1, f2, f3;
        // do loop:
        sumdiff(f[0], f[2], f0, f1);
        sumdiff(f[1], f[3], f2, f3);
        sumdiff(f0, f2, f[0], f[1]);
        sumdiff(f1, f3, f[2], f[3]);
        sumdiff(f[4], f[6], f0, f1);
        f3 = SQRT2 * f[7];
        f2 = SQRT2 * f[5];
        sumdiff(f0, f2, f[4], f[5]);
        sumdiff(f1, f3, f[6], f[7]);
    }

    {  // kh=8
        Type a, b, g0, f0, f1, g1, f2, g2, f3, g3;
        {  // ---- i=1
            double c1=.995184726672196886244836953109;  // == cos(Pi*1/32) == cos(Pi*1/32)
            double s1=.098017140329560601994195563888;  // == sin(Pi*1/32) == sin(Pi*1/32)
            double c2=.980785280403230449126182236134;  // == cos(Pi*2/32) == cos(Pi*1/16)
            double s2=.195090322016128267848284868476;  // == sin(Pi*2/32) == sin(Pi*1/16)
            // do loop II:
            cmult(s2, c2, f[34], f[62], b, a);
            sumdiff(f[32], a, f0, f1);
            sumdiff(f[60], b, g0, g1);
            cmult(s2, c2, f[35], f[63], b, a);
            sumdiff(f[33], a, f2, f3);
            sumdiff(f[61], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[32], f[33]);
            sumdiff(g1, b, f[62], f[63]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[60], f[61]);
            sumdiff(f1, b, f[34], f[35]);
        }
        {  // ---- i=2
            double c1=.980785280403230449126182236134;  // == cos(Pi*2/32) == cos(Pi*1/16)
            double s1=.195090322016128267848284868476;  // == sin(Pi*2/32) == sin(Pi*1/16)
            double c2=.923879532511286756128183189397;  // == cos(Pi*4/32) == cos(Pi*1/8)
            double s2=.382683432365089771728459984029;  // == sin(Pi*4/32) == sin(Pi*1/8)
            // do loop II:
            cmult(s2, c2, f[18], f[30], b, a);
            sumdiff(f[16], a, f0, f1);
            sumdiff(f[28], b, g0, g1);
            cmult(s2, c2, f[19], f[31], b, a);
            sumdiff(f[17], a, f2, f3);
            sumdiff(f[29], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[16], f[17]);
            sumdiff(g1, b, f[30], f[31]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[28], f[29]);
            sumdiff(f1, b, f[18], f[19]);
        }
        {  // ---- i=3
            double c1=.956940335732208864935797886980;  // == cos(Pi*3/32) == cos(Pi*3/32)
            double s1=.290284677254462367636192375816;  // == sin(Pi*3/32) == sin(Pi*3/32)
            double c2=.831469612302545237078788377618;  // == cos(Pi*6/32) == cos(Pi*3/16)
            double s2=.555570233019602224742830813947;  // == sin(Pi*6/32) == sin(Pi*3/16)
            // do loop II:
            cmult(s2, c2, f[50], f[46], b, a);
            sumdiff(f[48], a, f0, f1);
            sumdiff(f[44], b, g0, g1);
            cmult(s2, c2, f[51], f[47], b, a);
            sumdiff(f[49], a, f2, f3);
            sumdiff(f[45], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[48], f[49]);
            sumdiff(g1, b, f[46], f[47]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[44], f[45]);
            sumdiff(f1, b, f[50], f[51]);
        }
        {  // ---- i=4
            double c1=.923879532511286756128183189397;  // == cos(Pi*4/32) == cos(Pi*1/8)
            double s1=.382683432365089771728459984029;  // == sin(Pi*4/32) == sin(Pi*1/8)
            // c2 = s2 = sqrt(1/2)
            // do loop II:
            sumdiff(f[10], f[14], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[8], a, f0, f1);
            sumdiff(f[12], b, g0, g1);
            sumdiff(f[11], f[15], a, b);
            a *= SQRT1_2;
            b *= SQRT1_2;
            sumdiff(f[9], a, f2, f3);
            sumdiff(f[13], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[8], f[9]);
            sumdiff(g1, b, f[14], f[15]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[12], f[13]);
            sumdiff(f1, b, f[10], f[11]);
        }
        {  // ---- i=5
            double c1=.881921264348355029712756863661;  // == cos(Pi*5/32) == cos(Pi*5/32)
            double s1=.471396736825997648556387625904;  // == sin(Pi*5/32) == sin(Pi*5/32)
            double c2=.555570233019602224742830813950;  // == cos(Pi*10/32) == cos(Pi*5/16)
            double s2=.831469612302545237078788377616;  // == sin(Pi*10/32) == sin(Pi*5/16)
            // do loop II:
            cmult(s2, c2, f[42], f[54], b, a);
            sumdiff(f[40], a, f0, f1);
            sumdiff(f[52], b, g0, g1);
            cmult(s2, c2, f[43], f[55], b, a);
            sumdiff(f[41], a, f2, f3);
            sumdiff(f[53], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[40], f[41]);
            sumdiff(g1, b, f[54], f[55]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[52], f[53]);
            sumdiff(f1, b, f[42], f[43]);
        }
        {  // ---- i=6
            double c1=.831469612302545237078788377618;  // == cos(Pi*6/32) == cos(Pi*3/16)
            double s1=.555570233019602224742830813947;  // == sin(Pi*6/32) == sin(Pi*3/16)
            double c2=.382683432365089771728459984032;  // == cos(Pi*12/32) == cos(Pi*3/8)
            double s2=.923879532511286756128183189396;  // == sin(Pi*12/32) == sin(Pi*3/8)
            // do loop II:
            cmult(s2, c2, f[26], f[22], b, a);
            sumdiff(f[24], a, f0, f1);
            sumdiff(f[20], b, g0, g1);
            cmult(s2, c2, f[27], f[23], b, a);
            sumdiff(f[25], a, f2, f3);
            sumdiff(f[21], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[24], f[25]);
            sumdiff(g1, b, f[22], f[23]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[20], f[21]);
            sumdiff(f1, b, f[26], f[27]);
        }
        {  // ---- i=7
            double c1=.773010453362736960810906609759;  // == cos(Pi*7/32) == cos(Pi*7/32)
            double s1=.634393284163645498215171613224;  // == sin(Pi*7/32) == sin(Pi*7/32)
            double c2=.195090322016128267848284868478;  // == cos(Pi*14/32) == cos(Pi*7/16)
            double s2=.980785280403230449126182236133;  // == sin(Pi*14/32) == sin(Pi*7/16)
            // do loop II:
            cmult(s2, c2, f[58], f[38], b, a);
            sumdiff(f[56], a, f0, f1);
            sumdiff(f[36], b, g0, g1);
            cmult(s2, c2, f[59], f[39], b, a);
            sumdiff(f[57], a, f2, f3);
            sumdiff(f[37], b, g2, g3);
            cmult(s1, c1, f2, g3, b, a);
            sumdiff(f0, a, f[56], f[57]);
            sumdiff(g1, b, f[38], f[39]);
            cmult(c1, s1, g2, f3, b, a);
            sumdiff(g0, a, f[36], f[37]);
            sumdiff(f1, b, f[58], f[59]);
        }
    }
}
// -------------------------
// opcount by generator:  #mult=166=2.59375/pt   #add=462=7.21875/pt

template <typename Type>
inline void fht_dif_core_leq_64(Type *f, ulong n)
// Must have n \in {2, 4, 8, 16, 32, 64}
{
    switch ( n )
    {
    case 2: break;
    case 4: fht_dif_core_4(f); break;
    case 8: fht_dif_core_8(f); break;
    case 16: fht_dif_core_16(f); break;
    case 32: fht_dif_core_32(f); break;
    case 64: fht_dif_core_64(f); break;
//    default: ;  // ouch...
    }
}
// -------------------------


#endif  // !defined HAVE_SHORTFHTDIFCORE_H__
