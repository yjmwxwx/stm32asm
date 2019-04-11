
#include "aux2/transpose.h"
#include "aux2/transpose2.h"
#include "aux2/copy2d.h"
//#include "aux1/auxprint.h"
//#include "aux1/aux1double.h"
#include "perm/permq.h"  // is_identity()

#include "fxtio.h"

#include "fxttypes.h"
#include "fxtalloca.h"

#include <cstdlib>  // strtoul()


#include "test.h"  // last to include



#define SRC(k) (((unsigned long long)(k)*nc)%n1) // note: overflow if k*nc >= 2^64
template <typename Type>
int
is_transposed(const Type *f, ulong nr, ulong nc)
// check whether array has values as if filled
// with set_seq(f, nr*nc, 0, 1) and then transposed
{
    ulong n = nr * nc;
    ulong n1 = n - 1;
    if ( n<=2 )  return  1;

//    if ( (1==nr) || (1==nc) )  return is_seq(f, n);
    if ( (1==nr) || (1==nc) )  return is_identity(f, n);

    for (ulong k=0; k<n1; ++k)
    {
        ulong t = SRC(k);
        if ( f[k] != t )
        {
            cout << " element # " << k
                 << " should be == " << t
                 << "  but equals " << f[k] << endl;
            return 0;
        }
    }

    return  1;
}
// -------------------------
#undef SRC

template <typename Type>
void
test_print2d(const Type *f, ulong nr, ulong nc)
{
//    cout.precision(21);

    for (ulong k=0,idx=0; k<nr; ++k)
    {
        cout << k << ":  ";
        for (ulong j=0; j<nc; ++j,++idx)
        {
            cout << "(# "<< idx << ")=";
            cout << f[idx] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    cout << "Running tests for permutations ... " << endl;

    ulong minldn = 0, maxldn = 14;
    if ( argc>1 )  minldn = strtoul(argv[1], 0, 10);
    if ( argc>2 )  maxldn = strtoul(argv[2], 0, 10);

    ulong n = 1UL<<maxldn;
    double *tar = new double[n];
    double *fr = new double[n];
    double *gr = new double[n];
    const double *const ar = tar;

    for (ulong ldn=minldn; ldn<=maxldn; ++ldn)
    {
        n = 1UL<<ldn;
        cout << "====================  LDN = " << ldn
             << "   N = " << n << " :" << endl;

        for (ulong ldnr=0; ldnr<=ldn; ++ldnr)
        {
            ulong ldnc = ldn - ldnr;
            ulong nr = (1UL<<ldnr);
            ulong nc = (1UL<<ldnc);

            set_seq(tar, n, 0.0, 1.0);
            cout << "\n----- nr = " << nr << "  nc = " << nc << " : -----" << endl;

            EQUIV_REAL( acopy(ar, fr, n);
                        acopy(ar, gr, n);
                        transpose(gr, nr, nc);
                        transpose(gr, nc, nr); );

            EQUIV_REAL( acopy(ar, fr, n);
                        acopy(ar, gr, n);
                        transpose2(gr, nr, nc, 0);
                        transpose2(gr, nc, nr, 0); );

            EQUIV_REAL( acopy(ar, fr, n);
                        acopy(ar, gr, n);
                        transpose(gr, nr, nc, 0);
                        transpose(gr, nc, nr, 0); );

            EQUIV_REAL( acopy(ar, fr, n); transpose(fr, nr, nc);
                        acopy(ar, gr, n); transpose(gr, nr, nc);  );


//            acopy(ar, fr, n); transpose(fr, nr, nc);
//            if ( 0==is_transposed(fr, nr, nc) )
//            {
//                test_print2d(ar, nr, nc);
//                test_print2d(fr, nr, nc);
//                test_print2d(fr, nc, nr);
//                exit(33);
//            }

        }
    }

    cout << "\nOK, all passed." << endl;
    return 0;
}
// -------------------------

