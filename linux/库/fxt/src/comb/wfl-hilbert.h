#if !defined  HAVE_WFL_HILBERT_H__
#define       HAVE_WFL_HILBERT_H__
// This file is part of the FXT library.
// Copyright (C) 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#define WFL_MAXLEV 62  // jj: 2^62 is big enough
#define WFL_NUMLEV (WFL_MAXLEV+2)  // two sentinels
#define WFL_MAXDIM 5

class wfl_cell
// Container used in class wfl_hilbert.
{
public:
    ulong cstep; // "step" counter n along walk, deflated by lv levels;
//    ulong cvertex; // vertex within super-cell,  // jj: this was a write-only variable
    ulong cedge; // transforming edge-pair or corresponding symbol indexing tables

    // coordinate vector of cell origin lattice node
    // Raster encoding: coordinate vector is reverse of raster index modulo 2^l;
    // similarly for Gray path, with l = 1.
    ulong ccoord[WFL_MAXDIM];  // jj: static layout for speed

public:
    wfl_cell()  { ; }
    ~wfl_cell()  { ; }

    void init(ulong d, ulong /*lv*/, ulong /*v*/, ulong e)
    {
//        ulong lev = lv;
//        cvertex = v;
        cedge = e;
        ulong dim = d;
        for (ulong i = 0; i < dim; i++)  ccoord[i] = 0;
        cstep = 0;
    }
};
// -------------------------


