
#include "comb/mixedradix-restrpref.h"

#include "aux1/copy.h"  // fill()

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"
#include "fxtalloca.h"
#include "fxtio.h"
#include "jjassert.h"

#include <cstdlib>  // strtoul()


//% Mixed radix counting with restricted prefixes.


// Cf. comb/perm-restrpref-demo.cc for permutations with restricted prefixes.


//#define TIMING  // uncomment to disable printing

bool cond_true(const ulong *, ulong)
{ return true; }
// -------------------------

bool cond_false(const ulong *, ulong)
{ return false; }
// -------------------------


bool cond_dist(const ulong *a, ulong k)
// Adjacent digits distinct.
// Radix 2 gives A000045
// Radix 3 gives A001045
// Length n, radix n gives A055897
// Length n, radix n-1 gives A209290
// Length n, radix n+1 gives A055541 (same as A061302)
{
    if ( k==0 )  return true;
    if ( a[k] == a[k-1] )  return false;
    return true;
}
// -------------------------

bool cond_dist2(const ulong *a, ulong k)
// digits a[k] and a[k+2] distinct
{
    if ( k<=1 )  return true;
    if ( a[k] == a[k-2] )  return false;
    return true;
}
// -------------------------

bool cond_nonadj(const ulong *a, ulong k)
// NAF: no two adjacent nonzero digits
// For factorial bases this gives A000085 (involutions)
{
    if ( k==0 )  return true;
    if ( a[k] * a[k-1] )  return false;
//    if ( a[k] == a[k-1] )  return false;  // A060696
    return true;
}
// -------------------------


bool cond_sorted(const ulong *a, ulong k)
// Sorted digits (weakly ascending).
// For the rising factorial basis this gives A000108 (Catalan)
{
    if ( k==0 )  return true;
    if ( a[k] < a[k-1] )  return false;
    return true;
}
// -------------------------

bool cond_sorted_desc(const ulong *a, ulong k)
// Sorted digits (weakly descending).
// For the falling factorial basis this gives A000108 (Catalan)
{
    if ( k==0 )  return true;
    if ( a[k] > a[k-1] )  return false;
    return true;
}
// -------------------------

bool cond_smooth(const ulong *a, ulong k)
// Adjacent digits have absolute difference <= 1
// For factorial bases this gives A005773
// Smooth n-digit radix-n numbers: A081113
//   for n in $(seq 2 10); do ./bin $n $n 4 | g ct= ; done
{
    if ( k==0 )  return true;
    ulong d =  a[k] - a[k-1];
    if ( d == -1UL ) d = -d;
    if ( d > 1 )  return false;
    return true;
}
// -------------------------

bool cond_par(const ulong *a, ulong k)
// Adjacent digits have different parities.
// For factorial bases this gives A219024
{
    if ( k==0 )  return true;
    if ( 0==(1 & (a[k] ^ a[k-1])) )  return false;
    return true;
}
// -------------------------

bool cond_sorted_full(const ulong *a, ulong k)
// Sorted digits (weakly ascending), and all digits are there.
// For the rising factorial basis this gives powers of two,
{
    if ( k==0 )  return ( a[0] == 0 );
    if ( a[k] < a[k-1] )  return false;
    if ( a[k] > a[k-1]+1 )  return false;
    return true;
}
// -------------------------

bool cond_ccf_map(const ulong *a, ulong k)
// For the rising factorial basis this gives A000110
// See  class setpart_ccf_rgs_lex
{
    ulong ak = a[k];
    if ( ak==0 )  return true;
    if ( ak > k )  return false;
    if ( a[ak-1] != 0 )  return false;
    return true;
}
// -------------------------

bool cond_aj_neq_akp1(const ulong *a, ulong k)
// No digit a[j] in prefix such that a[j] == a[k] + 1
// For the rising factorial basis this gives
// A022493 (ascent sequences, Fishburn numbers),
//   see  class ascent_alt_rgs
// Base 3 gives A132109
{
//    if ( k==0 )  return ( a[0]==1 );
    if ( k==0 )  return true;
//    if ( (a[k]==0) && (a[k-1]==0) )  return false;  // A000000

    ulong ak1 = a[k] + 1;  // rfact: A022493, base n:  A088789
//    ulong ak1 = a[k] - 1; // ffact: A022493, rfact: A000000, base n: A088789

    for (ulong j=0; j<k; ++j)
        if ( a[j] == ak1 )  return false;
//        if ( a[j] > ak1 )  return false;  // A006318 cf. class schroeder_rgs_lex
    return true;
}
// -------------------------

bool cond_ascent(const ulong *a, ulong k)
// A022493 (ascent sequences, Fishburn numbers)
// See  class ascent_rgs
{
    if ( k==0 )  return ( a[0]==0 );
//    if ( k==0 )  return true;
    ulong s = 0;
    for (ulong j=1; j<k; ++j)
        s += ( a[j] > a[j-1] );  // count ascents ==> A022493
    if ( a[k] > s + 1 )  return false;
    return true;
}
// -------------------------
// compare to:
bool cond_descent(const ulong *a, ulong k)
// A225588 (descent sequences)
// See  class descent_rgs
{
    if ( k==0 )  return ( a[0]==0 );
//    if ( k==0 )  return true;
    ulong s = 0;
    for (ulong j=1; j<k; ++j)
        s += ( a[j] < a[j-1] );  // count descents ==> A225588
    if ( a[k] > s + 1 )  return false;
    return true;
}
// -------------------------
// compare to:
bool cond_change(const ulong *a, ulong k)
// A000522 (arrangements)
{
    if ( k==0 )  return ( a[0]==0 );
//    if ( k==0 )  return true;
    ulong s = 0;
    for (ulong j=1; j<k; ++j)
        s += ( a[j] != a[j-1] ); // count changes ==> A000522
    if ( a[k] > s + 1 )  return false;
    return true;
}
// -------------------------
// compare to:
bool cond_eq(const ulong *a, ulong k)
// A000110 (set partitions)
{
    if ( k==0 )  return ( a[0]==0 );
//    if ( k==0 )  return true;
    ulong s = 0;
    for (ulong j=1; j<k; ++j)
        s += ( a[j] == a[j-1] ); // count non-changes ==> A000110
    if ( a[k] > s + 1 )  return false;
    return true;
}
// -------------------------

bool cond_total_ascent(const ulong *a, ulong k)
// Total ascent: A000000
{
    if ( k==0 )  return ( a[0]==0 );
//    if ( k==0 )  return true;
    ulong s = 0;
    for (ulong j=1; j<k; ++j)
        s += ( a[j] > a[j-1] ? a[j] - a[j-1] : 0 );
    if ( a[k] > s + 1 )  return false;
    return true;
}
// -------------------------


bool cond_pref_sum(const ulong *a, ulong k)
// conditions on sum of digits in prefix
{
//    if ( k==0 )  return ( a[0]==0 );
//    if ( k==0 )  return true;
    ulong s = 0;
    for (ulong j=0; j<k; ++j)
        s += a[j];
//    if ( a[k] > s+1 )  return false;  // A000000
//    if ( a[k] < s )  return false; // A131205 (args n n)
    if ( a[k] == s )  return false; // A000000
    return true;
}
// -------------------------

bool cond_pref_fixedpoints(const ulong *a, ulong k)
// k <= number of fixed points in prefix
{
    if ( k==0 )  return ( a[0]==0 );
    ulong s = 0;
    for (ulong j=0; j<k; ++j)  s += ( j == a[j] );

    return ( a[k] <= s ); // A047970
}
// -------------------------


bool cond_upstep(const ulong *a, ulong k)
// weakly increasing, no upstep by 1
// Length n, radix n   ==> A005773
// Length n, radix n+1 ==> A025565
// Length n, radix n-1 ==> A005717
// Length n, radix n-2 ==> A000000
// Length n, radix n+2 ==> A225034
// Length n, radix n+3 ==> A000000
// Length n, radix n-3 ==> A000000
{
    if ( k==0 )  return true;
    if ( a[k] < a[k-1] )  return false;
    return ( a[k] - a[k-1] != 1 );
}
// -------------------------


bool cond_dist_smooth(const ulong *a, ulong k)
// Adjacent digits differ and have absolute difference <= 1
// For factorial bases this gives A050168
// Base 3: A063759
// Base 4: A128588.
{
    if ( k==0 )  return true;
    if ( a[k] == a[k-1] )  return false;
    ulong d =  a[k] - a[k-1];
    if ( d == -1UL ) d = -d;
    if ( d > 1 )  return false;
    return true;
}
// -------------------------


bool cond_fp_ptr(const ulong *a, ulong k)
// f(x)<=x and either f(x)==x or f(z) == z where z := f(f(x)),
// that is, f(x)<=x and f^2 == f^3
// A187761, cf. class map23_rgs
{
    ulong d = a[k];  // d=f(x)
    if ( d>k )  return false;  // f(x) <= x
//    if ( d==k )  return true;  // fixed point OK: f(x)==x  // can be omitted

//    ulong z = d; // a[k] is either a fixed point or a digit from the prefix (==> A000110)
    ulong z = a[d];  // z=f(f(x))
    return ( z == a[z] );
//    return true;
}
// -------------------------

bool cond_setpart(const ulong *a, ulong k)
// Either f(x)==0 or f(f(x)) == 0 (==> A000110)
// See class setpart_zero_map_rgs
{
    ulong d = a[k];
    if ( d>k )  return false;  // f(x) <= x
    if ( d==0 )  return true;  // zero OK
//    if ( a[k-d] )  return false;
    if ( a[d] )  return false;

    return true;
}
// -------------------------

bool cond_setpart2(const ulong *a, ulong k)
// Either f(x)==0 or f(x-f(x)) == 0 (==> A000110)
{
    ulong d = a[k];
    if ( d>k )  return false;  // f(x) <= x
    if ( d==0 )  return true;  // zero OK
    if ( a[k-d] )  return false;
//    if ( a[d] )  return false;

    return true;
}
// -------------------------

bool cond_setpart3(const ulong *a, ulong k)
// Either f(x)==0 or f(f(x)-1) == 0 (==> A000110)
{
    ulong d = a[k];
    if ( d>k )  return false;  // f(x) <= x
    if ( d==0 )  return true;  // zero OK
    if ( a[d-1] )  return false;
    return true;
}
// -------------------------


bool cond_setpart0(const ulong *a, ulong k)
// no digit greater than the number of zeros in prefix (==> A000110)
{
    ulong d = a[k];
    ulong z = 0;
    for (ulong j=0; j<k; ++j)
        z += ( a[j]==0 );
    if ( d > z )  return false;

    return true;
}
// -------------------------


bool cond_invol_fp(const ulong *a, ulong k)
// Either fixed point or only digit that repeats a previous fixed point:
// A000085 (involutions)
{
    ulong d = a[k];
    if ( d > k )  return false;  // f(x) <= x
    if ( d==k )  return true;  // fixed point OK

//    if ( d==0 )  return true;  // zero OK ==> A005425

    ulong v = a[d];
    if ( v < k )  // must be only pointer down to v
    {
        for (ulong j=v+1; j<k; ++j)
            if ( v==a[j] )  return false;
    }

    return true;
}
// -------------------------

bool cond_zero_map_s(const ulong *a, ulong k)
// Either zero or only digit that points to a zero:
// Parameter s: set partitions into sets of size at most s+1
// s>=2: A000085 (involutions)
{
    ulong d = a[k];
    if ( d>k )  return false;  // f(x) <= x
    if ( d==0 )  return true;  // zero OK

    if ( a[d] != 0 )  return false;

    ulong s = 0;
    for (ulong j=0; j<=k; ++j)
        s += ( d==a[j] );
    if ( s >= 2 )  return false;  // A000085, e.g.f. exp(x+x^2/2)
//    if ( s >= 3 )  return false;  // A001680, e.g.f. exp(x+x^2/2+x^3/6)
//    if ( s >= 4 )  return false;  // A001681, e.g.f. exp(x+x^2/2+x^3/6+x^4/24)
//    if ( s >= 5 )  return false;  // A110038, e.g.f. exp(x+x^2/2+x^3/6+x^4/24+x^5/120)
    // no condition on s: A000110, e.g.f. exp(exp(x)-1)

    return true;
}
// -------------------------

bool cond_arrange(const ulong *a, ulong k)
// no digit equal to 1 + number of non-zero digits in prefix
// A000522 (arrangements) with rfact
{
    ulong d = a[k];
    ulong z = 0;
    for (ulong j=0; j<k; ++j)
        z += ( a[j]!=0 );
    if ( d > z+1 )  return false;

    return true;
}
// -------------------------

bool cond_arrange1(const ulong *a, ulong k)
// no digit equal to 2 + number of zeros in prefix
// A000522 (arrangements) with rfact
{
    ulong d = a[k];
    ulong z = 0;
    for (ulong j=0; j<k; ++j)
        z += ( a[j]==0 );
    if ( d == z+2 )  return false;

    return true;
}
// -------------------------

bool cond_arrange2(const ulong *a, ulong k)
// no digit equal to -1 + number of non-zero digits in prefix
// A000522 (arrangements) with rfact
{
    ulong d = a[k];
    ulong z = 0;
    for (ulong j=0; j<k; ++j)
        z += ( a[j]!=0 );
    if ( d == z-1 )  return false;

    return true;
}
// -------------------------

bool cond_perm(const ulong *a, ulong k)
// no digit+1 equal to number of non-zero digits in prefix
// n! (permutations) with rfact
{
    ulong d = a[k];
    ulong z = 0;
    for (ulong j=0; j<k; ++j)
        z += ( a[j]!=0 );
    if ( d == z+1 )  return false;

    return true;
}
// -------------------------

bool cond_perm_ncyc(const ulong *a, ulong k)
{
    ulong d = a[k];
    ulong z = 0;  // number of zeros in prefix
    for (ulong j=0; j<k; ++j)
        z += ( a[j]==0 );
//    if ( d == z-0 )  return false;  // all permutations
//    if ( d == z-1 )  return false;  // A000774 permutations into at most two cycles
//    if ( d == z-2 )  return false;  // A000000
//    if ( d == z+1 )  return false;  // all permutations
    if ( d == z+2 )  return false;  // A000522 (arrangements)
//    if ( d == z+3 )  return false;  // A000000

    return true;
}
// -------------------------

bool cond_12_dist(const ulong *a, ulong k)
{
    ulong d = a[k];
    if ( (d!=1) && (d!=2) )  return false;
    if ( k!=0 )  return ( d != a[k-1] );
    return true;
}
// -------------------------

bool cond_leq_23(const ulong *a, ulong k)
// base n: A141043
{
    if ( k < 2 ) return true;
    if ( a[k] <= a[k-2] )  return false;
    if ( k < 3 ) return true;
    if ( a[k] <= a[k-3] )  return false;
    return true;
}
// -------------------------

bool cond_test(const ulong *a, ulong k)
{
    if ( k<2 )  return true;
    // following OEIS a-numbers: rfact, base-2, base-3
    if ( (a[k-2]>a[k-1]) && (a[k]!=0) )  return false;  // A000000, A005251, A052101
//    if ( (a[k-2]<a[k-1]) && (a[k]!=0) )  return false;  // A000000, A000071, A000000
//    if ( (a[k-2]==a[k-1]) && (a[k]!=0) )  return false;  // A000000, A171861, A000000
//    if ( (a[k-2]!=a[k-1]) && (a[k]!=0) )  return false;  // A000000, A038718, A000000
    return true;

    ulong d = a[k];

    if ( k==0 )  return (d==1);
    return d <= (k+1)*a[k-1];  // A007489

    ulong z = 0;
    for (ulong j=0; j<k; ++j)
//        z += ( a[j]==k );  // A058798
        z += ( a[j]==j );  // A000522 (arrangements)
    if ( d < z )  return false;

//    if ( k!=0 )  return ( a[k]!=a[k-1] );  // A098558
//    return ( a[k]<=k/2 );  // A010551

    return true;
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 4;
    NXARG(n, "Number of digits");

    ulong rr = 1;
    NXARG(rr, "Base (radix) of digits (0==>falling factorial, 1==>rising factorial)");

    ALLOCA(ulong, r, n);
    fill(r, n, rr);
#if 0
    RESTARGS("Optionally supply radix for all digits (rr ignored)");
    if ( argc>3 )  jjassert( argc == (int)n+3 );
    for (ulong k=3;  k<(ulong)argc; ++k)  r[k-3] = strtoul(argv[k], 0, 10);
    mixedradix_restrpref M(n, rr, (argc>3? r:0), cond_true );
#else
    mixedradix_restrpref M(n, rr, 0, cond_dist2 );
#endif

    ulong c = 4;
    NXARG(c, "Condition function:"
          "\n      0 ==> all words (condition always true),"
          "\n      1 ==> no two adjacent nonzero digits,"
          "\n      2 ==> adjacent digits distinct"
          "\n      3 ==> sorted (weakly ascending) digits"
          "\n      4 ==> smooth: adjacent digits have absolute difference <= 1"
          "\n      5 ==> adjacent digits have different parities"
//          "\n      rest ==> see source"
          );


    switch ( c )
    {
    case 0: M.first( cond_true );  break;
    case 1: M.first( cond_nonadj );  break;
    case 2: M.first( cond_dist );  break;
    case 3: M.first( cond_sorted );  break;
    case 4: M.first( cond_smooth );  break;
    case 5: M.first( cond_par );  break;


    case 11: M.first( cond_dist_smooth );  break;
    case 12: M.first( cond_dist2 );  break;
    case 13: M.first( cond_sorted_full );  break;
    case 14: M.first( cond_ccf_map );  break;

    case 15: M.first( cond_ascent );  break;
    case 16: M.first( cond_aj_neq_akp1 );  break;
    case 17: M.first( cond_descent );  break;
    case 18: M.first( cond_change );  break;
    case 19: M.first( cond_eq );  break;

    case 20: M.first( cond_invol_fp );  break;
    case 21: M.first( cond_zero_map_s );  break;

    case 22: M.first( cond_fp_ptr );  break;


    case 30: M.first( cond_arrange );  break;
    case 31: M.first( cond_arrange1 );  break;
    case 32: M.first( cond_arrange2 );  break;

    case 40: M.first( cond_perm );  break;
    case 41: M.first( cond_perm_ncyc );  break;

    case 50: M.first( cond_sorted_desc );  break;

    case 60: M.first( cond_pref_sum );  break;

    case 70: M.first( cond_upstep );  break;

    case 90: M.first( cond_setpart0 );  break;
    case 91: M.first( cond_setpart );  break;
    case 92: M.first( cond_setpart2 );  break;
    case 93: M.first( cond_setpart3 );  break;

    case 99: M.first( cond_test );  break;

    case 110: M.first( cond_12_dist );  break;

    case 120: M.first( cond_leq_23 );  break;

    case 130: M.first( cond_pref_fixedpoints );  break;

    case 150: M.first( cond_total_ascent );  break;

    default: M.first( cond_true );  break;
    }

    cout << endl;

    ulong ct = 0;

    while ( M.valid() )
    {
        ++ct;

#ifndef TIMING
        cout << " " << setw(4) << ct << ":";
        M.print("  ", true );
        cout << "  " << M.pos();
        cout << endl;
#endif

        M.next();
    }

    cout << " ct=" << ct << endl;

    return 0;
}
// -------------------------


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 20 4
arg 1: 20 == n  [Number of digits]  default=4
arg 2: 4 == rr  [Base (radix) of digits (0==>falling factorial, 1==>rising factorial)]  default=1
arg 3: 4 == c  [Condition function: ... ]
 ct=331160282
./bin 20 4  6.21s user 0.00s system 99% cpu 6.217 total
 ==> 331160282/6.21 == 53,326,937 per second

*/

// % echo $(for n in $(seq 0 11); do ./bin $n 1 150 | grep ct= | sed 's/ ct=//;s/$/, /;' ; done)


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/mixedradix-restrpref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/mixedradix-restrpref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

