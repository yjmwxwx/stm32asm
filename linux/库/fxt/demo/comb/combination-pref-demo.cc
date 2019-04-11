
#include "comb/combination-pref.h"

#include "comb/comb-print.h"

#include "fxtio.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Combinations via prefix shifts ("cool-lex" order)

//#define TIMING  // uncomment to disable printing


//#define WITH_COMP  // show also compositions

#ifdef WITH_COMP
#include "comb/comp2comb.h"
ulong *S, *P;
ulong np, kp;
#endif

ulong ct = 0;
void
visit(const combination_pref &C)
{
    const ulong n = C.size();
    const ulong *x = C.data();
    cout << setw(4) << ct << ":";
    print_deltaset("    ", x, n);
    print_deltaset_as_set("    ", x, n);
#ifdef WITH_COMP
    const ulong k = C.t_;
    for (ulong i=0, j=0;  j<k;  ++i)  if ( x[i] )  { S[j]=i; ++j; }  // delta set to set
//    print_set("    ", S, k);
    comb2comp(S, n, k, P);
    print_vec("    ", P, kp, true);
#endif
    cout << endl;
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "Combinations (n choose k)");
    ulong k = 3;
    NXARG(k, " k>=1");

#ifdef WITH_COMP
    S = new ulong[k];
    comb2comp_nk(n, k, np, kp);
    P = new ulong[kp];
#endif

    combination_pref C(n, k);
    do
    {
        ++ct;
#ifndef TIMING
        visit( C );
#endif
    }
    while ( C.next() );

    cout << " ct = " << ct << endl;

#ifdef WITH_COMP
    delete [] P;
#endif

    return 0;
}
// -------------------------

/*
Timing:

% time ./bin 32 20
arg 1: 32 == n  [Combinations (n choose k)]  default=7
arg 2: 20 == k  [ k>=1]  default=3
 ct = 225792840
./bin 32 20  1.08s user 0.00s system 99% cpu 1.076 total
 ==> binomial(32,20)/1.08 == 209,067,444 per second

% time ./bin 32 12
arg 1: 32 == n  [Combinations (n choose k)]  default=7
arg 2: 12 == k  [ k>=1]  default=3
 ct = 225792840
./bin 32 12  1.12s user 0.00s system 99% cpu 1.128 total
 ==> binomial(32,12)/1.12 == 201,600,750 per second

*/


//+++++++++++++++++++++++++++++++++++
#if 0  // code from the paper

ulong *b;
ulong n;

void iterate(int s, int t)
// Must have: s!=0, t!=0
{
    visit(b, n);  // missing in paper
    b[t] = 1;  b[0] = 0;
    visit(b, n);
    ulong x = 1, y = 0;
    while ( x<n-1 )
    {
        b[x++] = 0;  b[y++] = 1;       // X(s,t)
        if ( b[x]==0 )
        {
            b[x] = 1;  b[0] = 0;       // Y(s,t)
            if ( y>1 )  x = 1;         // Z(s,t)
            y = 0;
        }
        visit(b, n);
    }
}
// -------------------------

    n = s + t;
    b = new ulong[n];
    for (ulong j=0; j<n; ++j)  b[j] = 0;
    for (ulong j=0; j<t; ++j)  b[j] = 1;

    iterate(s, t);

#endif  // 0
//+++++++++++++++++++++++++++++++++++

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/combination-pref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/combination-pref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

