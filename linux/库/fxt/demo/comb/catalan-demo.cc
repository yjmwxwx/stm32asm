
#include "comb/catalan.h"
// demo-include "comb/catalan.cc"
#include "comb/is-catalan-rgs.h"

#include "bits/print-bin.h"

#include "fxtio.h"
#include "fxttypes.h"
#include "jjassert.h"

#include "nextarg.h"


//% Catalan restricted growth strings (RGS) and parentheses strings in minimal-change order.

// Cf. comb/catalan-rgs-demo.cc for fast iterative generation of lex order.
// Cf. comb/catalan-rgs-gray-demo.cc for fast iterative generation of the Gray code.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Number of paren pairs");
    bool xdr = true;
    NXARG(xdr, "Change direction in recursion ==> minimal-change order");
    int dr0 = -1;
    NXARG(dr0, "Starting direction in recursion (+-1)");
    dr0 = ( (dr0>0) ? +1 : -1 );

    catalan C(n, xdr, dr0);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( C.next() );

#else  // TIMING

    ulong w = 0;
    ulong n2 = 2*n;
    do
    {
        ++ct;
        cout << setw(3) << ct << ":  ";
        C.print_internal();

        // print paren string:
        const char *str = C.paren_string();
        cout << "    " << str;

        // print delta set:
        cout << "    ";
        for (ulong k=0; k<n2; ++k)  cout << ( str[k]=='(' ? '1' : '.' );

        ulong w2 = 0;  // bit-string representation
        for (ulong k=0, m=(1UL<<(n2-1));  k<n2;  ++k, m>>=1)
            if ( str[k]=='(' )  w2 |= m;
        if ( ct-1 )
        {
            print_bin_diff("   ", w, w2, 2*n, ")(AX");  // print changes
            if ( xdr )  // show distance of changes if non-adjacent
            {
                ulong wx = w^w2;
                for (ulong s=2; s<n2; ++s)  if ( wx&(wx>>s) )  { cout << "  " << s; break; }

                // make sure we have just two changes:
                ulong x = wx;
                x &= (x-1);  // clear lowest bit
                jjassert( x == (x&-x) );  // x has exactly one bit set

                // make sure changes cross only ones:
                x = wx;
                x &= (x-1);  // clear lowest bit
                x >>= 1;
                while ( 0==(x&wx) )  { jjassert(0!=(x&w2)); x>>=1; }
            }
        }
        w = w2;

        cout << endl;

    }
    while ( C.next() );


#endif  // TIMING


    cout << " ct=" << ct;  // Catalan number n
    cout << endl;

    return 0;
}
// -------------------------


/*
Timing:

 time ./bin 18
arg 1: 18 == n  [Number of paren pairs]  default=5
arg 2: 1 == xdr  [Change direction in recursion ==> minimal-change order]  default=1
arg 3: -1 == dr0  [Starting direction in recursion (+-1)]  default=-1
 ct=477638700
./bin 18  6.89s user 0.01s system 99% cpu 6.901 total
 ==> 477638700/6.89 == 69,323,468 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 18
arg 1: 18 == n  [Number of paren pairs]  default=5
arg 2: 1 == xdr  [Change direction in recursion ==> minimal-change order]  default=1
arg 3: -1 == dr0  [Starting direction in recursion (+-1)]  default=-1
 ct=477638700
./bin 18  4.72s user 0.00s system 99% cpu 4.724 total
 ==> 477638700/4.72 == 101,194,639 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/catalan-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/catalan-demo.cc DEMOFLAGS=-DTIMING"
/// End:

