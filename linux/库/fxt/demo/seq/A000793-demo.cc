
#include "comb/composition-nz-restrpref.h"
#include "aux0/gcd.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% OEIS sequence A000793:
//% Landau's function g(n): largest order of permutation of n elements.
//% Equivalently, largest lcm of (the parts of) partitions of n.
//% Also sequence A213206.

// Cf. comb/composition-nz-restrpref-demo.cc

//#define TIMING  // uncomment to disable printing



bool
cond_all(const ulong *a, ulong k)
// ==> A000793: Landau's function g(n); largest order of permutation of n elements.
// Equivalently, largest lcm of partitions of n.
{
    if ( k==0 )  return true;
    if ( a[k] < a[k-1] )  return false;
    return true;
}
// -------------------------

bool
cond_no_2(const ulong *a, ulong k)
// ==> A213206
{
    if ( a[k] == 2 )  return false;
    if ( k==0 )  return true;
    if ( a[k] < a[k-1] )  return false;
    return true;
}
// -------------------------

ulong n = 7;

bool
cond_no_n(const ulong *a, ulong k)
{
    if ( a[k] == n )  return false;
    if ( k==0 )  return true;
    if ( a[k] < a[k-1] )  return false;
    return true;
}
// -------------------------

int
main(int argc, char **argv)
{
    NXARG(n, "partitions of n (n>=1)");

    ulong c = 0;
    NXARG(c, "Condition function:"
          "\n      0 ==> all partitions,"
          "\n      1 ==> no part = n"
          "\n      2 ==> no part = 2"
          );


    composition_nz_restrpref P(n, cond_all);

    switch ( c )
    {
    case 0: P.first( cond_all );  break;
    case 1: P.first( cond_no_n );  break;
    case 2: P.first( cond_no_2 );  break;

    default:  cout << "Not a valid condition!" << endl;
        return 1;
    }

    ulong ct = 0;
    ulong r = 1;  // max order so far
    const ulong *x = P.data();
    while ( P.valid() )
    {

        ulong m = P.num_parts();

#ifndef TIMING
        ++ct;
#if 0
        cout << "[" << setw(2) << ct << "]";  // format for OEIS examples
#else
        cout << setw(4) << ct << ":";
        cout << "  [" << setw(2) << m << "]";
#endif

        P.print("  ");


//        jjassert( P.OK() );
#endif  // TIMING

        ulong t = 1;
        for (ulong j=0; j<m; ++j)  t = lcm(t, x[j]);
        if ( t > r )  r = t;

#ifndef TIMING
        cout << "  " << t;
        cout << endl;
#endif  // TIMING

        P.next();
    }

    cout << " ct=" << ct << endl;
    cout << " r=" << r << endl;

    return 0;
}
// -------------------------

//  echo $(for n in $(seq 1 20); do ./bin $n 0; done | grep r= ) | sed 's/ r=/, /g;'



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A000793-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A000793-demo.cc DEMOFLAGS=-DTIMING"
/// End:

