
#include "bpol/lfsr.h"  // class lfsr
#include "matrix/matrix.h"  // class matrix
#include "aux1/copy.h"  // copy_cyclic()

#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "fxtalloca.h"  // ALLOCA
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Hadamard matrices by maximum length shift register sequences (SRS)


typedef matrix<int>  Smat;  // matrix with integer entries

void
print01(int v)
{
    switch ( v )
    {
    case  0:  cout << "0";  break;
    case +1:  cout << "+";  break;
    case -1:  cout << "-";  break;
    default:
        cout << v;
//        cout << endl;
//        cout << "OUCH: m[" << r << ", " << c << "] == " << v ;
//        cout << endl;
//        jjassert(0);
    }
}
// -------------------------


void
smatprint(const char *bla, Smat &m)
{
    cout << bla << endl;
    for (ulong r=0; r<m.num_rows(); ++r)
    {
        for (ulong c=0; c<m.num_cols(); ++c)
        {
            cout << " ";
            int v = m.get(r, c);
            print01(v);
        }
        cout << endl;
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "n, a NxN Hadamard matrix will be computed where N=2**n.");
    ulong N = 1UL << n;

    RESTARGS("Optionally supply nonzero coefficients for poly used for SRS.");
    ulong p = 0;
    for (ulong k=2;  (ulong)argc>k;  ++k)  p |= (1UL << strtoul(argv[k], 0, 10));
    if ( 0!=p )  p |= (1UL<<n);

    // --- create signed SRS:
    //    int vec[N-1];
    ALLOCA(int, vec, N-1);
    lfsr S(n, p);  // p is a primitive polynomial of degree n
    for (ulong k=0; k<N-1; ++k)
    {
        ulong x = 1UL & S.get_a();
        vec[k] = ( x ? -1 : +1 );
        S.next();
    }

    cout << "Signed SRS:" << endl;
    cout << "  ";
    for (ulong k=0; k<N-1; ++k)  { cout << " "; print01(vec[k]); }
    cout << endl;

    // --- create Hadamard matrix:
    Smat H(N);
    for (ulong c=0; c<N; ++c)  H.set(0, c, +1);  // first row = [1,1,1,...,1]
    for (ulong r=1; r<N; ++r)
    {
        H.set(r, 0, +1);  // first column = [1,1,1,...,1]^T
//        copy_cyclic(vec, H.rowp_[r]+1, N-1, r-1);
//        copy_cyclic(vec, H.rowp_[r]+1, N-1, N-r);
        copy_cyclic(vec, H.row(r)+1, N-1, N-r);
    }

    smatprint("Hadamard matrix H:", H);


    // Make sure H is unitary:
    bool q = H.is_unitary((int)N);
    if ( !q ) { Smat T(H); T.transpose(); T*=H; smatprint("H^t * H:", T); }
    jjassert( q );


//    // --- create conference matrix (works for n=1,2,3 only):
//    Smat C(H);
//    C.set_diag(0);
//    smatprint("Conference matrix C:", C);
//
//    // Make sure C is unitary:
//    q = C.is_unitary(N-1);
////    if ( !q ) { Smat T(C); T.transpose(); T*=C; smatprint("C^t * C:", T); }
//    jjassert( q );

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/hadamard-srs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/hadamard-srs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

