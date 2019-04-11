
#include "bits/radix-m4.h"

#include "bits/graycode.h"

#include "fxttypes.h"  // ulong
#include "bits/bitsperlong.h"

#include "bits/print-bin.h"
#include "fxtio.h"
#include "jjassert.h"
#include "nextarg.h"

//% Representation in radix(-4).


long eval_radm4(ulong x)
{
    long v = 0;
    long rxpw = 1;
    while ( x )
    {
        long d = (long)(x & 3);  // two bits are one digit
        v += d * rxpw;
        rxpw *= -4;
        x >>= 2;
    }

    return v;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Number of bits");
    ulong n = 1UL<<ldn;
    ulong pn = ldn + 4;
    pn -= pn&1;

    for (long s=(long)-n; s<(long)n; ++s)
    {
        ulong k = (ulong)s;
        ulong m = bin_to_radm4(k);
        ulong g = gray_code(m);
        cout << setw(4) << s;
        print_bin(":  ", k, pn);

        print_bin("    ", m, pn);
        cout << " = [";
        for (ulong j=pn-2; (long)j>=0; j-=2)  cout << " " << ((m>>j)&3);
        cout << " ] ";

        print_bin("    ", g, pn);

//        cout << "  e=" << eval_radm4(m);
        cout << endl;

        jjassert( radm4_to_bin(m) == k );
        jjassert( next_radm4(m) == bin_to_radm4(k+1) );
        jjassert( prev_radm4(m) == bin_to_radm4(k-1) );
    }

    cout << endl;

//    for (ulong a=-n; (long)a<(long)n; ++a)
//    {
////        cout << " a=" << a << endl;
//        for (ulong b=-n; (long)b<(long)n; ++b)
//        {
////            cout << " b=" << b << endl;
//            ulong t = radm4_add(a, b);
////            print_bin("    ", t , pn);
//            jjassert( radm4_to_bin(t) == radm4_to_bin(a) + radm4_to_bin(b) );
//        }
//    }


    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/bits"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/bits/radix-m4-demo.cc"
/// make-target2: "1demo DSRC=demo/bits/radix-m4-demo.cc DEMOFLAGS=-DTIMING"
/// End:
