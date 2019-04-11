
#include "comb/composition-nz-weakly-unimodal.h"

#include "comb/is-unimodal.h"
#include "comb/is-symmetric.h"
#include "comb/is-smooth.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"


//% Weakly unimodal compositions, lexicographic order.
//% Cf. OEIS sequence A001523.

// See OEIS sequence A229706 for stats by greatest part.

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Compositions of n");

    bool aa = 0;
    NXARG(aa, "Whether to render as ASCII art");

    composition_nz_weakly_unimodal C(n);

    ulong ct = 0;

#ifdef TIMING
    do  { ++ct; }  while ( C.next() );
#else

    ulong m = C.num_parts();
    do
    {
#if 0  // A238871: smooth
        if ( ! is_smooth( C.data(), m) )  continue;
#endif

#if 0  // A059618: strongly unimodal compositions/partitions of n
        // G.f.:  1 + sum(n>=1, x^n * prod(k=1,n-1, 1+x^k )^2 )
        if ( ! is_strongly_unimodal(C.data(), m) )  continue;
        // cf. A229707 (stats by greatest part)
#endif
#if 0  // prescribed max part:
        const ulong *x = C.data();
        bool q = true;
        const ulong mx = 2;  // A033638
//        const ulong mx = 3;  // A000000
//        const ulong mx = 4;  // A000000
//        const ulong mx = 5;  // A000000
        for (ulong j=0; j<m; ++j)
            if ( x[j] > mx )  { q=0; break; }
        if ( !q )  continue;
#endif
#if 0  // max part appears...
        const ulong *x = C.data();
        ulong mx = 0;  // value of maximum
        ulong mct = 0;  // number of times maximum appears
        for (ulong j=0; j<m; ++j)
        {
            if ( x[j] == mx )  mct += 1;
            if ( x[j] > mx )  { mct=1; mx=x[j]; }
        }

//        if ( mct != 1 )  continue;  // once: A006330;  symm: A000009
//        if ( mct != 2 )  continue;  // twice: A114921;  symm: A035363
//        if ( mct != 3 )  continue;  // 3 times: A226541: symm: A087897
//        if ( mct <= mx )  continue;  // more than mx times: A118199, symm: A000000
//        if ( mct < mx )  continue;  // at least mx times: A001522;  symm: A189357
//        if ( mct != mx )  continue;  // exactly mx times: A188674;  symm: A027349
//        if ( 0==(mct&1) )  continue;  // odd no. of times: A000000;  symm: A000009
        if ( 0!=(mct&1) )  continue;  // even no. of times: A000000;  symm: A035363

//        if ( ! is_symmetric(x, m) )  continue;
#endif
#if 0  // all parts 1...max appear at least once: A227038
        { ulong w = 0;  // should better be a bit-array
            const ulong *x = C.data();
            for (ulong j=0; j<m; ++j)  w |= (1UL << x[j]);
            w >>= 1;
//            cout << w << endl;
            if ( 0 != (w & (w+1)) )  continue;
        }

#endif

#if 1
        cout << setw(4) << ct << ":";
        cout << "  [" << setw(2) << m << "]";
        C.print("  ");
//        cout << "  mv=" << C.max_part();
//        cout << "  pg1=" << C.pg1_;
        cout << endl;

        if ( aa )  // ASCII art
        {
            C.print_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( C.OK() );
#endif

        ++ct;

    }
    while ( (m=C.next()) );
#endif  // TIMING

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 65
arg 1: 65 == n  [Compositions of n]  default=7
  ct=1301654610
./bin 65  5.93s user 0.00s system 99% cpu 5.937 total
 ==> 1301654610/5.93 == 219,503,306 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-weakly-unimodal-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-weakly-unimodal-demo.cc DEMOFLAGS=-DTIMING"
/// End:

