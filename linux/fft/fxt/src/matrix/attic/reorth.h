#if !defined HAVE_REORTH_H__
#define      HAVE_REORTH_H__


#include "matrix/matrix.h"

#define  MAT  matrix<Type>

template <typename Type>
double orth_q(const MAT &m)
// Return quantity that reflects how much the matrix m
// deviates from being orthogonal.
{
    MAT mt( m );
    mt ^= m;
    mt.diag_subtract_val( 1.0 );  // = m * m^T - 1
    return  (double)mt.norm();
}
// -------------------------


template <typename Type>
double reorth_step(MAT &a, MAT *t=0)
// Multiply matrix a by (1+(1-A^T A)/2)
// making a closer to its nearest orthogonal natrix E
//
// If T is supplied it is used as temporary and
// the factor (1+(1-A^T A)/2) is stored upon return.
// Accumulate P = \prod{T_k} then E = A P
// and the polar decomposition of A  (A=W H)
// can be obtained as W=E,  H=W^T A
{
    MAT *tt = t;
    if ( 0==tt )  t = new MAT( a );
    else          (*t) = a;

    (*t).transpose();
    (*t) *= a;  // = A^T A

    (*t).negate();  //  = - A^T A
    (*t).diag_add_val( 1.0 ); // =  1 - A^T A  --> 0
    double  v = (double)(*t).norm();

    (*t) *= 0.5;  // = ( 1  - A^T A )/2  -->  0
    (*t).diag_add_val( 1.0 );  // = 1/2 * ( 3  - A^T A ) = (1+(1-A^T A)/2)  -->  1

    a *= (*t);    //  A = A ( 3  - A^T A )/2 = A (1+(1-A^T A)/2)

    if ( 0==tt )  delete t;

    return  v;  // (close to) zero when A (close to) orthogonal
}
// -------------------------


#undef  MAT


#endif  // !defined HAVE_REORTH_H__
