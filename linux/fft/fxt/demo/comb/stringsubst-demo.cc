
#include "comb/stringsubst.h"

#include "jjassert.h"
#include "array-len.h"

//% String substitution engine (Lindenmayer system, or L-system).


//#define TIMING  // uncomment to disable printing

// define to generate a stringsubst binary
//#define MAKE_UTIL
//
#ifdef MAKE_UTIL
#define FXT_SILENT_NXARG
#endif
#include "nextarg.h"  // NXARG()

#include <unistd.h>  // exit(), close()


static void
usage_err(const char *argv0)
{
    cerr << "Usage:" << endl;
    cerr << "  " << argv0 << " depth  axiom  symbol0 rule0  symbol1 rule1 ..." << endl;
    cerr << "For each symbol a rule must be supplied." << endl;
    cerr << "At least one symbol/rule pair is needed." << endl;
    cerr << "Example:  (terdragon)" << endl;
    cerr << "  " << argv0 << "  4   F   F F+F-F   + +   - -" << endl;
    cerr << "Example:  (Heighway dragon)" << endl;
    cerr << "  " << argv0 << "  4   L   L L+R   R L-R   + +   - -" << endl;
    cerr << "Example:  (rabbit sequence)" << endl;
    cerr << "  " << argv0 << "  9   0   0 1      1 10" << endl;
    cerr << "Example:  (Thue sequence)" << endl;
    cerr << "  " << argv0 << "  4  0   0 111   1 110" << endl;

    close(1);  // so SIG_PIPE is generated when used with pipes
    exit(1);
}
// -------------------------


int
main(int argc, char *argv[])
{
    ulong maxn = 3;
    NXARG(maxn, "Number of generations");

#ifndef MAKE_UTIL
    string_subst S(maxn);
#else
    string_subst S(maxn, 16384);
#endif

#ifndef MAKE_UTIL
    if ( argc <= 2 )  // default L-system
    {
        const char * R[] = { "F", "F+F-F",  "+", "+",  "-", "-"  };
        const char * A = "F";
        S.set_axiom( A );
        S.set_rules( R, ARRAY_LEN(R) );
    }
    else
#endif  // no default for stringsubst utility:
    {
        if ( argc < 5 )  usage_err(argv[0]);
        if ( ((argc-3) & 1) != 0 )  usage_err(argv[0]);

        jjassert( S.set_axiom(argv[2]) );
        jjassert( S.set_rules((const char **)argv+3, argc-3) );
    }

    jjassert( S.OK() );
    S.first();

    S.print_rules();

    ulong ct = 0;
#ifdef TIMING
    do  { ++ct; }  while ( S.next() );

#else
    char c;
    while ( (c = S.current()) != '\0' )
    {
        cout << c;
        ++ct;
        S.next();
    }
    cout << endl;
#endif

#ifndef MAKE_UTIL
    // suppress for utility to make 'tail -1' give final result
    cout << " ct=" << ct << endl;
#endif

    return  0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:


 time ./bin 40  a  a b  b ba
arg 1: 40 == maxn  [Number of generations]  default=3
Start: a
Rules:
  a --> b
  b --> ba
 ct=165580141
./bin 40 a a b b ba  3.24s user 0.00s system 99% cpu 3.239 total
 ==> 165580141/3.24 == 51,104,981 per second

 time ./bin 27 L L L+R R L-R + + - -
arg 1: 27 == maxn  [Number of generations]  default=3
Start: L
Rules:
  + --> +
  - --> -
  L --> L+R
  R --> L-R
 ct=268435455
./bin 27 L L L+R R L-R + + - -  3.72s user 0.00s system 99% cpu 3.726 total
 ==> 268435455/3.72 == 72,160,068 per second


 time ./bin  17  F  F F+F-F  + +  - -
arg 1: 17 == maxn  [Number of generations]  default=3
Start: F
Rules:
  + --> +
  - --> -
  F --> F+F-F
 ct=258280325
./bin 17 F F F+F-F + + - -  2.13s user 0.00s system 99% cpu 2.131 total
 ==> 258280325/2.13 == 121,258,368 per second

 time ./bin 9  a  a b  b bbbbbbbbbbbba
arg 1: 9 == maxn  [Number of generations]  default=3
Start: a
Rules:
  a --> b
  b --> bbbbbbbbbbbba
 ct=488538193
./bin 9 a a b b bbbbbbbbbbbba  1.84s user 0.00s system 99% cpu 1.840 total
 ==> 488538193/1.84 == 265,509,887 per second

 time ./bin 9  a  a baaaaaa  b bbbbbbbbbbbba
arg 1: 9 == maxn  [Number of generations]  default=3
Start: a
Rules:
  a --> baaaaaa
  b --> bbbbbbbbbbbba
 ct=1076501671
./bin 9 a a baaaaaa b bbbbbbbbbbbba  4.04s user 0.00s system 99% cpu 4.040 total
 ==> 1076501671/4.04 == 266,460,809 per second

*/

/*
BENCHARGS=40  a  a b  b ba
BENCHARGS=17  F  F F+F-F  + +  - -
BENCHARGS=17  F  F F+F-F  + +  - -
BENCHARGS=9   a  a baaaaaa  b bbbbbbbbbbbba
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/stringsubst-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/stringsubst-demo.cc DEMOFLAGS=-DTIMING"
/// End:
