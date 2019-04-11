
#include "comb/catalan-rgs-to-noncrossing-setpart-rgs.h"
#include "comb/is-noncrossing-setpart-rgs.h"
#include "comb/catalan-rgs.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Compute RGS for noncrossing set partitions from Catalan RGS.
//% Lexicographic order.


// Cf. comb/catalan-rgs-demo.cc for Catalan RGS.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of elements in set");

    catalan_rgs C(n);
    ulong *P = new ulong[n];

    ulong ct = 0;
    do
    {
        ++ct;
        catalan_rgs_to_noncrossing_setpart_rgs(C.data(), n, P);

#ifndef TIMING
        cout << setw(4) << ct << ":";

        // print RGS:
        C.print("  ", true );
        print_vec("    ", P, n , true);

        print_setpart("    ", P, n, 0, 1);

        cout << endl;

        jjassert( C.OK() );
        jjassert( is_noncrossing_setpart_rgs(P, n) );
#endif  // TIMING
    }
    while ( C.next() );



    cout << " ct=" << ct;  // Catalan number n
    cout << endl;

    delete [] P;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.1:

 time ./bin 17
arg 1: 17 == n  [Number of elements in set]  default=5
 ct=129644790
./bin 17  10.08s user 0.00s system 99% cpu 10.090 total
 ==> 129644790/10.08 == 12,861,586 per second
(rather slow!)

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-rgs-to-noncrossing-setpart-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-rgs-to-noncrossing-setpart-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

