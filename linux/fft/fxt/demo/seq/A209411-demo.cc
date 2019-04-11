
// demo-is-self-contained

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% OEIS sequence A209411:
//% Number of 2 x 2 matrices M such that M*transpose(M) == 0 (mod n).


//#define TIMING  // uncomment to disable printing

/*
? M=[a,b;c,d]
[a b]
[c d]


? M*M~
[a^2 + b^2  c*a + d*b]
[c*a + d*b  c^2 + d^2]
 ==
[0, 0]
[0, 0]
 */

int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Ring Z/nZ");

    ulong ct = 0;

    for (ulong a=0; a<n; ++a)
    {
        const ulong a2 = a * a;
        for (ulong b=0; b<n; ++b)
        {
            const ulong b2 = b * b;
            if ( ((a2 + b2) % n) != 0UL )  continue;

            for (ulong c=0; c<n; ++c)
            {
                const ulong ca = c * a;
                const ulong c2 = c * c;

                for (ulong d=0; d<n; ++d)
                {
                    const ulong db = d * b;
                    if ( ((ca + db) % n) != 0UL )  continue;

                    const ulong d2 = d * d;
                    if ( ((c2 + d2) % n) != 0UL )  continue;

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

1, 4, 1, 16, 49, 4, 1, 64, 81, 196, 1, 16, 337, 4, 49, 256, 577, 324,
1, 784, 1, 4, 1, 64, 1825, 1348, 81, 16, 1681, 196, 1, 1024, 1, 2308,
49, 1296, 2737, 4, 337, 3136, 3361, 4, 1, 16, 3969, 4, 1, 256, 2401,
7300, 577, 5392, 5617, 324, 49, 64, 1, 6724, 1, 784, 7441, 4, 81,
4096, 16513, 4, 1, 9232, 1, 196, 1, 5184, 10657, 10948, 1825, 16, 1,
1348, 1, 12544, 6561, 13444, 1, 16, 28273, 4, 1681, 64, 15841, 15876,
337, 16, 1, 4, 49, 1024, 18817, 9604, 81, 29200


for n in $(seq 500); do ./bin $n; done | grep --line-buffered -v arg


*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A209411-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A209411-demo.cc DEMOFLAGS=-DTIMING"
/// End:
