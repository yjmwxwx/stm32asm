
#include "matrix/matrix.h"  // class matrix
#include "aux1/copy.h"  // copy_cyclic()

#include "fxtio.h"
//#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "fxtalloca.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()

//% Conference and Hadamard matrices by quadratic residues


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
is_unitary(Smat H)
{
    Smat T(H);
    T.transpose();
    T *= H;
    int dg = T.get(0, 0);
    bool q = T.is_diag(dg);
    if ( !q )  smatprint("M^t * M:", T);
    return  ( q ? dg : 0 );
}
// -------------------------

void
doit(ulong q)
{
    cout << endl;
    int y = ( 1==q%4 ? +1 : -1 );
    ulong Q = q+1;

    // --- create table of quadratic characters modulo q:
//    int vec[q];
    ALLOCA(int, vec, q);
    fill<int>(vec, q, -1);  vec[0] = 0;
    for (ulong k=1; k<(q+1)/2; ++k)  vec[(k*k)%q] = +1;
//    for (ulong k=0; k<Q; ++k)  vec[k] = kronecker(k, q);  // Kronecker symbol

    cout << "Quadratic characters modulo " << q << ":" << endl;
    cout << "  ";
    for (ulong k=0; k<q; ++k)  { cout << " "; print01(vec[k]); }
    cout << endl;

    // --- create Q x Q conference matrix:
    Smat C(Q);
    C.set(0, 0, 0);
    for (ulong c=1; c<Q; ++c)  C.set(0, c, +1);  // first row = [1,1,1,...,1]
    for (ulong r=1; r<Q; ++r)
    {
        C.set(r, 0, y);  // first column = +-[1,1,1,...,1]^T
//        copy_cyclic(vec, C.rowp_[r]+1, q, Q-r);
        copy_cyclic(vec, C.row(r)+1, q, Q-r);
    }
    cout << Q << "x" << Q << " ";
    smatprint("conference matrix C:", C);
    jjassert( (int)q==is_unitary(C) );


    // --- create a N x N Hadamard matrix:
    ulong N = ( y<0 ? Q : 2*Q );
    Smat H(N);
    if ( N==Q )
    {
        copy(C, H);
        H.diag_add_val(1);
    }
    else
    {
        Smat K2(2);  K2.fill(+1); K2.set(1, 1, -1);  // K2 = [+1,+1; +1,-1]
        H.kronecker(K2, C);  // Kronecker product of matrices
        for (ulong k=0; k<Q; ++k)  // adjust diagonal of sub-matrices
        {
            ulong r, c;
            r=k;   c=k;   H.set(r, c, H.get(r, c)+1);
            r=k;   c=k+Q; H.set(r, c, H.get(r, c)-1);
            r=k+Q; c=k;   H.set(r, c, H.get(r, c)-1);
            r=k+Q; c=k+Q; H.set(r, c, H.get(r, c)-1);
        }
    }
    cout << N << "x" << N << " ";
    smatprint("Hadamard matrix H:", H);
    jjassert( (int)N==is_unitary(H) );
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong qv[] = {11, 5, 0};
    cout << "Argument q  must an odd prime." << endl;
    cout << " A QxQ conference matrix will be computed where Q=q+1." << endl;
    cout << " A NxN Hadamard matrix will create where" << endl;
    cout << "   N=q+1 if q%4==1,  N=2*(q+1) if q%4=3." << endl;
    cout << "Optional: more odd primes for more matrices." << endl;

    if ( 1==argc )
    {
        for (ulong k=0, q;  (q=qv[k]);  ++k)  doit(q);
    }
    else
    {
        for (ulong k=1; k<(ulong)argc; ++k)  doit(strtoul(argv[k], 0, 10));
    }

    return 0;
}
// -------------------------

/*
 for p in $(primes 3 101); do echo $p": "; ./bin $p  2>&1 >/dev/null || break; done
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/conference-quadres-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/conference-quadres-demo.cc DEMOFLAGS=-DTIMING"
/// End:

