#if !defined HAVE_RANGE_H__
#define      HAVE_RANGE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bits/bitsperlong.h"

//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#warning  'PARANOIA tests enabled in range.h'
#include "jjassert.h"
#endif  // PARANOIA

template <typename Type>
static inline bool in_range_q(Type xmin, Type xmax, Type x)
// Return whether xmin<= x <=xmax
// precondition:  xmin<=xmax
{
    return ( (x>=xmin) && (x<=xmax) );
//    return ( (x-xmin) | (xmax-x) ) >> (BITS_PER_LONG-1);
}
// -------------------------

template <typename Type>
static inline bool off_range_q(Type x, Type xmin, Type xmax)
// Return whether x<xmin or x>xmax
// precondition:  xmin<=xmax
{
    return ( (x<xmin) || (x>xmax) );
//    return  ( (xmin-x) | (x-xmax) ) >> (BITS_PER_LONG-1);
}
// -------------------------


template <typename Type>
static inline void wrap_range(Type xmin, Type xmax, Type &x)
// toroidal rules apply
// precondition:  xmin<=xmax
{
    if ( x<xmin )  x = xmax;
    else if ( x>xmax )  x = xmin;
}
// -------------------------

template <typename Type>
static inline void clip_range(Type xmin, Type xmax, Type &x)
// force x into [xmin, xmax]
// precondition:  xmin<=xmax
{
    if ( x<xmin )        x = xmin;
    else  if ( x>xmax )  x = xmax;
}
// -------------------------

template <typename Type>
static inline bool clip_range_q(Type xmin, Type xmax, Type &x)
// force x into [xmin, xmax]
// return whether clipping occurred
// precondition:  xmin<=xmax
{
    int clipq = 0;
    if ( x<xmin )  { x = xmin; clipq = 1; }
    else  { if ( x>xmax )  { x = xmax; clipq = 1; } }
    return clipq;
}
// -------------------------

template <typename Type>
static inline void clip_range0(Type xmax, Type &x)
// force x into [0, xmax]
{
    if ( x<0 )           x = 0;
    else  if ( x>xmax )  x = xmax;
}
// -------------------------


template <typename Type>
static inline bool intersect_range_o(Type xmin, Type xmax, Type &x1, Type &x2)
// push  [x1,x2]  into  [xmin,xmax]
// return:  0  if  completely outside  1  else
// precondition:  xmin<=xmax
// precondition:  x1<=x2
{
#ifdef PARANOIA
    jjassert( xmin<=xmax );
    jjassert( x1<=x2 );
#endif  // PARANOIA

    if ( (x1>xmax) || (x2<xmin) )  return 0;  // completely outside
    if ( x1<xmin )  x1 = xmin;
    if ( x2>xmax )  x2 = xmax;

#ifdef PARANOIA
    jjassert( x1<=x2 );
#endif  // PARANOIA
    return  1;
}
// -------------------------


template <typename Type>
static inline bool intersect_range(Type xmin, Type xmax, Type &x1, Type &x2)
// push  [x1,x2]  into  [xmin,xmax]
// return:  0  if  completely outside  1  else
// precondition:  xmin<=xmax
{
#ifdef PARANOIA
    jjassert( xmin<=xmax );
#endif  // PARANOIA

    if ( x1>x2 )  { Type t = x1;  x1 = x2;  x2 = t; }  // swap2(x1, x2)
    int ret = intersect_range_o(xmin, xmax, x1, x2);

#ifdef PARANOIA
    jjassert( x1<=x2 );
#endif  // PARANOIA
    return  ret;
}
// -------------------------

#undef PARANOIA


#endif  // !defined HAVE_RANGE_H__
