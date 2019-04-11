
#include "comb/big-fact2perm.h"
// demo-include "comb/big-fact2perm.cc"
#include "ds/left-right-array.h"

#include "comb/mixedradix-lex.h"
#include "comb/fact2perm.h"

#include "comb/comb-print.h"
#include "comb/mixedradix.h"

#include "aux0/swap.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"  // NXARG()
#include "fxtio.h"


//% Generate all permutations from mixed radix (factorial) numbers,
//% using left-right array, so conversion is fast also for large length.

//#define TIMING  // uncomment to disable printing


//void invperm2ffact(const ulong *x, ulong n, ulong *fc)
//{
//    for (ulong k=1; k<n; ++k)
//    {
//        ulong xk = x[k];
//        ulong i = 0;
//        for (ulong j=0; j<k; ++j)  if ( x[j]>xk )  ++i;
//        fc[k-1] = i;
//    }
//}
//// -------------------------


int
main(int argc, char **argv)
{
#ifndef TIMING

    ulong n = 4;
    NXARG(n, "Number of elements to permute");
    bool rq = 0;
    NXARG(rq, "Whether to use rising factorial base.");
    const bool dfz = true;  // whether to print dots for zeros
    const ulong n1 = n - 1;

    left_right_array LR(n);

    mixedradix_lex M(n1, rq);
    M.print_nines(" Nines: ");  cout << endl;

    const ulong *a = M.data();  // factorial number
    ulong *p = new ulong[n];  // permutation
    ulong *tp = new ulong[n];  // aux for testing
    ulong *t = new ulong[n];  // aux for testing

    ulong ct = 0;
    do
    {
        cout << " " << setw(3) << ct << ":";
        print_mixedradix("    ", a, n1, dfz);


        if ( rq )  rfact2perm(a, n, p, LR);
        else       ffact2perm(a, n, p, LR);
        print_perm("    ", p, n, dfz);


        if ( rq )  rfact2perm(a, n, tp);
        else       ffact2perm(a, n, tp);
//        print_mixedradix("    :: ", tp, n, dfz);
        for (ulong j=0; j<n1; ++j)  { jjassert( p[j]==tp[j] ); }


        if ( rq )  perm2rfact(p, n, t);
        else       perm2ffact(p, n, t);
//        print_mixedradix("    :: ", t, n1, dfz);
        for (ulong j=0; j<n1; ++j)  { jjassert( t[j]==a[j] ); }


        if ( rq )  perm2rfact(p, n, t, LR);
        else       perm2ffact(p, n, t, LR);
//        print_mixedradix("    :: ", t, n1, dfz);
        for (ulong j=0; j<n1; ++j)  { jjassert( t[j]==a[j] ); }


        if ( rq )  rfact2invperm(a, n, tp);
        else       ffact2invperm(a, n, tp);
        print_perm("    ", tp, n, dfz);
//        print_mixedradix("    :: ", tp, n, dfz);
        for (ulong j=0; j<n; ++j)  { jjassert( j== p[tp[j]] ); }


        if ( rq )  rfact2invperm(a, n, tp, LR);
        else       ffact2invperm(a, n, tp, LR);
//        print_mixedradix("    :: ", tp, n, dfz);
        for (ulong j=0; j<n; ++j)  { jjassert( j== p[tp[j]] ); }

//        if ( rq ) ;
//        else
//        {
//            invperm2ffact(tp, n, t);
//            print_mixedradix("    :: ", t, n1, dfz);
////            for (ulong j=0; j<n1; ++j)  { jjassert( t[j]==a[j] ); }
//        }

        ++ct;
        cout << endl;
    }
    while ( M.next() );

    delete [] p;
    delete [] tp;
    delete [] t;

#else  // TIMING:

    ulong n = 10*1000*1000;  // note: ULIMIT with demo-script (kills this branch)
    NXARG(n, "Number of elements to permute");

    ulong memar = 2*n*sizeof(ulong);
    ulong memLR = n*(sizeof(ulong)+sizeof(bool));
    cout << "Mem==" << ((memar+memLR)/1024/1024) << "MB" << endl;

    bool rq = 0;
    NXARG(rq, "Whether to use rising factorial base.");
    const ulong n1 = n - 1;

    ulong *a = new ulong[n1];
    ulong *p = new ulong[n];

    for (ulong j=0; j<n1; ++j)  a[j] = j/2;
    if ( !rq )  for (ulong k=0, r=n-2;  k<r;  ++k, --r)  swap2(a[k], a[r]);
//    print_mixedradix("    :: ", a, n1, true);

    left_right_array LR(n);

    if ( rq )  rfact2perm(a, n, p, LR);
    else       ffact2perm(a, n, p, LR);
//    print_perm("    ", p, n, true);  cout << endl;

    delete [] a;
    delete [] p;

#endif

    return 0;
}
// -------------------------

/*
Timing:

 time ./bin . 0
arg 1: 10000000 == n  [Number of elements to permute]  default=10000000
arg 2: 0 == rq  [Whether to use rising factorial base.]  default=0
./bin . 0  1.96s user 0.17s system 99% cpu 2.130 total
 ==> 10000000/1.96 == 5,102,040 second

 time ./bin . 1
arg 1: 10000000 == n  [Number of elements to permute]  default=10000000
arg 2: 1 == rq  [Whether to use rising factorial base.]  default=0
./bin . 1  1.90s user 0.14s system 100% cpu 2.044 total
 ==> 10000000/1.90 == 5,263,157 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/big-fact2perm-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/big-fact2perm-demo.cc DEMOFLAGS=-DTIMING"
/// End:
