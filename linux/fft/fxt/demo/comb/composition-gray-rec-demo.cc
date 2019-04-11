
#include "comb/comp2comb.h"
#include "comb/comb-print.h"

#include "aux0/binomial.h"
#include "aux0/swap.h"

#include "nextarg.h"
#include "fxtio.h"
#include "fxttypes.h"

#include "jjassert.h"


//% Generating all compositions of n into k parts in minimal-change order.


//#define TIMING  // uncomment to disable printing

ulong *p;  // composition data (Kp elements)
ulong Np, Kp;

ulong *c;  // combination data (Kc elements)
ulong Nc, Kc;

ulong rq;  // determine order
ulong ct;  // count objects

ulong *co;  // aux: test Gray-ness
ulong *tt;  // aux


bool complq = false;

void visit()
{
    cout << setw(4) << ct << ":";
//    print_vec("  ", p, Kp, true);

//    for (ulong j=0; j<Kp; ++j)  tt[j] = p[Kp-1-j];  // reverse
    for (ulong j=0; j<Kp; ++j)  tt[j] = p[j];
    print_vec("    ", tt, Kp, true);

    comp2comb(tt, Kp, c);
    if ( complq )  print_set_as_deltaset("    ", c, Kc, Nc, "1.");
    else           print_set_as_deltaset("    ", c, Kc, Nc, ".1");
    print_vec("    ", c, Kc);

    if ( ct > 1 )
    {
        ulong xct = 0;  // count changes
        for (ulong j=0; j<Kc; ++j)  xct += ( co[j] != c[j] );
        --xct;
        if ( xct )  cout << "  << " << xct;
    }

    for (ulong j=0; j<Kc; ++j)  co[j] = c[j];

    cout << endl;
}
// -------------------------


void comp_rec(ulong k, ulong n, bool z)
{
    if ( (k==0) || (n==0) )  // visit
    {
        ++ct;
#ifndef TIMING
        visit();
#endif
        return;
    }

    if ( 1==k )  // rest goes to last bucket
    {
        p[0] = n;
        comp_rec(0, 0, z);
        p[0] = 0;  // clean up
        return;
    }

    ulong j1 = n, j2 = 0, js = -1UL;
    if ( z )  { swap2(j1, j2);  js=-js; }  // go backward

    ulong j = j1;
    while ( 1 )
    {
        bool r = 0;  // default is lexicographic
        switch ( rq )
        {
        case 1:  // (complemented) Gray code
            r = 1; break;
            // Gray code for combinations, not minimal-change for compositions

        case 2:  // modulo moves, (Eades-McKay)
            r = (j&1);
            break;

        case 3:  // enup moves
            r = !(j&1);
            break;

        case 4:  // Gray code
            r = ((Kp-k)^j)&1;
            break;

        case 5:  // yet another Gray code
            r = !(((Kp-k)^j)&1);
            break;
        }

        p[k-1] = j;
        comp_rec(k-1, n-j, r^z);
        if ( j==j2 )  break;
        j += js;
    }

    p[k-1] = 0;  // clean up
}
// -------------------------

int
main(int argc, char **argv)
{
    Np = 3;
    NXARG(Np, "Compositions of n (n>=1)");
    Kp = 5;
    NXARG(Kp, "Into k parts  (k-compositions of n) (k>=1) ");

    rq = 3;
    NXARG(rq, "Order:"
          "\n   0 ==>  lexicographic"
          "\n   1 ==>  ordering from (complemented) Gray code for combinations "
          "\n   2 ==>  Eades-McKay, homogeneous moves"
          "\n   3 ==>  enup moves, two-close, homogeneous moves"
          "\n   4 ==>  Gray code, homogeneous moves"
          "\n   5 ==>  Gray code, homogeneous moves"
          );

    Kc = Np;
    Nc = Np+Kp-1;

//    NXARG(Nc, "opt: n of combinations");
//    NXARG(Kc, "opt: k of combinations");
//
//    Kp = Nc-Kc+1;
//    Np = Kc;
//    cout << "  Np=" << Np << "  Kp=" << Kp << endl;
//    cout << "  Nc=" << Nc << "  Kc=" << Kc << endl;

//    complq = false;
//    NXARG(complq, "whether to complement delta sets");

    ulong b = binomial(Nc, Kc);
    cout << " ( " << Nc << " choose " << Kc << " ) = " << b << endl;

    jjassert( Nc>=Kc );

    p = new ulong[Kp];
    for (ulong k=0; k<Kp; ++k)  p[k] = 0;  // init compositions
    tt = new ulong[Kp];
    c = new ulong[Kc];
    co = new ulong[Kc];

    ct = 0;
    comp_rec(Kp, Np, 1);

    cout << " ct = " << ct << endl;
    jjassert( ct == b );

    delete [] p;
    delete [] tt;
    delete [] c;
    delete [] co;

    return 0;
}
// -------------------------

/*
Timing:
time ./bin 30 10
arg 1: 30 == Np  [Compositions of n (n>=1)]  default=3
arg 2: 10 == Kp  [Into k parts  (k-compositions of n) (k>=1) ]  default=5
 ct = 211915132
./bin 30 10  4.35s user 0.02s system 99% cpu 4.375 total
 ==> 211915132/4.85 == 43,693,841 per second
*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-gray-rec-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-gray-rec-demo.cc DEMOFLAGS=-DTIMING"
/// End:
