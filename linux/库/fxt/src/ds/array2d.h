#if !defined HAVE_ARRAY2D_H__
#define      HAVE_ARRAY2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "aux2/copy2d.h"  // offset_copy(), fill(), null()
#include "aux1/copy.h"  // fill(), null()
//#include "aux2/minmax2d.h"
//#include "aux2/shift2d.h"
//#include "aux2/reverse2d.h"
//#include "aux2/rotate2d.h"
//#include "aux2/scale2d.h"
//#include "aux2/applyfunc2d.h"
//#include "aux0/swap.h"


//#include "aux0/swap.h"
//#include "sort/minmaxmed23.h"  // max2()


//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#define  ARRAY2D_ASSERTS  // define to catch access beyond size
#endif  // PARANOIA



//#define  ARRAY2D_ASSERTS   // define to catch access beyond size
#ifdef ARRAY2D_ASSERTS
#include "jjassert.h"
#endif


template <typename Type>
class array2d
{
public:
    ulong nc_, nr_;  // #rows, #cols
    Type **rowp_;    // (pointer to) array of pointers to rows
    Type *f_;        // pointer to data if contiguous rows, else 0

protected:
    bool myfq_;     // whether f_ was allocated by constructor


private:  // have pointer data
    array2d(const array2d&);  // forbidden
    array2d & operator = (const array2d&);  // forbidden

public:
    explicit array2d(ulong nr, ulong nc, Type *f=0);
    explicit array2d(ulong nr, ulong nc, Type **rowp);

    ~array2d()
    {
        delete [] rowp_;
        if ( myfq_ )  delete [] f_;
    }


    ulong num_elem()  const  { return nr_ * nc_; }
    ulong num_cols()  const  { return nc_; }
    ulong num_rows()  const  { return nr_; }

    bool mem_contig_q()  const
    // Return whether memory is contiguous.
    { return ( f_ != 0 ); }

    Type get(ulong r, ulong c)  const
    {
#ifdef  ARRAY2D_ASSERTS
        jjassert( r < nr_ );
        jjassert( c < nc_ );
#endif
        return rowp_[r][c];
    }
    void set(ulong r, ulong c, Type v)
    {
#ifdef  ARRAY2D_ASSERTS
        jjassert( r < nr_ );
        jjassert( c < nc_ );
#endif
        rowp_[r][c]=v;
    }

    Type * row(ulong r)
    {
#ifdef  ARRAY2D_ASSERTS
        jjassert( r < nr_ );
#endif
        return rowp_[r];
    }

    const Type * operator [] (ulong y) const
    {
#ifdef  ROW_ASSERTS
        jjassert( y < nr_ );
#endif
        return rowp_[y];
    }

    Type * operator [] (ulong y)
    {
#ifdef  ROW_ASSERTS
        jjassert( y < nr_ );
#endif
        return rowp_[y];
    }

public:
    void null()
    {
        if ( mem_contig_q() )  ::null(f_, num_elem() );
        else  ::null(rowp_, nr_, nc_);
    }

