
#include "comb/motzkin-step-rgs-lex.h"
#include "comb/is-motzkin-step-rgs.h"
//#include "comb/is-catalan-step-rgs.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Motzkin step RGS (restricted growth strings), lexicographic order.
//% RGS are a[] such that a[k] >= a[k-1] (weakly ascending), a[k]<=k, and
//% a[k] - a[k-1] != 1 (no increments by 1).
//% Same as: rising factorial numbers where the digits are sorted
//% where increments by 1 are disallowed.
//% Cf. OEIS sequence A001006.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Motzkin (step-)RGS for paths from (0,0) to (n,n)");

    motzkin_step_rgs_lex C(n);

    ulong ct = 0;

#ifdef TIMING
//    bool bq = 0;
//    NXARG(bq, "With benchmark: whether do generate in backward order");
//    if ( !bq )
//    {
        C.first();
//        cout << "forward:" << endl;
        do  { ++ct; }  while ( C.next() );
//    }
//    else
//    {
//        C.last();
//        cout << "backward:" << endl;
//        do  { ++ct; }  while ( C.prev() );
//    }
#else

    bool pq = 0;
    NXARG(pq, "Whether do draw path (as ASCII art)");

//    C.last();
    ulong j = 0;  // position of leftmost change
    do
    {
        ++ct;

        cout << setw(4) << ct << ":";
        C.print("  ", true);
        cout << "  " << j;
        cout << endl;

        if ( pq )
        {
            C.print_aa();
            cout << endl;
        }

        jjassert( C.OK() );
    }
    while ( (j=C.next()) );
//    while ( (j=C.prev()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 23
arg 1: 23 == n  [Motzkin (step-)RGS for paths from (0,0) to (n,n)]  default=6
 ct=1129760415
./bin 23  6.02s user 0.00s system 99% cpu 6.019 total
 ==> 1129760415/6.02 == 187,667,843 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/motzkin-step-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/motzkin-step-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

