
#include "comb/paren-pref.h"

#include "comb/comb-print.h"
#include "comb/paren-string-to-rgs.h"  // paren_bits_to_rgs()


#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"



//% Generate all well-formed pairs of parentheses by prefix shifts

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong t = 5;
    NXARG(t, "Number of ones (t>0)");
    jjassert( t>0 );
    ulong s = t;
    NXARG(s, "Number of zeros (s<=t)");
    jjassert( t>=s );

    paren_pref C(t, s);

    ulong ct = 0;

#ifdef TIMING

#ifdef PAREN_PREF_FIXARRAYS
    cout << "PAREN_PREF_FIXARRAYS is defined." << endl;
#endif
#ifdef PAREN_PREF_BASE1
    cout << "PAREN_PREF_BASE1 is defined." << endl;
#endif

    do  { ++ct; }  while ( C.next() );

#else // TIMING

    const ulong n = s + t;
    const ulong *x = C.data();
    do
    {
        ++ct;
        cout << setw(4) << ct << ":";

        if ( s==t )  // print as paren string
        {
            cout << "    ";
            for (ulong j=0; j<n; ++j)  cout << ( x[j] ? '(' : ')' );
        }
        print_deltaset("    ", x, n);

        cout << endl;

        jjassert( C.OK() );
    }
    while ( C.next() );

#endif // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------




/*
Code as given in the paper
   Frank Ruskey, Aaron Williams:
   "Generating Balanced Parentheses and Binary Trees by Prefix Shifts"
   CATS 2008, Computing: The Australasian Theory Symposium,
   Wollongong, Australia, (2008)

CoolCat(t, s)
Require: t >= s > 0
 1: n = t + s
 2: b = array(1^t 0^s)  // note one-based array
 3: x = t
 4: y = t
 5: visit(b)
 6: while x < n - [[t == s]] do
 7:   b[x] = 0
 8:   b[y] = 1
 9:   x=x+1
10:    y =y+1
11:    if b[x] == 0
12:       if x == 2y - 2 { Case (c) }
13:          x=x+1
14:       else
15:          b[x] = 1 { Case (b) }
16:          b[2] = 0
17:          x=3
18:          y=2
19:       end
20:    end { else Case (a) }
21:    visit(b)
22: end
*/


/*
Timing:

// one-based array:

 time ./bin 18
arg 1: 18 == t  [Number of ones (t>0)]  default=5
arg 2: 18 == s  [Number of zeros (s<=t)]  default=18
 ct = 477638700
./bin 18  1.78s user 0.00s system 99% cpu 1.776 total
 ==> 477638700/1.78 == 268,336,348 per second

 time ./bin 18
arg 1: 18 == t  [Number of ones (t>0)]  default=5
arg 2: 18 == s  [Number of zeros (s<=t)]  default=18
PAREN_PREF_FIXARRAYS is defined.
 ct = 477638700
./bin 18  1.70s user 0.00s system 100% cpu 1.700 total
 ==> 477638700/1.70 == 280,963,941 per second

// (zero-based array gives a slight slowdown)

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

// one-based array:
 time ./bin 18
arg 1: 18 == t  [Number of ones (t>0)]  default=5
arg 2: 18 == s  [Number of zeros (s<=t)]  default=18
 ct=477638700
./bin 18  1.04s user 0.00s system 99% cpu 1.039 total
 ==> 477638700/1.04 == 459,267,980 per second

 time ./bin 18
arg 1: 18 == t  [Number of ones (t>0)]  default=5
arg 2: 18 == s  [Number of zeros (s<=t)]  default=18
PAREN_PREF_FIXARRAYS is defined.
 ct=477638700
./bin 18  1.01s user 0.00s system 99% cpu 1.007 total
 ==> 477638700/1.01 == 472,909,603 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/paren-pref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/paren-pref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

