
#include "bits/grsnegative.h"
#include "ds/bitarray.h"
#include "bits/print-bin.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "nextarg.h"
#include "jjassert.h"


//% OEIS sequence A005943:
//% Length-n subwords of the Golay-Rudin-Shapiro (GRS) sequence.

//#define TIMING  // uncomment to disable printing

int
main(int argc, char **argv)
{
    ulong b = 7;
    NXARG(b, "Words with b bits.");
    jjassert( b <= BITS_PER_LONG );

    const ulong B = 1UL << b;
    const ulong m = B - 1;  // mask

    ulong n = 20;
    NXARG(n, "Use GRS sequence of length 2^n.");
    const ulong N = 1UL << n;

    bitarray W(B);
    W.clear_all();

    ulong w = 0;
    for (ulong k=0; k<b; ++k)  // first word
    {
        w <<=1;
        w |= grs_negative_q(k);
    }
    w &= m;
    W.set(w);

    for (ulong k=b; k<N; ++k)
    {
        w <<= 1;
        w |= grs_negative_q(k);
        w &= m;
        W.set(w);
    }

#ifndef TIMING
    for (ulong k=0, z=0; k < W.size(); ++k)
    {
        if ( W.test(k) )
        {
            ++z;
            cout << setw(4) << z << ": ";
            print_bin("", k, b);
            cout << endl;
        }
    }
#endif  // TIMING

    const ulong ct = W.count_ones();
    cout << "ct= " << ct << endl;
    return 0;
}
// -------------------------

/*
time for n in $(seq 1 32); do ./bin $n 32; done
approx 13 minutes
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A005943-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A005943-demo.cc DEMOFLAGS=-DTIMING"
/// End:
