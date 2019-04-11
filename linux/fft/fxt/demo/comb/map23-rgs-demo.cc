
#include "comb/map23-rgs.h"

#include "comb/comb-print.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Restricted growth strings (RGS) for maps
//% f: [n] -> [n] with f(x)<=x and f(f(x)) == f(f(f(x))).
//% Lexicographic order.
//% Cf. OEIS sequence A187761.

// 1, 1, 2, 6, 23, 106, 568, 3459, 23544, 176850, 1451253, 12904312,
//   123489888, 1264591561, 13790277294, 159466823794, 1948259002647

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of digits (cardinality of the set)");

    map23_rgs M(n);

    ulong ct = 0;

#ifdef TIMING
    M.first();
    do  { ++ct; }  while ( M.next() );
#else  // TIMING

    ulong j = 0;
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";
        M.print("    ", true );
        cout << setw(4) << j;
        cout << endl;
    }
    while ( (j=M.next()) );

#endif  // TIMING

    cout << " ct=" << ct;
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 13
arg 1: 13 == n  [Number of digits (cardinality of the set)]  default=5
 ct=1264591561
./bin 13  4.35s user 0.00s system 99% cpu 4.353 total
  ==> 1264591561/4.35 == 290,710,703 per second

*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/map23-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/map23-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