class wfl_hilbert
// Fred Lunnon's (second) iterative algorithm to convert linear coordinate
// into coordinates of d-dimensional Hilbert curve (and back).
// Translated and adapted from Java code by Fred Lunnon.
//
// See the file wfl-hilbert-doc.txt in the doc/ directory
// for Fred Lunnon's explanations of the algorithm.
{
public:
//    ulong step; // current count of steps along walk (linear coordinate)
    // jj: was a copy of branch[0].cstep

    ulong dim; // dimension d of walk: d >= 2, constant along branch
//    ulong lev; // level lv of cell above individual nodes lv = 0
    // jj: lev is now unlimited for dim>=2

    ulong p2d1; // 2^d - 1

//    ulong *coord; // coordinate vector of current lattice node
    // jj: was a copy of branch[0].ccoord

    // jj: array after other data for better memory locality; also static layout
    wfl_cell branch[WFL_NUMLEV]; // chain along branch of tree of cells / D0L symbols


public:
    wfl_hilbert(ulong dm/*, ulong lev*/)
    {
        // commence walk at origin
        this->dim = dm;
        this->p2d1 = (1UL << dm) - 1;

        ulong e = 1; // 2^(-lv mod d)
        for (ulong lv = 0; lv < WFL_NUMLEV; lv++)
        {
            // stabilise walk via edge-pair [0, e] or symbol k at level lv
            branch[lv].init(dm, lv, 0, e );
            e = ( (e == 1) ? 1 << (dim-1) : e >> 1 );
        }
    }

    ~wfl_hilbert()  { ; }

    const ulong * get_coord()  const
    // jj: avoid the class member coord
    { return  branch[0].ccoord; }

    ulong get_step()  const
    // jj: avoid the class member step
    { return  branch[0].cstep; }

    ulong gray(ulong j)  const
    { return j ^ (j >> 1); }

    ulong inverse_gray(ulong x)  const
    {
#if 1
        ulong y = 1;
        do  { x = x ^ (x >> y);  y = y << 1; }  while (y < dim);
#else  // jj: unrolled
        x = x ^ (x >> 1);
        x = x ^ (x >> 2);
        x = x ^ (x >> 4);
#if WFL_MAXDIM > 8
        x = x ^ (x >> 8);
        x = x ^ (x >> 16);
        x = x ^ (x >> 32);
#endif
#endif
        return x;
    }

    ulong decor(ulong j)  const  // jj: want a better name for this method
    // Convert path pace to unit hypercube edge-pair decorating path
    {
        if (j == 0)        return (gray(j)   << dim) | gray(j+1);
        if (j == p2d1)     return (gray(j-1) << dim) | gray(j);
        if ((j & 1) == 0)  return (gray(j-2) << dim) | gray(j+1);
        else               return (gray(j-1) << dim) | gray(j+2);
    }

    ulong compo(ulong e, ulong f)  const  // jj: want a better name for this method
    // Transform f (or vertex f when fl = 0) by e, both edge-pairs of
    //   unit cube vertices packed into integers (also D0L symbols);
    //   Relative to unshifted canonical edge: axis x_{d-1} fixed!
    {
        ulong el = e >> dim,  er = e & p2d1;
        ulong fl = f >> dim,  fr = f & p2d1;

        // Unpack left/even/negative, right/odd/positive vertices:
        ulong elr = (el ^ er);  // always a power of 2
#if 1
        fl = fl * elr;
        fr = fr * elr;
#else  // jj: slower
        if ( elr!=1 )
        {
            ulong s = 0;
            while ( elr>>=1 )  { ++s; }
            elr -= 1;
            fl <<= s;
            fr <<= s;
        }

#endif
        // Circular shift log_2(el(+)er) places to cycle axes
        // then XOR with mask el to reverse axes:
        ulong gl = (((fl << 1) | (fl >> (dim-1))) & p2d1) ^ el;
        ulong gr = (((fr << 1) | (fr >> (dim-1))) & p2d1) ^ el;
        return (gl << dim) | gr; // repack vertices
    }

    ulong inverse_ept(ulong e)  const
    // Inverse of edge-pair transform
    // Relative to unshifted canonical edge: axis x_{d-1} fixed!
    {
        ulong el = e >> dim,  er = e & p2d1;
        // (el ^ er) is always a power of 2
        ulong p2r = (1 << (dim-1)) / (el ^ er);  // jj: division!
        ulong gl = el * p2r;
        p2r = (p2r >> 1UL) | ((p2r << (dim-1UL)) & p2d1);
        gl = (gl | (gl >> dim)) & p2d1;
        return (gl << dim) | (gl ^ p2r); // repack vertices
    }

    ulong jump_to_step(ulong new_step)
    // Goto node at given step count along walk,
    //   final step in 0 <= n < 2^(dim*lev), returning minimum level unaltered;
    {
        ulong nstep = new_step;
        ulong lv = 0;  // min level lv common with current step
        while ( branch[lv].cstep != nstep )
        {
            lv = lv + 1;
            nstep >>= dim;
        }

        const ulong lv1 = lv; // save level for return
        nstep = new_step - (branch[lv].cstep << (lv*dim)); // residual step count

        while ( lv != 0 )
        {
            lv = lv - 1;
            ulong j = nstep >> (lv*dim);
            nstep = nstep - (j << (lv*dim));
            branch[lv].cstep = (branch[lv+1].cstep << dim) + j;

            // extract next digit j to radix 2^d
            ulong edge = compo(branch[lv+1].cedge, decor(j));
            ulong vertex = compo(branch[lv+1].cedge, gray(j));
            branch[lv].cedge = edge;

            // edge-pair and vertex at level lv
            for (ulong i = 0; i < dim; i++)
            {
                branch[lv].ccoord[i] = (branch[lv+1].ccoord[i] << 1) + (vertex & 1);
                vertex >>= 1;
            }
            // unpack vertex, update coordinate vector
        }

        return lv1;
    }

    ulong jump_to_coord(const ulong * ncoord)
    // Goto node at given coordinate vector along walk,
    //   final step in 0 <= n < 2^(dim*lev), returning minimum level unaltered;
    {
        // min level lv common with current coord
        ulong lv = -1UL;
        bool unequal;
        do  // jj: do-while loop
        {
            lv = lv + 1;
            unequal = false;
            for (ulong i = 0; i < dim; i++)
            {
                unequal |= ((ncoord[i] >> lv) != branch[lv].ccoord[i]);
            }
        }
        while ( unequal );

        const ulong lv1 = lv; // save for return

        // Isolate node in cell octant, encode radix 2:
        while ( lv != 0 )
        {
            lv = lv - 1;
            ulong vertex = 0;
            for (ulong i = 0; i < dim; i++)
            {
                branch[lv].ccoord[i] = ncoord[i] >> lv;
                vertex += (((ncoord[i] >> lv) & 1) << i);
            }

            const ulong ce = branch[lv+1].cedge;
            const ulong j = inverse_gray( compo( inverse_ept( ce ), vertex ) & p2d1 );

            // spatial cube vertex -> Gray path pace
            branch[lv].cstep = ( branch[lv+1].cstep << dim ) + j;

            // register next digit j of step, to radix 2^d
            ulong edge = compo( branch[lv+1].cedge, decor(j) );

            branch[lv].cedge = edge;
        }

        return lv1;
    }

    // JA etc user methods, UNTESTED
    /* Both jump() methods currently do work which is irrelevant at level 0
       [e.g. computing edge/symbol], somewhat slowing short jump for low dim.
       Special-purpose methods would improve next(), prev(), hilbert_move(). */
    const ulong * lin2hilbert(ulong nstep)
    // coordinate vector at given step counter
    { jump_to_step( nstep );  return get_coord(); }

    ulong hilbert2lin(const ulong * ncoord)
    // step counter at given coordinate vector
    { jump_to_coord(ncoord);  return get_step(); }

    /*
    public ulong * hilbert_move(ulong step)
    // coordinate vector increment as given step advances to next
    {
        ulong[] d_coord = new ulong[dim];
        jump_to_step(step);
        for (ulong i = 0; i < dim; i++)  d_coord[i] = coord[i];
        jump_to_step(step+1);
        for (ulong i = 0; i < dim; i++)  d_coord[i] = coord[i] - d_coord[i];
        return d_coord;
    }
    */

    ulong next()
    // Goto subsequent node along Hilbert walk, returning minimum level unaltered
    { return jump_to_step( get_step() + 1 ); }

    ulong prev()
    // Goto previous node along Hilbert walk, returning minimum level unaltered
    { return jump_to_step( get_step() - 1 ); }
};
// -------------------------

#endif // !defined HAVE_WFL_HILBERT_H__
