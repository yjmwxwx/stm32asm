
#include "bits/bitrotate.h"  // bit_rotate_left
#include "bits/bitcyclic-minmax.h"  // bitcyclic_min()
#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"
//#include "jjassert.h"

#include "nextarg.h"


//% necklaces via cyclic shifts and complements (sigma-tau search)
// Frank Ruskey, Carla Savage, Terry MinYih Wang:
// {Generating Necklaces},
// J. Algorithms, vol.13, pp.414-430, 1992.


//#define TIMING  // uncomment to disable printing


ulong n, ct;

#ifdef TIMING
void visit(ulong)  { ; }
#else  // TIMING
void visit(ulong x)
{
    ++ct;
    cout << setw(4) << ct << ":";
    print_bin("  ", x, n);
    cout << endl;
}
// -------------------------
#endif  // TIMING

inline ulong sigma(ulong x)  { return bit_rotate_left(x, 1, n); }
inline ulong tau(ulong x)  { return  x ^ 1; }

void search(ulong y)
{
    visit(y);
    ulong t = y;
    while ( 1 )
    {
        t = sigma(t);
        ulong x = tau(t);
        if ( (x&1) && (x == bit_cyclic_min(x, n)) )  search(x);
        else  break;
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    n = 7;
    NXARG(n, "Number of bits");

    ct = 0;
    search(1);
    cout << " ct=" << ct;
    cout << endl;
    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 32
arg 1: 32 == n  [Number of bits]  default=7
 ct=134219795
./bin 32  27.09s user 0.13s system 99% cpu 27.244 total
 ==> 134219795/27.09 == 4,954,588 per second

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/necklace-sigma-tau-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/necklace-sigma-tau-demo.cc DEMOFLAGS=-DTIMING"
/// End:
