
#include "mod/mod.h"

#include "fxttypes.h"  // ulong
#include "nextarg.h"

//% Demo of mod_init(): properties of (Z/mZ)*


umod_t mm[] = {
    4,
    17,
    18,
    31,
    32,
    121,
    2047,
    65537,
//    0x3f40f80000000001ULL,  // valgrind chokes on this one
//    0x3fffc00000000001ULL,  // valgrind chokes on this one
    0
};
// -------------------------

int
main(int argc, char **argv)
{
    umod_t m = 0;
    NXARG(m, "Modulus,  0==>use all moduli from list");
    if ( 0!=m )
    {
        mm[0] = m;
        mm[1] = 0;
    }

    for (ulong k=0; mm[k]; ++k)
    {
        mod::init( mm[k] );
        mod::print_info();
        cout << endl;
    }
    cout << endl;

    mod_reset();  // we want to keep valgrind happy
//    delete [] mod::mtab;  // this is what mod_reset() does for valgrind

    return 0;
}
// -------------------------

/*
valgrind used to BREAK this demo (killing arithmetic).
This seems to be fixed with versions >=3.50.
Note of 2012-January-10: commented out the two large moduli,
  valgrind does not like them.
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/modinfo-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/modinfo-demo.cc DEMOFLAGS=-DTIMING"
/// End:

