
#include "graph/lyndon-gray.h"
#include "bits/crc64.h"  // class crc64

#include "bits/bitlow.h"
#include "bits/print-bin.h"
#include "bits/bitcyclic-period.h"
#include "bits/bitcount.h"

#include "ds/bitarray.h"

#include "nextarg.h"

#include "fxttypes.h"
#include "bits/bitsperlong.h"
#include "fxtio.h"
#include "jjassert.h"


//% Gray cycle through n-bit Lyndon words. Must have n odd, and n < BITS_PER_LONG.
//% By default print (length-7710, base-36) delta sequence for n=17.


//#define TIMING  // uncomment to disable printing

crc64 zcrc;  // CRC

static inline void print_crc()
{
    cout << setfill('0');
    cout << "   crc=" << hex << setw(16) << (zcrc.get_a()) << dec;
    cout << setfill(' ');
}
// -------------------------

ulong
check(lyndon_gray &lg)
// Generate Gray code and print (almost) nothing.
// Only a the progress is shown.
// Update CRC with delta sequence only at "checkpoints".
// CRC is trivial (=0xffffffff) for n<23.
// Return length of path.
{
    ulong k = 0;
    while ( 1 )
    {
        const ulong m1 = (1UL<<16);
        const ulong m2 = (1UL<<20) - 1;
        for (ulong j=m1;  j;  --j)
        {
            ++k;
            if ( 0==lg.next() )  return k;  // at end
        }

        // indicate progress:
        cout << ".";  cout.flush();
        zcrc.word_in( lg.p_ );  // update CRC

        if ( 0==(k&m2) )
        {
            cout << "  "  << setw(9) << k;
            cout << " ( " << 100.0 * (double)k / (double)lg.nlyn_ << " % )";

            print_crc();
            cout << endl;
        }
    }
    return k;  // never reached
}
// -------------------------


ulong
print(lyndon_gray &lg, ulong wh)
// Generate Gray code and print
// delta seq (if wh==1) or full output (wh>=2).
// Update CRC with delta sequence.
{
#ifndef TIMING
    const char dd[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@";
    // enough w/base: "_23456789.123456789.123456789.123456789";
    ulong n = lg.n_;
#else
    (void)wh;
#endif

    ulong k = 0;
    while ( 1 )
    {
        ++k;

#ifndef TIMING
//        if ( bit_count(lg.p_) <= 3 )
        if ( wh>=2 )
        {
            cout << setw(4) << k << ": ";
            print_bin("   ", lg.p_, n);  // Lyndon word
            cout << "  " << setw(2) << lg.r_;  // amount of rotation
            print_bin("  ", lg.pr_, n );    // rotated word
            print_bin("   ", lg.d_, n);     // delta word
            cout << "  ";
//            print_crc();
        }
        ulong d = lowest_one_idx(lg.d_);  // delta value
        // CRC is updated with delta values:
        zcrc.byte_in((uchar)d);

        cout << dd[d];
        if ( 1==wh )  if ( 0==(k%100) )  cout << endl;

        if ( wh>=2 )
        {
//            cout << "  " << bit_count(lg.p_);
            if ( n!=bit_cyclic_period(lg.p_, n) )  cout << " N";
            cout << endl;
        }
#endif

        if ( 0==lg.next() )  return k;
        lg.make_rot();
    }
    return k;  // never reached
}
// -------------------------


bool
doit(ulong n, ulong wh, ulong ncmp)
{
    lyndon_gray  lg(n, ncmp);

    ulong nlyn = lg.nlyn_;
    cout << "n = " << n;
    cout << "   #lyn = " << nlyn;
    cout << endl;


    ulong k;
    if ( 0==wh )  k = check(lg);
    else          k = print(lg, wh);

    cout << endl;
    cout << "last = "; print_bin("", lg.p_, lg.n_);  // unadjusted
    cout << "  ";

    print_crc();
    cout << endl;

    cout << endl;
    cout << "n = " << n;
    cout << "   #lyn = " << nlyn;
    cout << "   #= " << k;
    if ( lg.is_cycle() )  cout << "   Cycle";
    cout << endl;
#ifdef TIMING
    cout << " ct=" << nlyn << endl;
#endif

    return  ( k==nlyn );
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 9;
//    NXARG(n, " a prime < BITS_PER_LONG (37 needs 4GByte of RAM)");
    NXARG(n, "an odd number < BITS_PER_LONG (37 needs 4GByte of RAM)");
    if ( n<2 )  n = 2;

    ulong wh = 2;
    NXARG(wh, "printing: 0==>none, 1==>delta seq., 2==>full output");

    ulong ncmp = 2;  // works for all odd n <= 41
    NXARG(ncmp, "use comparison function (0,1,2,3)");

    ulong testall = 0;
    NXARG(testall, "special: test all odd values <= value");

    if ( 0==testall )
    {
        bool q = doit(n, wh, ncmp);
        if ( !q )
        {
            cout.flush();
            cout << " *** FAILED (incomplete path for n = "<< n << ")" << endl;
            cerr << " *** FAILED (incomplete path for n = "<< n << ")" << endl;
        }
    }
    else
    {
//        ulong p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
//                     37, 41, 43, 47, 53, 59, 61,  ~0UL};
        const ulong p[] =
            {     3,  5,  7,  9,
                  11, 13, 15, 17, 19,
                  21, 23, 25, 27, 29,
                  31, 33, 35, 37, 39,
                  41, 43, 45, 47, 49,
                  51, 53, 55, 57, 59,
                  61, ~0UL };

        ulong k = 0;
        while ( (n=p[k++]) <= testall )
        {
            cout << " ---------------------------------" << endl;
            bool q = doit(n, 0, ncmp);
            if ( !q )
            {
                cout.flush();
                cout << " *** FAILED (incomplete path for n = "<< n << ")" << endl;
//                cerr << " *** FAILED (incomplete path for n = "<< n << ")" << endl;
            }
        }
    }

//    cout << " bitarray uses " << (bitarray::use_asm_q()?"":"NO ") << "assembler " << endl;

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin 27 0 2  # where class bitarray uses assembler instructions
last = .........................11     crc=6a8de2476a9df75f
n = 27   #lyn = 4971066   #= 4971066   Cycle
./bin 27 0 2  11.98s user 0.08s system 99% cpu 12.102 total

 time ./bin 27 0 2  # where class bitarray uses DIVMOD and DIVMOD_TEST
last = .........................11     crc=6a8de2476a9df75f
n = 27   #lyn = 4971066   #= 4971066   Cycle
./bin 27 0 2  12.09s user 0.07s system 99% cpu 12.206 total


 time ./bin 29 0 2  # where class bitarray uses assembler instructions
last = ...........................11     crc=7528016ec3986c1d
n = 29   #lyn = 18512790   #= 18512790   Cycle
./bin 29 0 2  52.28s user 0.30s system 99% cpu 52.670 total

 time ./bin 29 0 2  # where class bitarray uses DIVMOD and DIVMOD_TEST
last = ...........................11     crc=7528016ec3986c1d
n = 29   #lyn = 18512790   #= 18512790   Cycle
./bin 29 0 2  52.61s user 0.28s system 99% cpu 52.950 total
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 29 0 2
last = ...........................11     crc=7528016ec3986c1d
n = 29   #lyn = 18512790   #= 18512790   Cycle
./bin 29 0 2  37.13s user 0.01s system 99% cpu 37.144 total
*/

/*
BENCHARGS=29 0 2
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/graph"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/graph/lyndon-gray-demo.cc"
/// make-target2: "1demo DSRC=demo/graph/lyndon-gray-demo.cc DEMOFLAGS=-DTIMING"
/// End:

