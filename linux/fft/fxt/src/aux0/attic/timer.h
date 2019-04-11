#if !defined  HAVE_TIMER_H__
#define       HAVE_TIMER_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include <sys/time.h>  // gettimeofday(), struct timeval


inline double timediff(timeval &x, timeval &y)
// Return time difference in seconds.
// Usage:
//    timeval t0, t1;
//    gettimeofday(&t0, 0);
//    big_computation();
//    gettimeofday(&t1, 0);
//    double elapsed_time = timediff(t0, t1);
{
    static const double mio1 = 1.0/1000000.0;
    double tx = (double)(x.tv_sec);
    tx += (double)(x.tv_usec) * mio1;
    double ty = (double)(y.tv_sec);
    ty += (double)(y.tv_usec) * mio1;
    return  ty - tx;
}
// -------------------------



#endif  // !defined HAVE_TIMER_H__
