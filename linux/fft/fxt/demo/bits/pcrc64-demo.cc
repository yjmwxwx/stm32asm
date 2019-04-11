
#include "bits/pcrc64.h"

#include "bits/print-bin.h"
#include "fxtio.h"
#include "nextarg.h"
#include "fxttypes.h"
#include "jjassert.h"

//% Parallel Cyclic Redundancy Check (CRC)


//#define TIMING  // uncomment to disable printing

//#define Type ulong
//#define Type uint
#define Type ushort
//#define Type uchar

void
Print(const pcrc64<Type> &P, const ulong pn)
{
    for (uint k=0; k<64; ++k)
    {
        cout << setw(3) << k << ":";
        print_bin("  ", P.x_[k], pn );
        cout << endl;
    }
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 32768;
    NXARG(n, "Will feed values 0,1,2...,n-1 into CRC");
    const ulong pn = 8 * sizeof(Type);

    pcrc64<Type> P;
    for (ulong k=0; k<n; ++k)  P.word_in((Type)k);

#ifndef TIMING
    Print(P, pn);
    cout << endl;
#else
    cout << " nbytes= " << (sizeof(Type) * n) << endl;
//    cout << "Bits per word =" << 8*sizeof(Type) << endl;
#endif

    print_bin(" sum= ", P.sum(), pn );
    cout << endl;

    return 0;
}
// -------------------------

/*
Timing:

 With Type ulong (64 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 8589934592
 sum= 1111111111111111111111111111111111..1..1....1...1.1...11.1..11.1
./bin $((1<<30))  4.35s user 0.03s system 99% cpu 4.373 total
 ==> 8589934592/2^30/4.35 == 1.9746 GB / sec

 With Type uint (32 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 4294967296
 sum= 11..1..1....1...1.1...11.1..11.1
./bin $((1<<30))  4.40s user 0.02s system 99% cpu 4.420 total
 ==> 4294967296/2^30/4.40 == 0.9761 GB / sec

 With Type ushort (16 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 2147483648
 sum= 1.1...11.1..11.1
./bin $((1<<30))  4.15s user 0.02s system 99% cpu 4.182 total
 ==> 2147483648/2^30/4.15 == 0.5174 GB / sec


 With Type uchar (8 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 1073741824
 sum= .1..11.1
./bin $((1<<30))  4.65s user 0.03s system 99% cpu 4.672 total
 ==> 1073741824/2^30/4.65 == 0.2309 GB / sec
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 With Type ulong (64 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 8589934592
 sum= 1111111111111111111111111111111111..1..1....1...1.1...11.1..11.1
./bin $((1<<30))  2.85s user 0.00s system 99% cpu 2.856 total
 ==> 8589934592/2^30/2.85 == 2.8070 GB / sec

 With Type uint (16 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 4294967296
 sum= 11..1..1....1...1.1...11.1..11.1
./bin $((1<<30))  2.85s user 0.00s system 99% cpu 2.857 total
 ==> 4294967296/2^30/2.85 == 1.4035 GB / sec

 With Type ushort (16 bit):
%  time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 2147483648
Bits per word =16
 sum= 1.1...11.1..11.1
./bin $((1<<30))  3.21s user 0.00s system 99% cpu 3.213 total
==> 2147483648/2^30/3.21 == 0.6230  GB / sec

 With Type uchar (8 bit):
% time ./bin $((1<<30))
arg 1: 1073741824 == n  [Will feed values 0,1,2...,n-1 into CRC]  default=32768
 nbytes= 1073741824
 sum= .1..11.1
./bin $((1<<30))  2.85s user 0.00s system 99% cpu 2.856 total
==> 1073741824/2^30/2.85 == 0.3508 GB / sec

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/pcrc64-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/pcrc64-demo.cc DEMOFLAGS=-DTIMING"
/// End:

