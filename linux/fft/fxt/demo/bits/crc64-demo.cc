
#include "bits/crc64.h"
// demo-include "bits/crc64.cc"
#include "bpol/poly-tab.h"

#include "fxttypes.h"
#include "bits/print-bin.h"
#include "jjassert.h"
#include "fxtio.h"
#include "nextarg.h"


//% Cyclic Redundancy Check (CRC) with 64 bits.

//#define TIMING  // uncomment to disable printing


void
Print(const char *str, uint64 a)
{
    cout << "  " << str << "= 0x" << setfill('0') << setw(16) << hex << a;
    cout << dec << setfill(' ');
    print_bin("\n      = ", a, 64);
}
// -------------------------


int
main(int argc, char **argv)
{
    // Note: with TIMING defined: 2**b values are checksummed
#ifdef TIMING
    ulong b = 10;
    NXARG(b, "2**b bytes fed into CRC");
#else
    ulong b = 0xf5;
    NXARG(b, "Byte to feed into CRC");
#endif

    long nc = -1;
    NXARG(nc, " If nc>=0 ==> alternative modulo polynomial, (nc<16).");
    if ( nc >= 16 )  nc = -1;

    uint64 c = 0;  // default
    if ( nc>=0 )  c = crc64::cc[nc];
    crc64 crc( c );


#ifdef TIMING

    crc.reset();
    const ulong N = (1UL<<b);
    for (ulong k=0; k<N; ++k)  crc.byte_in((uchar)k);
    uint64 a2 = crc.get_a();
    cout << setw(4) << " == " << "  ";
    Print("crc", a2);
    cout << endl;
    cout << " ct=" << N << endl;


#else  // TIMING

    uchar cb = (uchar)b;

    cout << endl;
    Print("        c", crc.c_);
    cout << endl;
    cout << endl;

    cout << " ------- bit-wise computation:" << endl;
    uchar t = cb;
    uint64 a1;
    for (ulong k=0; k<=8; ++k)
    {
        a1 = crc.get_a();
        cout << setw(4) << k << "  ";
        Print("crc", a1);
        crc.bit_in(t);
        cout << "   " << (t&1);
        cout << endl;

//        t >>= 1;
        t = (uchar)(t >> 1);  // compiler's pedantry
    }
    cout << endl;


    cout << " ------- byte-add and 8 x shift computation:" << endl;
    crc.reset();
    crc.a_ ^= cb;
    uint64 b1;
    for (ulong k=0; k<=8; ++k)
    {
        b1 = crc.get_a();
        cout << setw(4) << k << "  ";
        Print("crc", b1);
        crc.shift();
        cout << endl;
    }
    cout << endl;
    jjassert( b1==a1 );
    cout << endl;


    cout << " ------- computation with built-in byte_in():" << endl;
    crc.reset();
    crc.byte_in(cb);
    uint64 a2 = crc.get_a();
    cout << setw(4) << " == " << "  ";
    Print("crc", a2);
    cout << endl;

    jjassert( a2==a1 );

    cout << endl;

#endif  // TIMING

    return 0;
}
// -------------------------

/*
Timing:

time ./bin 29
arg 1: 29 == b  [Byte to feed into CRC]  default=245
arg 2: -1 == nc  [ If nc>=0 ==> alternative modulo polynomial, (nc<16).]  default=-1
 ==     crc= 0x47e5a6da4a1856ff
    = .1...111111..1.11.1..11.11.11.1..1..1.1....11....1.1.11.11111111
./bin 29  10.14s user 0.04s system 99% cpu 10.183 total
 ==> 2^29/10.14 == 52,945,849 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 29
arg 1: 29 == b  [2**b bytes fed into CRC]  default=10
arg 2: -1 == nc  [ If nc>=0 ==> alternative modulo polynomial, (nc<16).]  default=-1
 ==     crc= 0x47e5a6da4a1856ff
      = .1...111111..1.11.1..11.11.11.1..1..1.1....11....1.1.11.11111111
 ct=536870912
./bin 29  7.31s user 0.00s system 99% cpu 7.317 total
 ==> 536870912/7.31 == 73,443,353 per second

*/

/*
BENCHARGS=29
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/crc64-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/crc64-demo.cc DEMOFLAGS=-DTIMING"
/// End:

