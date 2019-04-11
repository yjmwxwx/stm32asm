#if !defined HAVE_CONSTANTS_H__
#define      HAVE_CONSTANTS_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

// echo 'scale=40; sqrt(1/2);' | bc -l
// echo -e 'default(realprecision,40); sqrt(1/2)' | gp -q
#define SQRT1_2     0.707106781186547524400844362104
// == M_SQRT1_2 in cmath
#define SQRT2       1.414213562373095048801688724209
// == M_SQRT2 in cmath

#define COS_1_PI_8  0.923879532511286756128183189397
#define SIN_1_PI_8  0.382683432365089771728459984029

#define PI          3.14159265358979323846264338327950

#endif  // !defined HAVE_CONSTANTS_H__
