
#define LR_WITH_DUMB_METHODS  // for testing
#include "ds/left-right-array.h"

#include "fxtio.h"
#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% The left-right array.


//#define TIMING  // uncomment to disable printing


void
print_lr(const left_right_array &LR, const ulong *A)
{
    const ulong n = LR.n_;
    cout << " fl[]=";
    for (ulong k=0; k<n; ++k)  cout << " " << LR.fl_[k];
    cout << endl;
//    cout << " tg[]=";
//    for (ulong k=0; k<n; ++k)  cout << " " << LR.tg_[k];
//    cout << endl;
    cout << "  a[]=";
    for (ulong k=0; k<n; ++k)
    {
        cout << " ";
        if ( LR.tg_[k] ) cout << "*";
        else             cout << A[k];
    }
    cout << endl;
}
// -------------------------


void
test_lr(left_right_array &LR)
{
    ulong n = LR.n_;
    ulong idx1, idx2;
    for (ulong j=0; j<LR.num_free(); ++j)
    {
        idx1 = LR.get_free_idx_dumb(j);
        idx2 = LR.get_free_idx(j);
        jjassert( idx1==idx2 );
    }

    for (ulong j=0; j<LR.num_set(); ++j)
    {
        idx2 = LR.get_set_idx(j);
        idx1 = LR.get_set_idx_dumb(j);
        jjassert( idx1==idx2 );
    }

    for (ulong j=0; j<n; ++j)
    {
        ulong t1, t2;
        t2 = LR.num_FLI(j);
        t1 = LR.num_FLI_dumb(j);
        jjassert( t1==t2 );


        t2 = LR.num_FRI(j);
        t1 = LR.num_FRI_dumb(j);
        jjassert( t1==t2 );

        t2 = LR.num_SLI(j);
        t1 = LR.num_SLI_dumb(j);
        jjassert( t1==t2 );

        t2 = LR.num_SRI(j);
        t1 = LR.num_SRI_dumb(j);
        jjassert( t1==t2 );


        t2 = LR.num_FLE(j);
        t1 = LR.num_FLE_dumb(j);
        jjassert( t1==t2 );


        t2 = LR.num_FRE(j);
        t1 = LR.num_FRE_dumb(j);
        jjassert( t1==t2 );

        t2 = LR.num_SLE(j);
        t1 = LR.num_SLE_dumb(j);
        jjassert( t1==t2 );


        t2 = LR.num_SRE(j);
        t1 = LR.num_SRE_dumb(j);
        jjassert( t1==t2 );
    }

    for (ulong j=0; j<LR.num_set(); ++j)
    {
        idx1 = LR.get_set_idx(j);  // j-th set index

        idx2 = LR.get_set_idx_chg(j);  // remove
        jjassert( LR.is_free(idx2) );
        jjassert( idx1==idx2 );

        ulong u = LR.num_FLI(idx2);
        idx1 = LR.get_free_idx_chg( u-1 );
        jjassert( idx1==idx2 );
    }
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 9;
    NXARG(n, "Number of elements.");

    ulong *A = new ulong[n];
    left_right_array LR(n);
    LR.free_all();

#ifndef TIMING
    print_lr(LR, A);
    cout << endl;
#endif

    for (ulong e=0; e<n; ++e)
    {
        ulong s = 0;  // first free
        if ( 0!=(e&1) )  s = LR.num_free()-1;  // last free

#ifndef TIMING
        test_lr(LR);  // test

        cout << " ------- s=" << s << ": -------" << endl;
        ulong idx1 = LR.get_free_idx(s);
        ulong idx2 = LR.get_free_idx_chg(s);
        A[idx2] = e+1;
        print_lr(LR, A);
        jjassert( idx1==idx2 );
        cout << endl;

#else

        A[ LR.get_free_idx_chg(s) ] = e + 1;
//        A[ LR.get_free_idx_chg(0) ] = e + 1;
        // latter slightly faster because of better memory locality

#endif
    }

    delete [] A;
    return 0;
}
// -------------------------


/*
Timing:

 time ./bin $(( 1<<23 ))
arg 1: 8388608 == n  [Number of elements.]  default=9
./bin $(( (1<<24)-(1<<23) ))  3.71s user 0.12s system 100% cpu 3.824 total
 ==> 8388608/3.71 == 2,261,080 per second

 time ./bin 10000000
arg 1: 10000000 == n  [Number of elements.]  default=9
./bin 10000000  1.82s user 0.15s system 99% cpu 1.973 total
 ==> 10000000/1.82 == 5,494,505 per second

 time ./bin $(( 1<<24 ))
arg 1: 16777216 == n  [Number of elements.]  default=9
./bin $(( 1<<24 ))  8.09s user 0.25s system 99% cpu 8.338 total
 ==> 16777216/8.09 == 2,073,821 per second

*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

GCC 4.9.0:

 time ./bin $(( 1<<23 ))
arg 1: 8388608 == n  [Number of elements.]  default=9
./bin $(( 1<<23 ))  1.74s user 0.05s system 99% cpu 1.795 total
 ==> 8388608/1.74 == 4,821,039 per second

 time ./bin 10000000
arg 1: 10000000 == n  [Number of elements.]  default=9
./bin 10000000  0.84s user 0.06s system 99% cpu 0.894 total
 ==> 10000000/0.84 == 11,904,761 per second

 time ./bin $(( 1<<24 ))
arg 1: 16777216 == n  [Number of elements.]  default=9
./bin $(( 1<<24 ))  3.92s user 0.08s system 99% cpu 4.001 total
 ==> 16777216/3.92 == 4,279,902 per second


*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/left-right-array-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/left-right-array-demo.cc DEMOFLAGS=-DTIMING"
/// End:
