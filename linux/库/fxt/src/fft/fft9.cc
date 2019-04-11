// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <cmath>

#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "complextype.h"  // Complex

//#define U   0.6981317007977318307694763073954450853771  // == (2*M_PI/9)
#define CU1 0.7660444431189780352023926505554166739358  // == ((2*cos(U)-cos(2*U)-cos(4*U))/3)
#define CU2 0.9396926207859083840541092773247314699362  // == ((cos(U)+cos(2*U)-2*cos(4*U))/3)
#define CU3 0.1736481776669303488517166267693147960003  // == ((cos(U)-2*cos(2*U)+cos(4*U))/-3)

#define SU1 0.6427876096865393263226434099072634329075  // == (sin(U))
#define SU2 0.9848077530122080593667430245895230136706  // == (sin(2*U))
#define SU3 0.8660254037844386467637231707529361834714  // == (sin(3*U))
#define SU4 0.3420201433256687330440996146822595807630  // == (sin(4*U))


void
fft9_m1(Complex *x)
// 9-point FFT, fixed isign = -1
//.
// Cf. Nussbaumer p.148f
{
    Complex t1, t2, t3, t4, t5, t6, t7, t8, t9;
    sumdiff(x[1], x[8], t1, t6);
    sumdiff(x[7], x[2], t2, t7);
    sumdiff(x[3], x[6], t3, t8);
    sumdiff(x[4], x[5], t4, t9);

    Complex t10, t11, t12, t13, t14;
    t12 = t2 - t4;
    sumdiff(t1, t2, t5, t11);
    t5 += t4;
    sumdiff(t7, t9, t10, t14);
    t10 += t6;
    t13 = t7 - t6;

    Complex m0, m1, m3, m4, m5;
    m0 = x[0] + t3 + t5;
    m1 = 1.5 * t3;
    m3 = t11 * CU1;
    m4 = t12 * CU2;
    m5 = (t11+t12) * CU3;

    Complex m6, m7, m8, m9, m10;
    m6 = t10 * Complex(0, -SU3);
    m7 = t8  * Complex(0, -SU3);
    m8 = t13 * Complex(0, +SU1);
    m9 = t14 * Complex(0, +SU4);
    m10 = (t14-t13) * Complex(0, SU2);

    t10 = m3 + m4;
    t1 = m5 - m4;
    t2 = m8 + m9;
    t3 = m9 - m10;
    t4 = m0 - t5;
    t6 = t4 - 0.5*t5;

    t5 = t4 - m1;
    t8 = t1 + t5;
    t7 = t5 + t10;
    t9 = t5 - t10 - t1;

    t10 = m7 + t2;
    t12 = m7 - t2 + t3;
    t11 = m7 - t3;

    x[0] = m0;
    sumdiff(t7, t10, x[1], x[8]);
    sumdiff(t8, t11, x[7], x[2]);
    sumdiff(t9, t12, x[4], x[5]);
    sumdiff(t6, m6,  x[3], x[6]);
}
// -------------------------

void
fft9_p1(Complex *x)
// 9-point FFT, fixed isign = +1
{
    Complex t1, t2, t3, t4, t5, t6, t7, t8, t9;
    sumdiff(x[8], x[1], t1, t6);  // changed wrt. fft9_minus()
    sumdiff(x[2], x[7], t2, t7);  // changed wrt. fft9_minus()
    sumdiff(x[6], x[3], t3, t8);  // changed wrt. fft9_minus()
    sumdiff(x[5], x[4], t4, t9);  // changed wrt. fft9_minus()

    Complex t10, t11, t12, t13, t14;
    t12 = t2 - t4;
    sumdiff(t1, t2, t5, t11);
    t5 += t4;
    sumdiff(t7, t9, t10, t14);
    t10 += t6;
    t13 = t7 - t6;

    Complex m0, m1, m3, m4, m5;
    m0 = x[0] + t3 + t5;
    m1 = 1.5 * t3;
    m3 = t11 * CU1;
    m4 = t12 * CU2;
    m5 = (t11+t12) * CU3;

    Complex m6, m7, m8, m9, m10;
    m6 = t10 * Complex(0, -SU3);
    m7 = t8  * Complex(0, -SU3);
    m8 = t13 * Complex(0,  SU1);
    m9 = t14 * Complex(0,  SU4);
    m10 = (t14-t13) * Complex(0, SU2);

    t10 = m3 + m4;
    t1 = m5 - m4;
    t2 = m8 + m9;
    t3 = m9 - m10;
    t4 = m0 - t5;
    t6 = t4 - 0.5*t5;

    t5 = t4 - m1;
    t8 = t1 + t5;
    t7 = t5 + t10;
    t9 = t5 - t10 - t1;

    t10 = m7 + t2;
    t12 = m7 - t2 + t3;
    t11 = m7 - t3;

    x[0] = m0;
    sumdiff(t7, t10, x[1], x[8]);
    sumdiff(t8, t11, x[7], x[2]);
    sumdiff(t9, t12, x[4], x[5]);
    sumdiff(t6, m6,  x[3], x[6]);
}
// -------------------------



void
fft9_m1(double *xr, double *xi)
// 9-point FFT, fixed isign = -1
//.
// Cf. Nussbaumer p.148
{
    // --- RE:
    double tr1, tr2, tr3, tr4, tr5, tr6, tr7, tr8, tr9, tr10, tr11, tr12, tr13, tr14;

    tr1 =  xr[1] + xr[8];
    tr6 =  xr[1] - xr[8];

    tr2 =  xr[7] + xr[2];
    tr7 =  xr[7] - xr[2];

    tr3 =  xr[3] + xr[6];
    tr8 =  xr[3] - xr[6];

    tr4 =  xr[4] + xr[5];
    tr9 =  xr[4] - xr[5];


    tr5 =   tr1 + tr4 + tr2;

    tr14 =  tr7 - tr9;
    tr10 =  tr7 + tr9 + tr6;
    tr13 =  tr7 - tr6;

    tr11 =  tr1 - tr2;
    tr12 =  tr2 - tr4;


    double mr0, mr1, mr2, mr3, mr4, mr5, tr15, tr16;

    mr0 =  xr[0] + tr3 + tr5;
    mr1 =  1.5 * tr3;
    mr2 = -0.5 * tr5;

    tr15 =  tr12 + tr11;
    tr16 =  tr14 - tr13;

    mr3 =  CU1 * tr11;
    mr4 =  CU2 * tr12;
    mr5 =  CU3 * tr15;


    // --- IM:
    double ti1, ti2, ti3, ti4, ti5, ti6, ti7, ti8, ti9, ti10, ti11, ti12, ti13, ti14;

    ti1 =  xi[1] + xi[8];
    ti6 =  xi[1] - xi[8];

    ti2 =  xi[7] + xi[2];
    ti7 =  xi[7] - xi[2];

    ti3 =  xi[3] + xi[6];
    ti8 =  xi[3] - xi[6];

    ti4 =  xi[4] + xi[5];
    ti9 =  xi[4] - xi[5];

    ti5 =   ti1 + ti4 + ti2;

    ti14 =  ti7 - ti9;
    ti10 =  ti7 + ti9 + ti6;
    ti13 =  ti7 - ti6;

    ti11 =  ti1 - ti2;
    ti12 =  ti2 - ti4;


    double mi0, mi1, mi2, mi3, mi4, mi5, ti15, ti16;

    mi0 =   xi[0] + ti3 + ti5;
    mi1 =   1.5 * ti3;
    mi2 =  -0.5 * ti5;

    ti15 =  ti12 + ti11;
    ti16 =  ti14 - ti13;

    mi3 =  CU1 * ti11;
    mi4 =  CU2 * ti12;
    mi5 =  CU3 * ti15;


    // RE, IM:  ------------------

    double mr6, mr7, mr8, mr9, mr10;
    double mi6, mi7, mi8, mi9, mi10;

    mr6 =   SU3 * ti10;
    mi6 =  -SU3 * tr10;

    mr7 =   SU3 * ti8;
    mi7 =  -SU3 * tr8;

    mr8 =  -SU1 * ti13;
    mi8 =   SU1 * tr13;

    mr9 =  -SU4 * ti14;
    mi9 =   SU4 * tr14;

    mr10 = -SU2 * ti16;
    mi10 =  SU2 * tr16;

    // -------------------------


    // --- RE:

    double tr0;
    tr0 =  -mr3 - mr4;
    tr1 =   mr5 - mr4;
    tr2 =  -mr8 - mr9;
    tr3 =   mr9 - mr10;
    tr4 =   mr0 + mr2 + mr2;
    tr5 =   tr4 - mr1;
    tr6 =   tr4 + mr2;
    tr7 =   tr5 - tr0;
    tr8 =   tr1 + tr5;
    tr9 =   tr0 - tr1 + tr5;
    tr10 =  mr7 - tr2;
    tr11 =  mr7 - tr3;
    tr12 =  mr7 + tr2 + tr3;


    xr[0]= mr0;

    xr[1]= tr7 + tr10;
    xr[8]= tr7 - tr10;

    xr[7]= tr8 + tr11;
    xr[2]= tr8 - tr11;

    xr[3]= tr6 + mr6;
    xr[6]= tr6 - mr6;

    xr[4]= tr9 + tr12;
    xr[5]= tr9 - tr12;


    // --- IM:

    double ti0;
    ti0 =  -mi3 - mi4;
    ti1 =   mi5 - mi4;
    ti2 =  -mi8 - mi9;
    ti3 =   mi9 - mi10;
    ti4 =   mi0 + mi2 + mi2;
    ti5 =   ti4 - mi1;
    ti6 =   ti4 + mi2;
    ti7 =   ti5 - ti0;
    ti8 =   ti1 + ti5;
    ti9 =   ti0 - ti1 + ti5;
    ti10 =  mi7 - ti2;
    ti11 =  mi7 - ti3;
    ti12 =  mi7 + ti2 + ti3;


    xi[0]= mi0;

    xi[1]= ti7 + ti10;
    xi[8]= ti7 - ti10;

    xi[7]= ti8 + ti11;
    xi[2]= ti8 - ti11;

    xi[3]= ti6 + mi6;
    xi[6]= ti6 - mi6;

    xi[4]= ti9 + ti12;
    xi[5]= ti9 - ti12;
}
// -------------------------

void
fft9_p1(double *xr, double *xi)
// 9-point FFT, fixed isign = +1
{
    fft9_m1(xi, xr);  // note swapped args
}
// -------------------------

