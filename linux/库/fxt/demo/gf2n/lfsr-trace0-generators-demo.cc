
#include "bpol/mersenne-coprime.h"

#include "bpol/bitpolmod-arith.h"  // bitpolmod_times_x()
#include "bpol/poly-tab.h"  // minweight_primpoly[]
#include "bpol/gf2n-trace.h"  // gf2n_fast_trace()

#include "aux0/gcd.h"  // for checking only

#include "bits/bitsperlong.h"
#include "bits/print-bin.h"
#include "nextarg.h"
#include "fxttypes.h"  // ulong
#include "jjassert.h"


//% Count primitive elements with trace==0 in GF(2^n).
//% Cf. OEIS sequences A192211 and A152049.
//% Fast method using class mersenne_coprime.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 8;
    NXARG(n, "Bits in word (n>=2)");
    jjassert( n>=2 );
    jjassert( n<BITS_PER_LONG );

    const ulong c = minweight_primpoly[n];
    const ulong h = 1UL << (n-1);

    const ulong g = 2;  // == 'x'
    const ulong tv = gf2n_trace_vector(g, c, h);

    umod_t mm = (((umod_t)1) << n) - 1;

    mersenne_coprime MC(n);

    umod_t k = 1;
    ulong ct = 0;
    ulong f = g;  // 'x'
    bool cq = true;  // first is coprime
//    while ( MC.pos() != mm )
    while ( k != mm )
    {
#ifndef TIMING
//        cout << setw(4) << k << ": cq=" << cq << endl;
        jjassert ( k == MC.pos() );
        jjassert ( cq == ( 1==gcd(k, mm) ) );
#endif

        if ( cq )
        {
            if ( 0 == gf2n_fast_trace(f, tv) )
                ++ct;
        }

        f = bitpolmod_times_x(f, c, h);

        ++k;
        cq = MC.next();
    }

    cout << "  ct=" << ct;
    cout << endl;

//    cout << setw(7) << k << ": "; print_bin("  ", f, n);  cout << endl;  // ::
    jjassert( f == 1UL );


    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

% time ./bin 26
arg 1: 26 == n  [Bits in word (n>=2)]  default=8
  ct =44717400
./bin 26  0.19s user 0.00s system 99% cpu 0.196 total
 ==> 2^26/0.19 == 353,204,547 per second

% time ./bin 27
arg 1: 27 == n  [Bits in word (n>=2)]  default=8
  ct =56730861
./bin 27  0.65s user 0.00s system 99% cpu 0.649 total
 ==> 2^26/0.65 == 103,244,406 per second

% time ./bin 28
arg 1: 28 == n  [Bits in word (n>=2)]  default=8
  ct =66385676
./bin 28  3.20s user 0.00s system 99% cpu 3.202 total
 ==> 2^28/3.20 == 83,886,080 per second

% time ./bin 29
arg 1: 29 == n  [Bits in word (n>=2)]  default=8
  ct =266917769
./bin 29  2.27s user 0.00s system 99% cpu 2.269 total
 ==> 2^29/2.27 == 236,507,009 per second

Speed depends on number of times the priority-queue needs to reschedule:
 for (e=1,64,m=2^e-1;print([e,1.0*(m-eulerphi(m))/m]))
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/gf2n"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/gf2n/lfsr-trace0-generators-demo.cc"
/// make-target2: "1demo DSRC=demo/gf2n/lfsr-trace0-generators-demo.cc DEMOFLAGS=-DTIMING"
/// End:
