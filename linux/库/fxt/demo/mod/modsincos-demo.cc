
#include "mod/mod.h"

#include "fxttypes.h"  // ulong
#include "nextarg.h"

//% Demo of cosine/sine modulo p.


int
main(int argc, char **argv)
{
    umod_t  m = 257;
    NXARG(m, "Modulus");

    mod::init(m);
    mod::print_info();
    cout << endl;
    mod_info_roots();
    cout << endl;
    cout << endl;

    mod_reset();  // we want to keep valgrind happy
//    delete [] mod::mtab;  // this is what mod_reset() does for valgrind

    return 0;
}
// -------------------------

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/modsincos-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/modsincos-demo.cc DEMOFLAGS=-DTIMING"
/// End:

