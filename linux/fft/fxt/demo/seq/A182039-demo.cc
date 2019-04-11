
// demo-is-self-contained

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% OEIS sequence A182039:
//% Number of orthogonal 2 x 2 matrices M in the ring Z/nZ.

//#define TIMING  // uncomment to disable printing

/*
? M=[a,b;c,d]
[a b]
[c d]


? M*M~
[a^2 + b^2  c*a + d*b]
[c*a + d*b  c^2 + d^2]
 ==
[1, 0]
[0, 1]
 */

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Ring Z/nZ");

    ulong ct = 0;

    for (ulong a=0; a<n; ++a)
    {
        const ulong a2 = a * a;
        for (ulong b=0; b<n; ++b)
        {
            const ulong b2 = b * b;
            if ( ((a2 + b2) % n) != 1UL )  continue;

            for (ulong c=0; c<n; ++c)
            {
                const ulong ca = c * a;
                const ulong c2 = c * c;

                for (ulong d=0; d<n; ++d)
                {
                    const ulong db = d * b;
                    if ( ((ca + db) % n) != 0UL )  continue;

                    const ulong d2 = d * d;
                    if ( ((c2 + d2) % n) != 1UL )  continue;

                    ++ct;
#ifndef TIMING
                    cout << setw(4) << ct << ":  [ " << a << ", " << b << ";  " << c << ", " << d << " ]" << endl;
#endif  // TIMING
                }
            }
        }
    }


    cout << " ct=" << ct;
//    cout << n << " " << ct;  // b-file
    cout << endl;


    return 0;
}
// -------------------------

/*
for n in $(seq 100); do ./bin $n | g ct= ; done | sed 's/ct=//'

0, 2, 8, 16, 8, 16, 16, 64, 24, 16, 24, 128, 24, 32, 64, 128, 32, 48,
40, 128, 128, 48, 48, 512, 40, 48, 72, 256, 56, 128, 64, 256, 192, 64,
128, 384, 72, 80, 192, 512, 80, 256, 88, 384, 192, 96, 96, 1024, 112,
80, 256, 384, 104, 144, 192, 1024, 320, 112, 120, 1024, 120, 128, 384,
512, 192, 384, 136, 512, 384, 256, 144, 1536, 144, 144, 320, 640, 384,
384, 160, 1024, 216, 160, 168, 2048, 256, 176, 448, 1536, 176, 384,
384, 768, 512, 192, 320, 2048, 192, 224, 576, 640
*/

/*

Timing: (AMD Phenom II X4 945 3000MHz)

  time for n in $(seq 1000); do ./bin $n; done | grep --line-buffered -v arg

for n in $(seq 1000); do; ./bin $n; done  3915.17s user 1.63s system 99% cpu 1:05:18.20 total
grep -v arg > tt  0.02s user 0.02s system 0% cpu 1:05:18.20 total

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A182039-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A182039-demo.cc DEMOFLAGS=-DTIMING"
/// End:
