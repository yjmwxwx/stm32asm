#if !defined HAVE_ROTATE2D_H__
#define      HAVE_ROTATE2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux2/reverse2d.h"
#include "perm/rotate.h" // rotate() 1-dim


template <typename Type>
void rotate_up(Type **f, ulong nr, ulong nc, ulong s)
// rotate towards row #0
{
    if ( s>=nr )  s %= nr;
    else if ( s==0 )  return;

    reverse_vert(f,    s,    nc);
    reverse_vert(f+s,  nr-s, nc);
    reverse_vert(f,    nr,   nc);
}
// -------------------------

template <typename Type>
void rotate_down(Type **f, ulong nr, ulong nc, ulong s)
// rotate away from row #0
{
    if ( s>=nr )  s %= nr;
    else if ( s==0 )  return;

    reverse_vert(f,         nr-s, nc);
    reverse_vert(f+(nr-s),  s,    nc);
    reverse_vert(f,         nr,   nc);
}
// -------------------------

template <typename Type>
void rotate_vert(Type **f, ulong nr, ulong nc, long s)
{
    if ( s>0 )  rotate_up(f,nr,nc, (ulong)s);
    else        rotate_down(f,nr,nc,  (ulong)-s);
}
// -------------------------


template <typename Type>
void rotate_left(Type **f, ulong nr, ulong nc, ulong s)
// rotate towards col #0
{
    if ( s>=nc )  s %= nc;
    else if ( s==0 )  return;
    while ( nr-- )  rotate_left(f[nr],nc,s);
}
// -------------------------

template <typename Type>
void rotate_right(Type **f, ulong nr, ulong nc, ulong s)
// rotate away from col #0
{
    if ( s>=nc )  s %= nc;
    else if ( s==0 )  return;
    while ( nr-- )  rotate_right(f[nr],nc,s);
}
// -------------------------

template <typename Type>
void rotate_horiz(Type **f, ulong nr, ulong nc, long s)
{
    if ( s>0 )  rotate_right(f,nr,nc,(ulong)s);
    else        rotate_left(f,nr,nc,(ulong)-s);
}
// -------------------------


template <typename Type>
void rotate_vh(Type **f, ulong nr, ulong nc, long vert, long horiz)
{
    if ( 0!=vert )   rotate_vert(f,nr,nc,vert);
    if ( 0!=horiz )  rotate_horiz(f,nr,nc,horiz);
}
// -------------------------

template <typename Type>
void zero2center(Type **f, ulong nr, ulong nc)
// useful for 2dim FFTs:
// brings zero freq to midpoint
{
    ulong nrh = nr/2;
    if ( nr&1 )  ++nrh;
    ulong nch = nc/2;
    if ( nc&1 )  ++nch;
    rotate_vh(f,nr,nc, nch,nrh);
}
// -------------------------

#endif // !defined HAVE_ROTATE2D_H__
