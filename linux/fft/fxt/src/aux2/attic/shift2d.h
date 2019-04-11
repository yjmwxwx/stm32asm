#if !defined HAVE_SHIFT2D_H__
#define      HAVE_SHIFT2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux1/copy.h"
#include "aux1/shift.h"


template <typename Type>
void shift_left(Type **f, ulong nr, ulong nc, ulong s)
// shift towards col #0
{
    if ( s>=nc )  { null(f,nr,nc); return; }
    if ( s==0 )  return;
    while ( nr-- )  shift_left(f[nr],nc,s);
}
// -------------------------

template <typename Type>
void shift_right(Type **f, ulong nr, ulong nc, ulong s)
// shift away from col #0
{
    if ( s>=nc )  { null(f,nr,nc); return; }
    else if ( s==0 )  return;
    while ( nr-- )  shift_right(f[nr],nc,s);
}
// -------------------------

template <typename Type>
void shift_horiz(Type **f, ulong nr, ulong nc, long s)
// shift each row:
// if s>0  shift right
// else    shift left
{
    if ( s>0 )  shift_right(f,nr,nc,(ulong)s);
    else        shift_left(f,nr,nc,(ulong)-s);
}
// -------------------------


template <typename Type>
void shift_up(Type **f, ulong nr, ulong nc, ulong s)
// shift towards row #0
// (analogue to 'shift left columns')
{
    if ( s>=nr )  { null(f,nr,nc); return; }
    else if ( s==0 )  return;
    ulong k;
    for (k=0; k<nr-s; ++k)  acopy(f[k+s], f[k], nc);
    for (   ; k<nr; ++k)  null(f[k],nc);
}
// -------------------------

template <typename Type>
void shift_down(Type **f, ulong nr, ulong nc, ulong s)
// shift away from row #0
// (analogue to 'shift right columns')
{
    if ( s>=nr )  { null(f,nr,nc); return; }
    else if ( s==0 )  return;
    ulong k;
    for (k=nr-1; k>=s; --k)  acopy(f[k-s], f[k], nc);
    do  { null(f[k],nc); }  while ( k-- );
}
// -------------------------

template <typename Type>
void shift_vert(Type **f, ulong nr, ulong nc, long s)
// if s>0  shift up
// else    shift down

{
    if ( s>0 )  shift_up(f,nr,nc,(ulong)s);
    else        shift_down(f,nr,nc,(ulong)-s);
}
// -------------------------


template <typename Type>
void shift_vh(Type **f, ulong nr, ulong nc, long vert, long horiz)
// shift both horiz/vert
{
    if ( 0!=vert )   shift_vert(f,nr,nc,vert);
    if ( 0!=horiz )  shift_horiz(f,nr,nc,horiz);
}
// -------------------------

#endif // !defined HAVE_SHIFT2D_H__
