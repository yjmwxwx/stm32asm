
#include "comb/partition-gen.h"

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% Generate all integer partitions, with parts repeated at most r times.

//#define TIMING  // uncomment to disable printing


#define USE_COND

int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Partitions of n (n>=1)");
    jjassert( n>=1 );
#ifdef USE_COND
    ulong r = 1;
    NXARG(r, "Partitions with parts repeated at most r times (0==> no restriction)");
#endif  // USE_COND

    partition_gen pp(n);
    ulong ct = 0;

    while ( pp.next() < n )
    {
#ifdef TIMING
        ++ct;  // just count, no condition applied
#else

#ifdef USE_COND
        bool q = true;
        if ( r )
        {
            for (ulong j=0; j<n; ++j)
            {
                if ( pp.pc_[j] > r )  { q = false; break; }
                // r=1: OEIS sequence A000009
                // r=2: A000726
                // r=3: A001935
                // r=4: A035959
                // r=5: A219601, not A097797
                // r=6: A035985 ?
                // r=7: A000000, neither A027342, nor A036007
                // r=8: A104502
                // r=9: A000000
            }
        }

        if ( q )
        {
#endif  // USE_COND
            ++ct;
            cout << "     " << setw(2) << ct << ": ";
            cout << setw(4) << pp.n_ << " == ";
            pp.print2();
            cout << "  ==  ";
            pp.print();
            cout << endl;
#ifdef USE_COND
        }
#endif  // USE_COND

#endif  // TIMING
    }

//    cout << " " << n << ": ";
    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing:
 % time ./bin 100
arg 1: 100 == nmax  [Shown all partitions for n<=nmax]  default=6
 100:  ct=190569292
./bin 100  10.55s user 0.04s system 99% cpu 10.615 total
 ==> 17,952,830 part/sec
*/

/*
Counting restricted partitions:
% for r in $(seq 1 5); do echo $(for k in $(seq 1 30); do ./bin $k $r | g ct; done | cut -d= -f2); done
 1 1 2 2 3 4 5 6 8 10 12 15 18 22 27 32 38 46 54 64 76 89 104 122 142 165 192 222 256 296
 1 2 2 4 5 7 9 13 16 22 27 36 44 57 70 89 108 135 163 202 243 297 355 431 513 617 731 874 1031 1225
 1 2 3 4 6 9 12 16 22 29 38 50 64 82 105 132 166 208 258 320 395 484 592 722 876 1060 1280 1539 1846 2210
 1 2 3 5 6 10 13 19 25 34 44 60 76 100 127 164 205 262 325 409 505 628 769 950 1156 1414 1713 2081 2505 3026
 1 2 3 5 7 10 14 20 27 37 49 65 85 111 143 184 234 297 374 470 586 729 902 1113 1367 1674 2042 2485 3013 3645
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/partition-gen-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/partition-gen-demo.cc DEMOFLAGS=-DTIMING"
/// End:

