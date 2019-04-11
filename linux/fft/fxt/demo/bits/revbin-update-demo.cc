
#include "bits/revbin-upd.h"

#include "bits/print-bin.h"
#include "nextarg.h"

#include "fxtio.h"
#include "jjassert.h"
#include "fxttypes.h"  // ulong

//% Revbin-update routines.


//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Reverse the first 2**n binary words.");
    const ulong n = 1UL<<ldn;
    const ulong h = n/2;
    make_revbin_upd_tab(h);


#ifdef TIMING
    ulong wh = 0;
    NXARG(wh, "TIMING: Which routine: 0=>xor-tables,  1=>bit-wise.");
    ulong r = 0;
    if ( wh )
    {
        cout << "revbin_upd():" << endl;
        // 5.915 sec for 2**30 words:
        for (ulong k=0; k<n-1; ++k)  { r = revbin_upd(r, h); }
    }
    else
    {
        cout << "Using revbin_upd_tab[]:" << endl;
        // 6.173 sec for 2**30 words:
        for (ulong k=0; k<n-1; ++k)  { r = revbin_tupd(r, k); }
    }
    if ( r==239 )  return 1;  // dummy

#else
    ulong r1 = 0,  r2 = 0;
    for (ulong k=0; k<n-1; ++k)
    {
        print_bin("  ", k, ldn);
        print_bin("  :  ", r1, ldn);
        cout << endl;
//        print_bin("  ", r2, ldn);  cout << endl;
        jjassert( r1==r2 );

        r1 = revbin_upd(r1, h);
        r2 = revbin_tupd(r2, k);
    }
#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 1
arg 1: 30 == ldn  [Reverse the first 2**n binary words.]  default=5
arg 2: 1 == wh  [TIMING: Which routine: 0=>xor-tables,  1=>bit-wise.]  default=0
revbin_upd():
./bin 30 1  2.81s user 0.00s system 99% cpu 2.809 total

 time ./bin 30 0
arg 1: 30 == ldn  [Reverse the first 2**n binary words.]  default=5
arg 2: 0 == wh  [TIMING: Which routine: 0=>xor-tables,  1=>bit-wise.]  default=0
Using revbin_upd_tab[]:
./bin 30 0  1.78s user 0.00s system 99% cpu 1.785 total

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/revbin-update-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/revbin-update-demo.cc DEMOFLAGS=-DTIMING"
/// End:

