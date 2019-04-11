
#include "comb/perm-restrpref.h"  // class perm_restrpref

#include "perm/printcycles.h"
#include "comb/comb-print.h"
#include "perm/permq.h"

#include "comb/fact2perm.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "perm/permq.h"  // is_involution(), is_connected()
//#include "jjassert.h"

#include "nextarg.h"  // NXARG()

//% OEIS sequence A003043:
//% Number of Hamiltonian paths (or Gray codes) on n-cube with a marked starting node.
//% Computation as Permutations with restricted prefixes.
//% Also A059783: paths from vec(0) to vec(1).

//#define TIMING  // uncomment to disable printing

ulong *z;
// used here:
#ifdef TIMING
void visit(const ulong *, ulong, ulong)  { ; }
#else  // TIMING
void visit(const ulong *a, ulong n, ulong ct)
{
    cout << setw(4) << ct << ":";
    for (ulong i=0; i<n; ++i)  z[i] = a[i+1] - 1;
    print_perm("  ", z, n);
//    print_perm("  ", a+1, n);

    cout << endl;
}
// -------------------------
#endif  // TIMING


bool cond_gray(const ulong *a, ulong k)
// For n a power of two:
// A003043 Hamiltonian paths (or Gray codes)
//   on n-cube with a marked starting node.
{
    if ( k==1 ) return ( a[1]==1 );
    ulong t = (a[k]-1) ^ (a[k-1]-1);
    return ( 0==( t & (t-1) ) );
}
// -------------------------


ulong nn = 0;
ulong xct = 0;
bool cond_gray_path(const ulong *a, ulong k)
// For n a power of two:
// A059783 paths from vec(0) to vec(1) in n-dimensional hypercube
{
    if ( k==1 ) return ( a[1]==1 );
    ulong t = (a[k]-1) ^ (a[k-1]-1);
    if ( 0!=( t & (t-1) ) )  return false;

    if ( a[k]==nn )  // abuse of mechanism
    {
        ++xct;
        visit(a, k, xct);
        return false;
    }

    return true;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Permutations of {1, 2, ..., n}");

    z = new ulong[n];

    nn = n;  // for cond_gray_path()


    ulong c = 0;
    NXARG(c, "Condition function: "
          "\n      (0: A003043, Hamiltonian paths),"
          "\n      (1: A059783, paths from vec(0) to vec(1))"
//          "\n      (8: playground)"
          );

    perm_restrpref *perm;
    switch ( c )
    {
    case 0:
        cout << "A003043, Hamiltonian paths:" << endl;
        perm = new perm_restrpref(n, cond_gray, visit);  break;
    case 1:
        cout << "A059783, paths from vec(0) to vec(1)):" << endl;
        perm = new perm_restrpref(n, cond_gray_path, visit);  break;

//    case 9:
//        cout << "Playground:" << endl;
//        perm = new perm_restrpref(n, cond_gray, visit);  break;

    default:
        cout << "Error!" << endl;
        return 1;
    }

    ulong ct = perm->all();
    cout << " ct=" << ct << endl;

    if ( c==1 )  // for cond_gray_path()
        cout << " xct=" << xct << endl;

    delete perm;
    delete [] z;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A003043-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A003043-demo.cc DEMOFLAGS=-DTIMING"
/// End:

