#if !defined HAVE_CMULT_H__
#define      HAVE_CMULT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "complextype.h"


static inline void csqr(double &u, double &v)
// {u,v} <--| {u*u-v*v, 2*u*v}
{
    double t = u * u - v * v;
    v *= (u + u);
    u = t;
}
// -------------------------

static inline void csqr_n(double &u, double &v, double dn)
// {u,v} <--| {dn*(u*u-v*v), dn*(2*u*v)}
{
    double t = u * u - v * v;
    v *= (u + u);
    v *= dn;
    u = t * dn;
}
// -------------------------

static inline void csqr(double a, double b,
                        double &u, double &v)
// {u,v} <--| {a*a-b*b, 2*a*b}
{
    u = a * a - b * b;
    v = a * b;
    v += v;
}
// -------------------------

static inline void cmult(double c, double s,
                         double &u, double &v)
// {u,v} <--| u = u*c-v*s;  v = u*s+v*c
{
    double t = u * s + v * c;
    u *= c;
    u -= v * s;
    v = t;
}
// -------------------------

static inline void cmult_n(double c, double s,
                           double &u, double &v,
                           double dn)
// {u,v} <--| {dn*(u*c-v*s), dn*(u*s+v*c)}
{
    double t = u * s + v * c;
    u *= c;
    u -= v * s;
    u *= dn;
    v = t * dn;
}
// -------------------------

static inline void cmult(double c, double s,
                         double x, double y,
                         double &u, double &v)
// {u,v} <--| {x*c-y*s, x*s+y*c}
{
    u = x * c - y * s;
    v = y * c + x * s;
}
// -------------------------

static inline void cmult(double c, double s,
                         Complex x, Complex y,
                         Complex &u, Complex &v)
// {u,v} <--| {x*c-y*s, x*s+y*c}
// used in generated complex fhts
{
    u = x * c - y * s;
    v = y * c + x * s;
}
// -------------------------

static inline void cmult(Complex c, Complex s,
                         Complex x, Complex y,
                         Complex &u, Complex &v)
// {u,v} <--| {x*c-y*s, x*s+y*c}
// used in generated complex fhts
{
    u = x * c - y * s;
    v = y * c + x * s;
}
// -------------------------

static inline void cmult_inv(double c, double s,
                             double x, double y,
                             double &u, double &v)
// {u,v} <--| {x*c+y*s, -x*s+y*c}
// same as cmult(c, -s, x, y, u, v)
{
    u = x * c + y * s;
    v = y * c - x * s;
}
// -------------------------

static inline void cmult_inv(double c, double s,
                             Complex x, Complex y,
                             Complex &u, Complex &v)
// {u,v} <--| {x*c+y*s, -x*s+y*c}
// same as cmult(c, -s, x, y, u, v)
// used in generated complex fhts
{
    u = x * c + y * s;
    v = y * c - x * s;
}
// -------------------------

static inline void cmult_inv(Complex c, Complex s,
                             Complex x, Complex y,
                             Complex &u, Complex &v)
// {u,v} <--| {x*c+y*s, -x*s+y*c}
// same as cmult(c, -s, x, y, u, v)
// used in generated complex fhts
{
    u = x * c + y * s;
    v = y * c - x * s;
}
// -------------------------


#endif  // !defined HAVE_CMULT_H__