    void fill(Type v)
    {
        if ( mem_contig_q() )  ::fill(f_, num_elem(), v );
        else  ::fill(rowp_, nr_, nc_, v);
    }

//    void min_max(Type *mi, Type *ma)  const
//    { ::min_max((const Type **)rowp_, nr_, nc_, mi, ma); }
//
//    Type min()  const  { return ::min((const Type **)rowp_, nr_, nc_); }
//    Type max()  const  { return ::max((const Type **)rowp_, nr_, nc_); }
//
//    void linear_scale(Type mi, Type ma, Type nmi, Type nma)
//    { ::linear_scale(rowp_, nr_, nc_, mi, ma, nmi, nma); }
//
//    void linear_scale(Type nmi, Type nma)
//    { ::linear_scale(rowp_, nr_, nc_, nmi, nma); }
//
//    void log_scale(double xi, double xa, Type nma)
//    { ::log_scale(rowp_, nr_, nc_, xi, xa, nma); }
//
//    void apply_func(Type (*func)(Type))
//    { for (ulong r=0; r<nr_; ++r)  ::apply_func(rowp_[r], nc_, func); }
//
//    void shift_up(ulong r)  { ::shift_up(rowp_, nr_, nc_, r); }
//    void shift_down(ulong r)  { ::shift_down(rowp_, nr_, nc_, r); }
//    void shift_vert(long r)  { ::shift_vert(rowp_, nr_, nc_, r); }
//    void shift_left(ulong r)  { ::shift_left(rowp_, nr_, nc_, r); }
//    void shift_right(ulong r)  { ::shift_right(rowp_, nr_, nc_, r); }
//    void shift_horiz(long r)  { ::shift_horiz(rowp_, nr_, nc_, r); }
//    void shift_vh(long vert, long horiz)  { ::shift_vh(rowp_, nr_, nc_, vert, horiz); }
//
//    void reverse_vert()  { ::reverse_vert(rowp_, nr_, nc_); }
//    void reverse_horiz()  { ::reverse_horiz(rowp_, nr_, nc_); }
//
//    void rotate_up(ulong r)  { ::rotate_up(rowp_, nr_, nc_, r); }
//    void rotate_down(ulong r)  { ::rotate_down(rowp_, nr_, nc_, r); }
//    void rotate_vert(long r)  { ::rotate_vert(rowp_, nr_, nc_, r); }
//    void rotate_left(ulong r)  { ::rotate_left(rowp_, nr_, nc_, r); }
//    void rotate_right(ulong r)  { ::rotate_right(rowp_, nr_, nc_, r); }
//    void rotate_horiz(long r)    { ::rotate_horiz(rowp_, nr_, nc_, r); }
//
//    void rotate_vh(long vert, long horiz)  { ::rotate_vh(rowp_, nr_, nc_, vert, horiz); }
//
//    void zero2center()  { ::zero2center(rowp_, nr_, nc_); }
};
// -------------------------


template <typename Type>
array2d<Type>::array2d(ulong nr, ulong nc, Type *f/*=0*/)
    : nc_(nc), nr_(nr)
{
    if ( 0 != f )  // data supplied
    {
        f_ = f;
        myfq_ = false;
    }
    else
    {
        f_ = new Type[ nr_ * nc_ ];
        myfq_ = true;
    }

    rowp_ = new Type*[nr_];

    // setup row-pointers:
    rowp_[0] = f_;
    for (ulong i=1; i<nr_; ++i)  rowp_[i] = rowp_[i-1] + nc_;
}
// -------------------------


template <typename Type>
array2d<Type>::array2d(ulong nr, ulong nc, Type **rowp)
    : nc_(nc), nr_(nr)
{
    // Check whether memory is contiguous.
    ulong r = 0;
    Type *p = rowp[0];
    while (  r<nr_ )
    {
        ++r;
        p += nc_;
        if ( p != rowp[r] )  break;
    }
    bool mcq = ( r == nc_ );

    if ( mcq )  f_ = rowp[0];
    else        f_ = 0;

    rowp_ = new Type*[nr_];
    for (ulong j=0; j<nr; ++j)  rowp_[j] = rowp[j];

    myfq_ = false;
}
// -------------------------


template <typename Type1, typename Type2>
void copy(const array2d<Type1> &src,
          array2d<Type2> &dst)
{
    ::offset_copy((const Type1 **)src.rowp_, src.nr_, src.nc_,
                  dst.rowp_, dst.nr_, dst.nc_);
}
// -------------------------


//template <typename Type1, typename Type2>
//void copy(const array2d<Type1> &src,
//          array2d<Type2> &dst,
//          ulong coff, ulong roff)
//{
//    ::offset_copy((const Type1 **)src.rowp_, src.nr_, src.nc_,
//                  dst.rowp_, dst.nr_, dst.nc_,
//                  coff, roff);
//}
//// -------------------------



#endif  // !defined HAVE_ARRAY2D_H__
