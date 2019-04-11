
#include "comb/ascent-nonflat-rgs.h"

#include "comb/comb-print.h"


#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Ascent sequences (restricted growth strings, RGS)
//% without flat steps (i.e., no two adjacent digits are equal), lexicographic order.
//% An ascent sequence is a sequence [d(1), d(2), ..., d(n)] where d(k)>=0
//% and d(k) <= asc([d(1), d(2), ..., d(k-1)]) and asc(.) counts the number
//% of ascents of its argument.
//% Cf. OEIS sequence A138265.

// Cf. seq/A218757-demo.cc for ascent sequences without flat steps by number of zeros
// Cf. comb/ascent-rgs-demo.cc for all ascent sequences

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 6;
    NXARG(n, "Length of strings");

    ascent_nonflat_rgs A(n);

    ulong ct = 0;


#ifdef TIMING
    A.first();
    do  { ++ct; }  while ( A.next() );
#else

    ulong j = n;
    do
    {
#if 0
        {  // limit max digit:
            const ulong *x = A.data();
            bool q = true;
            const ulong b = 2;
            for (ulong j=0; j<n; ++j)
                if ( x[j] > b )
                { q=false;  break; }
            if ( ! q )  continue;
        }
#endif

        ++ct;


#if 1
        cout << setw(4) << ct << ":  ";

        // print RGS:
        A.print("  ", true );
//        print_vec("  ", A.m_, n, true );
//        cout << setw(4) << A.num_ascents();

        cout << setw(4) << j;

        cout << endl;

        jjassert( A.OK() );
#endif
    }
    while ( (j=A.next()) );

#endif  // TIMING

    cout << " ct=" << ct;  // OEIS sequence A138265
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 15
arg 1: 15 == n  [Length of strings]  default=6
 ct=1704439030
./bin 15  8.63s user 0.00s system 99% cpu 8.634 total
 ==> 1704439030/8.63 == 197,501,625 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/ascent-nonflat-rgs-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/ascent-nonflat-rgs-demo.cc DEMOFLAGS=-DTIMING"
/// End:

