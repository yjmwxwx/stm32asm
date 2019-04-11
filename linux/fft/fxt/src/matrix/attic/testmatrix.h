#if !defined HAVE_TESTMATRIX_H__
#define      HAVE_TESTMATRIX_H__

#include "matrix/matrix.h"
#include "matrix/matrixsymmetryq.h"

#include "fxtio.h"


#define  MAT  matrix<Type>


template <typename Type>
bool report_symmetry(const MAT &A, const Type eps=1e-8)
// convenient quick hack
{
    bool ret = false;
#define  CHK(x) if ( is_ ## x (A, eps) )  { cout << "  is "  #x << endl;  ret = true; }
    CHK(symmetric);
    CHK(anti_symmetric);
    CHK(minor_symmetric);
    CHK(minor_anti_symmetric);
    CHK(circulant);
    CHK(toeplitz);
#undef  CHK

    return  ret;
}
// -------------------------

#undef  MAT


#endif // !defined HAVE_TESTMATRIX_H__
