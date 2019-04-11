
#include "comb/weakly-unimodal-rgs-lex.h"
#include "comb/is-unimodal.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Weakly unimodal RGS (restricted growth strings), lexicographic order.
//% Cf. OEIS sequences:
//%  A088536: unimodal maps [1..n] -> [1..n].
//%  A225006: unimodal maps [1..n] -> [1..n+1].
//%  A000124: unimodal maps [1..n] -> [1,2].
//%  A002412: unimodal maps [1,2,3] -> [1..n].
//%  A006324: unimodal maps [1,2,3,4] -> [1..n].

//  A000000: unimodal maps [1..n] -> [1..n+2] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1..2*n] (not in the OEIS).
//  A000000: unimodal maps [1..2*n] -> [1..n] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1..n-1] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1..floor(n/2)] (not in the OEIS).
//  A000000: unimodal maps [1..n] -> [1,2,3] (not in the OEIS).


//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "length of RGS (n>=1)");

    ulong m = 3;
    NXARG(m, "number of allowed digit values (m>=2)");

    weakly_unimodal_rgs_lex W(n, m);

    ulong ct = 0;

#ifdef TIMING
#ifdef WEAKLY_UNIMODAL_RGS_LEX_M1
    cout << "WEAKLY_UNIMODAL_RGS_LEX_M1 is defined" << endl;
#endif
    do  { ++ct; }  while ( W.next() );
#else

    ulong j = 1;  // position of leftmost change
    do
    {
#if 0  // With args n n: OEIS sequence A014300:
        if ( ! is_strongly_unimodal(W.data(), n) )  continue;
#endif
        ++ct;

        cout << setw(4) << ct << ":";
        W.print("  ", true);
        cout << "  " << j - 1;
//        cout << "  mp=" << W.mp_;
//        cout << "  mv=" << W.mv_;
//        cout << "  tr=" << W.tr_;
        cout << endl;

        jjassert( W.OK() );
    }
    while ( (j=W.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 13 13
arg 1: 13 == n  [length of RGS]  default=5
arg 2: 13 == m  [number of allowed digit values (m>=2)]  default=3
  ct=2155894508
./bin 13 13  8.16s user 0.00s system 99% cpu 8.168 total
 ==> 2155894508/8.16 == 264,202,758 per second

 time ./bin 13 13
arg 1: 13 == n  [length of RGS]  default=5
arg 2: 13 == m  [number of allowed digit values (m>=2)]  default=3
WEAKLY_UNIMODAL_RGS_LEX_M1 is defined
  ct=2155894508
./bin 13 13  10.58s user 0.00s system 99% cpu 10.582 total
 ==> 2155894508/10.58 == 203,770,747 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/weakly-unimodal-rgs-lex-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/weakly-unimodal-rgs-lex-demo.cc DEMOFLAGS=-DTIMING"
/// End:

