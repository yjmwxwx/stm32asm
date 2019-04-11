#if !defined  HAVE_TEX_LINE_H__
#define       HAVE_TEX_LINE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

// define to use pict2e vectors (else use curves):
#define TEX_USE_PICT2E  // default
// aux0/tex-line.cc:
void tex_line(long x0, long y0, long x1, long y1, bool vq=true);

inline void tex_line(ulong x0, ulong y0, ulong x1, ulong y1, bool vq=true)
{ tex_line((long)x0, (long)y0, (long)x1, (long)y1, vq); }

void tex_line_fl(double x0, double y0, double x1, double y1, bool vq=true);
void tex_draw_turn(double x, double y, double dx, double dy, double ndx, double ndy,
                   ulong style, bool vq=true, double m=0.25);



#endif  // !defined HAVE_TEX_LINE_H__
