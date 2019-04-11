
#include "comb/mset-perm-lex-rec.h"
// demo-include "comb/mset-perm-lex-rec.cc"

#include "comb/comb-print.h"

#include "fxttypes.h"
#include "fxtio.h"
//#include "jjassert.h"

#include <cstdlib>  // strtoul()



//% All multiset permutations in lexicographic order.
//% Recursive generation using a linked list.
//% Same as: all strings with fixed content.


//#define TIMING  // uncomment to disable printing

const bool dfz = true;  // whether to print dots for zeros

#ifndef TIMING
void visit(const mset_perm_lex_rec &P)
{
    cout << setw(4) << P.ct_ << ":";
    print_perm("  ", P.ms_, P.n_, dfz);
//    print_perm("  ", P.nn_, P.k_+1, dfz);
    cout << endl;
//    for (ulong j=0; j<k; ++j)  jjassert( P.r_[j]==0 );
}
// -------------------------
#else
void visit(const mset_perm_lex_rec & /*unused*/) {;}
#endif



int
main(int argc, char **argv)
{
    ulong k;   // number of sorts of elements
    ulong *r;  // element i is repeated r[i] times

    cout << "args: multiplicities of elements" << endl;
    if ( argc<=1 )
    {
        ulong t[]={2, 2, 1, 0};  // proper multisets  ct=30
//        ulong t[]={1, 1, 1, 1, 0};  // permutations  ct = 24
//        ulong t[]={6, 2, 0};  // combinations  ct=28
        k=0;  while ( t[k] )  { ++k; }
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)  r[j] = t[j];
    }
    else
    {
        k = (ulong)argc - 1;  // jjcast
        r = new ulong[k];
        for (ulong j=0; j<k; ++j)
        {
            ulong t = strtoul(argv[j+1], 0, 10);
            r[j] = t;
        }
    }

    mset_perm_lex_rec P(r, k);
    delete [] r;

    cout << "multiplicities: ( ";
    for (ulong i=0; i<k; ++i)  cout << P.r_[i] << (i<k-1?", ":" ");
    cout << ")";
    cout << "  k=" << P.k_ << "  n=" << P.n_;
    cout << endl;


    P.generate( visit );


    cout << " ct=" << P.ct_ << endl;
#ifndef TIMING
    cout << " rct=" << P.rct_ << endl;
    cout << " rec/object=" << (double)(P.rct_)/(double)(P.ct_) << endl;
#endif

    return 0;
}
// -------------------------


/*
Timing:

time ./bin 2 2 2 3 3 3
args: multiplicities of elements
multiplicities: ( 2, 2, 2, 3, 3, 3 )  k=6  n=15
ct=756756000
rct=2183129955
rec/object=2.88485
./bin 2 2 2 3 3 3  38.02s user 0.18s system 99% cpu 38.227 total
 ==> 756756000/38.02 == 19,904,155 per second

 time ./bin 3 3 3 2 2 2 ## reordered
./bin 3 3 3 2 2 2  32.39s user 0.18s system 99% cpu 32.564 total
 ==> 756756000/32.39 == 23,363,877 per second

time  ./bin 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
args: multiplicities of elements
multiplicities: ( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )  k=12  n=12
ct=479001600
rct=1302061344
rec/object=2.71828
./bin 1 1 1 1 1 1 1 1 1 1 1 1  19.06s user 0.12s system 99% cpu 19.215 total
 ==> 479001600/19.06 == 25,131,248 per second

time  ./bin 15 15  ## combination (30 choose 15)
args: multiplicities of elements
multiplicities: ( 15, 15 )  k=2  n=30
ct=155117520
rct=601080388
rec/object=3.875
 ==> 155117520/3.875 == 40,030,327 per second
*/

/*
BENCHARGS= 2 2 2 3 3 3
BENCHARGS= 3 3 3 2 2 2 ## reordered
BENCHARGS= 1 1 1 1 1 1 1 1 1 1 1 1  ## permutations of 12
BENCHARGS= 15 15  ## combinations (30 choose 15)

*/

/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mset-perm-lex-rec2-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mset-perm-lex-rec2-demo.cc DEMOFLAGS=-DTIMING"
/// End:
