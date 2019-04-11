
#include "comb/perm-restrpref.h"  // class perm_restrpref

#include "perm/printcycles.h"
#include "comb/comb-print.h"
#include "perm/permq.h"

#include "comb/fact2perm.h"
#include "perm/perminvert.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "perm/permq.h"  // is_involution(), is_connected()
//#include "jjassert.h"

#include "nextarg.h"  // NXARG()

//% Permutations with restricted prefixes

// Cf. comb/mixedradix-restrpref-demo.cc for mixed radix numbers with restricted prefixes.

static ulong N;  // permutations of length N


//#define TIMING  // uncomment to disable printing

ulong *z;  // for zero-based permutations
ulong *fc;
// used here:
#ifdef TIMING
void visit(const ulong *, ulong, ulong)  { ; }
#else // TIMING
void visit(const ulong *a, ulong n, ulong ct)
{
    cout << setw(4) << ct << ":";
    for (ulong i=0; i<n; ++i)  z[i] = a[i+1] - 1;
    print_perm("  ", z, n);
//    print_perm("  ", a+1, n);

//    make_inverse_notag(z, n);
    perm2ffact(z, n, fc);
//    perm2rfact(z, n, fc);
//    perm2rfact_rev(z, n, fc);
    print_vec("    ", fc, n-1, true);

    print_cycles("    ", z, n);

//    ulong z[n];  for (ulong k=0; k<n; ++k)  z[k] = a[k+1]-1;
//    if ( is_cyclic(z, n) )  cout << "  Cyc";
//    if ( is_connected(z, n) )  cout << "  Ind";
//    if ( is_involution(z, n) )  cout << "  Inv";
//    if ( is_updown_permutation(z, n) )  cout << "  UpD";
//    if ( is_derangement(z, n) )  cout << "  Der";

    cout << endl;
}
// -------------------------
#endif  // TIMING


bool cond_0(const ulong *, ulong)
// trivial (empty) condition
{
    return true;
}
// -------------------------

bool cond_invol(const ulong *a, ulong k)
// involution condition
// OEIS sequence A000085
{
    ulong ak = a[k];
    if ( (ak<=k) && (a[ak]!=k) )  return false;
    return true;
//    return  ( a[a[k]]==k );  // cannot use this as permutation may be incomplete
}
// -------------------------

bool cond_updown(const ulong *a, ulong k)
// up-down condition: a1 < a2 > a3 < a4 > ...
// OEIS sequence A000111
{
//    if ( k<3 ) return true;
//    if ( a[k]>a[k-1] )   return ( a[k-1]<a[k-2] );
//    else                 return ( a[k-1]>a[k-2] );
    if ( k<2 ) return true;
    if ( (k%2) )  return ( a[k]<a[k-1] );
    else          return ( a[k]>a[k-1] );
}
// -------------------------

bool cond_indecomp(const ulong *a, ulong k)
// indecomposable condition: {a1, ..., ak} != {1, ..., k} for all k<n
// OEIS sequence A003319
{
    if ( k==N )  return true;
    for (ulong i=1; i<=k; ++i)  if ( a[i]>k )  return true;
    return false;
}
// -------------------------

bool cond_derange(const ulong *a, ulong k)
// derangement condition: f[k]!=k for all k
// OEIS sequence A000166
{
    return ( a[k] != k );
}
// -------------------------

bool cond_xx1(const ulong *a, ulong k)
// condition: f[k-1]!=f[k]-1 for all k
// OEIS sequence A000255
{
    if ( k==1 )  return true;
    return ( a[k-1] != a[k]-1 );  // must look backward
}
// -------------------------


bool cond_dist(const ulong *a, ulong k)
// condition: abs(f[k]-k) >= 2
{
    ulong ak = a[k];

//    if ( ak<=k )  return ( k-ak <= 1 );  else return true;  // A000079 Powers of 2

    const ulong d = ( ak>k ? ak-k : k-ak );

    return ( d>=2 );  // OEIS sequence A001883: 1, 4, 29, 206, 1708, 15702, 159737,

//    return ( d>=1 );  // derangements
//    return ( d<2 );  // A000045: Fibonacci numbers
//    return ( d<=2 );  // A002524: 1, 2, 6, 14, 31, 73, 172, 400, 932, 2177,

// abs distance <= d, for d = 1, 2, 3, ..., 10:
// A000045, A002524, A002526, A072856, A154654,
// A154655, A154656, A154657, A154658, A154659.
}
// -------------------------

bool cond_dist_set(const ulong *a, ulong k)
// playground
{
    if ( a[k]==k )  return false;
    if ( !cond_invol(a, k) )  return false;
    // A001147 fixed-point free involutions: disjoint pairs from 2*n items
    return true;

    if ( k==N )  return true;
    for (ulong i=1; i<=k; ++i)  if ( a[i]>k )  return true;
    return false;
    // A000698


    if ( k==1 )  return true;

    ulong d = a[k] - a[k-1];
    if ( (long)d < 0 )  d = -d;

//    if ( (d==3) || (d==5) )  return true;  //
    if ( (d==4) || (d==5) )  return true;  // A174708
//    if ( (d==3) || (d==4) || (d==5) )  return true;  // A174707
//    if ( (d>=3) && (d<=5) )  return true;  // A174707
//    if ( (d>=2) && (d<=4) )  return true;  // A174704

//    if ( d<=1 )  return true;  // 1, 2, 2, 2, 2, 2, ...
//    if ( d<=2 )  return true;  // A003274
//    if ( d<=3 )  return true;  // A174700
//    if ( d<=4 )  return true;  // A174701
//    if ( d<=5 )  return true;  // A174702

//    if ( d>=2 )  return true;  // A002464
//    if ( d>=3 )  return true;  // A127697
//    if ( d>=4 )  return true;  // A179957
//    if ( d>=5 )  return true;  // A179958

//    if ( (d==3) || (d==4) )  return true;  // A174706
//    if ( (d==4) || (d==5) )  return true;  //
//    if ( (d==1) || (d==2) )  return true;  // A003274
//    if ( d%2==1 )  return true;  // A092186

//    if ( d%3==0 )  return true;  // 1 0 0 0 0 0 0 0 0 0 0
//    if ( d%3==1 )  return true;  // 1 2 2 2 10 12 28 144 292 934 6094
//    if ( d%3==2 )  return true;  // 1 0 0 0 0 2 14 12 48 260 476

    return false;
}
// -------------------------

bool cond_gt_k2(const ulong *a, ulong k)
// condition: a[k-2] < a[k]
// OEIS sequence A001405 (central binomial coefficients)
{
    if ( k<3 ) return true;
    return ( a[k-2] < a[k] );  // A001405

//    if ( k<4 ) return true;
//    return ( a[k-3] < a[k] );  // A022916

//    if ( k<5 ) return true;
//    return ( a[k-4] < a[k] );  // A022917

//    if ( k<6 ) return true;
//    return ( a[k-5] < a[k] );  // A000000
}
// -------------------------


bool cond_cyc_dist(const ulong *a, ulong k)
{
    if ( k == 1 )  return ( 1 == a[k] );  // cyclic permutations only

    // max distance:
//    const ulong md = 2;  // 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, ...
//    const ulong md = 3;  // A000000
    const ulong md = 4;  // A174700 with offset

    ulong d = a[k] - a[k-1];
    if ( (long)d  < 0 )  d = -d;
    if ( d > md )  return false;

//    return true;

    if ( k==N )
    {
        d = a[N] - a[1];
        if ( (long)d  < 0 )  d = -d;
        if ( d > md )  return false;
    }

    return true;
}
// -------------------------

bool cond_gray(const ulong *a, ulong k)
// A003043
// cf. A236602 (sequence may be incorrect)
{
    if ( k==1 )  return  ( a[1]==1 );
    if ( k < N )
    {
        const ulong x = (a[k]-1) ^ (a[k-1]-1);
        return  !(x & (x-1));
    }

    // k==N:
    const ulong e = a[N] - 1;  // end
//    const ulong s = a[2] - 1;  // second  // must have n>=2
//    if ( s > e )  return false;

//    return true;  // Gray code

//    cout << " :: s = " << s << "  e = " << e << endl;

    // Gray cycle:
    const ulong x = e;
    return  !(x & (x-1));
}
// -------------------------

bool cond_asc_desc_geq_2(const ulong *a, ulong k)
// A277556
{
    if ( k<=2 )  return  true;
    bool q0 = ( a[k-0] > a[k-1] );
    bool q1 = ( a[k-1] > a[k-2] );
    if ( k==3 )  return ( q0 == q1 );
    if ( k==N )  return ( q0 == q1 );
    bool q2 = ( a[k-2] > a[k-3] );
    if ( q2 == q0 )  return ( q0 == q1 );
    return true;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Permutations of {1, 2, ..., n}");
    z = new ulong[n];
    N = n;

    fc = new ulong[n];

    ulong c = 4;
    NXARG(c, "Condition function:"
          "\n      (0: empty), (1: involutions),"
          "\n      (2: up-down), (3: indecomposable),"
          "\n      (4: derangement), (5: no [x,x+1])"
          "\n      (6: distance condition)"
//          "\n      (7: playground)"
//          "\n      (8: playground)"
          );

    perm_restrpref *perm;
    switch ( c )
    {
    case 0:
        cout << "All permutations:" << endl;
        perm = new perm_restrpref(n, cond_0, visit);  break;
    case 1:
        cout << "Involutions (self-inverse permutations):" << endl;
        perm = new perm_restrpref(n, cond_invol, visit);  break;
    case 2:
        cout << "Up-down permutations:" << endl;
        perm = new perm_restrpref(n, cond_updown, visit);  break;
    case 3:
        cout << "Connected (indecomposable) permutations:" << endl;
        perm = new perm_restrpref(n, cond_indecomp, visit);  break;
    case 4:
        cout << "Derangements:" << endl;
        perm = new perm_restrpref(n, cond_derange, visit);  break;
    case 5:
        cout << "No [x,x+1]:" << endl;
        perm = new perm_restrpref(n, cond_xx1, visit);  break;
    case 6:
        cout << "Distance <=2 :" << endl;
        perm = new perm_restrpref(n, cond_dist, visit);  break;

    case 7:
        cout << "Playground:" << endl;
        perm = new perm_restrpref(n, cond_dist_set, visit);  break;
    case 8:
        cout << "Playground:" << endl;
        perm = new perm_restrpref(n, cond_gt_k2, visit);  break;

    case 10:
        cout << "Playground:" << endl;
        perm = new perm_restrpref(n, cond_cyc_dist, visit);  break;

    case 11:
        cout << "Canonical Gray cycles:" << endl;
        perm = new perm_restrpref(n, cond_gray, visit);  break;

    case 12:
        cout << "Ascends and descends of length at least 2:" << endl;
        perm = new perm_restrpref(n, cond_asc_desc_geq_2, visit);  break;

    default:
        cout << "Error!" << endl;
        return 1;
    }

    ulong ct = perm->all();
    cout << " ct=" << ct << endl;

    delete perm;
    delete [] z;
    delete [] fc;

    return 0;
}
// -------------------------

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 12 0  ## all permutations (best case)
arg 1: 12 == n  [Permutations of {1,2,...,n}]  default=5
arg 2: 0 == c  [Condition function: ...]
All permutations:
 ct = 479001600
./bin 12 0  11.50s user 0.00s system 99% cpu 11.504 total
 ==> 479001600/11.50 == 41,652,313 per second

 time ./bin 12 4 ## derangements
arg 1: 12 == n  [Permutations of {1, 2, ..., n}]  default=5
arg 2: 4 == c  [Condition function:
      (0: empty), (1: involutions),
      (2: up-down), (3: indecomp),
      (4: derangement), (5: no [x,x+1])
      (6: distance condition)]  default=4
Derangements:
 ct = 176214841
./bin 12 4  5.21s user 0.00s system 99% cpu 5.212 total
 ==> 176214841/5.21 == 33,822,426 per second

 time ./bin 14 1  ## involutions
arg 1: 14 == n  [Permutations of {1,2,...,n}]  default=5
arg 2: 1 == c  [Condition function: ...]
Involutions (self-inverse permutations):
 ct = 2390480
./bin 14 1  4.54s user 0.00s system 99% cpu 4.543 total
 ==> 2390480/4.54 == 526,537 per second

*/

/*
 for n in $(seq 1 55) ; do ./bin $n 12 | grep 'ct=' ; done
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/perm-restrpref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/perm-restrpref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

