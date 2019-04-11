
#include "comb/composition-nz-restrpref.h"

#include "comb/comb-print.h"

#include "comb/is-unimodal.h"
#include "comb/is-smooth.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% Compositions of n into positive parts with restricted prefixes.
//% Lexicographic order.

// Cf. comb/composition-nz-demo.cc for all compositions

//#define TIMING  // uncomment to disable printing

bool cond_true(const ulong *, ulong)
{ return true; }
// -------------------------

bool cond_false(const ulong *, ulong)
{ return false; }
// -------------------------

bool cond_dist(const ulong *a, ulong k)
// Adjacent parts distinct.
// Carlitz compositions, A003242.
{
    if ( k==0 )  return true;
    return ( a[k] != a[k-1] );
}
// -------------------------

bool cond_consec(const ulong *a, ulong k)
// Partitions into consecutive integers.
// A001227 (odd divisors of n)).
{
    if ( k==0 )  return true;
    return  ( a[k] == a[k-1] + 1 );

//    return  ( a[k] == a[k-1] + 2 );  // A038548 Number of divisors <= sqrt(n).
}
// -------------------------

bool cond_updown(const ulong *a, ulong k)
// compositions with alternating increases and decreases:
// A025047 (and A025048, A025049).
{
    if ( k==0 )  return true;
    if  ( a[k] == a[k-1] )  return false;
    if ( k <= 1 )    return true;
    return ( (a[k-2] < a[k-1]) != (a[k-1] < a[k-0]) );
}
// -------------------------

bool cond_odd(const ulong *a, ulong k)
// Compositions into odd parts:
// A000045 (Fibonacci numbers).
{
    return  ( 1 == ( a[k] & 1UL ) );
//    return ( a[k] <= 2 );  // also Fibonacci
//    return ( a[k] >= 2 );  // also Fibonacci (A212804)
}
// -------------------------


bool cond_smooth(const ulong *a, ulong k)
// Absolute differences <= 1:  A034297.
{
    if ( k==0 )  return true;
//    if ( k==0 )  return  ( a[0]==1 );  // A000000
    ulong d = a[k] - a[k-1];
    if ( (long)d < 0 ) d = -d;
    return ( d <= 1 );
}
// -------------------------

bool cond_1diff(const ulong *a, ulong k)
// No flat-steps and Up-steps only of size == 1:  A238870.
{
    if ( k==0 )  return ( a[0]==1 );  // first part ==1
//    if ( k==0 )  return  true;
    ulong d = a[k] - a[k-1];
//    if ( (long)d < 0 ) d = -d;
    if ( (long)d < 0 )   return true;
    return ( d == 1 );
}
// -------------------------

bool cond_smooth_part(const ulong *a, ulong k)
// Flat partitions: differences <= 1:  A034296.
{
    if ( k==0 )  return true;

    ulong d = a[k-1] - a[k];
    if ( (long)d < 0 )  return false;  // descending list:
    return ( d <= 1 );  // A034296
    return ( d <= 2 );  // A224956

//    if ( (long)d > 0 )  return false;  // ascending list:
//    return ( -d <= 1 );  // A034296
//    return ( -d <= 2 );  // A224956


}
// -------------------------

bool cond_superdiag(const ulong *a, ulong k)
// superdiagonal compositions and partitions
{
//    if ( (k!=0) && (a[k] < a[k-1]) )  return false;  // partitions
//    if ( (k!=0) && (a[k] <= a[k-1]) )  return false;  // partitions into distinct parts

//    return ( a[k] > k+1 );
    // strictly superdiagonal:
    // compositions: A238874; partitions: A238394; dist. part: A025147 (parts >= 2)

    return ( a[k] > k );
    // superdiagonal:
    // compositions: A219282; partitions A238873; dist. part: A000009
}
// -------------------------


bool cond_subdiag(const ulong *a, ulong k)
{
//    if ( (k!=0) && (a[k] < a[k-1]) )  return false;  // partitions
//    if ( (k!=0) && (a[k] <= a[k-1]) )  return false;  // partitions into distinct parts
    return  ( a[k] <= k+1 );
    // subdiagonal:
    // compositions: A008930; partitions: A238875; dist. part.: A010054
}
// -------------------------

bool cond_superdiag_growth(const ulong *a, ulong k)
{
//    if ( (k!=0) && (a[k] < a[k-1]) )  return false;  // partitions
//    if ( (k!=0) && (a[k] <= a[k-1]) )  return false;  // partitions into distinct parts
//    if ( k==0 )  return true;
    return  ( (long)(a[k] - a[0]) >= (long)k );
    // subdiagonal growth:
    // compositions: A238861; partitions: A238860;  dist. part.: A000009
}
// -------------------------


bool cond_subdiag_growth(const ulong *a, ulong k)
{
//    if ( (k!=0) && (a[k] < a[k-1]) )  return false;  // partitions
//    if ( (k!=0) && (a[k] <= a[k-1]) )  return false;  // partitions into distinct parts
//    if ( k==0 )  return true;
//    return  ( a[k] - a[0] <= k );  // faulty: gives A177510
    return  ( (long)(a[k] - a[0]) <= (long)k );
    // subdiagonal growth:
    // compositions: A238859; partitions: A238876;  dist. part.: A001227
}
// -------------------------

bool cond_diff_growth(const ulong *a, ulong k)
{
    if ( k==0 ) return true;
    ulong d = a[k] - a[k-1];
    if ( (long)d < 0 )  return false;  // partitions
//    if ( (long)d <= 0 )  return false;  // partitions into distinct parts

    if ( k > 1 )
    {
        ulong t = a[k-1] - a[k-2];
        // successive differences non-decreasing:
//        if ( d < t )  return false;  // A240026;  dist: A179255
        // successive differences strictly increasing:
        if ( d <= t )  return false;  // A240027; dist: A179254
    }
    return true;
}
// -------------------------

bool cond_par_diff(const ulong *a, ulong k)
// Parities of adjacent part different: A062200
{
    if ( k==0 )  return true;
    return ( ((a[k]^a[k-1]) & 1) ==1 );
}
// -------------------------

bool cond_asc(const ulong *a, ulong k)
// Partitions as weakly ascending lists: A000041.
{
    if ( k==0 )  return true;
    return  ( a[k] >= a[k-1] );
}
// -------------------------

bool cond_desc(const ulong *a, ulong k)
// Partitions as weakly descending lists: A000041.
{
    if ( k==0 )  return true;
    return  ( a[k] <= a[k-1] );
}
// -------------------------

bool cond_growth(const ulong *a, ulong k)
// part(k) <= 2 * part(k-1):  A002843
{
    if ( k==0 )  return true;
    return  ( a[k] <= 2*a[k-1] );
}
// -------------------------

bool cond_fall(const ulong *a, ulong k)
// 2*part(k) <= part(k-1):  A000929
{
    if ( k==0 )  return true;
    return  ( 2*a[k] <= a[k-1] );
//    return  ( a[k] >= 2* a[k-1] );  // same ascending
//    return  ( 3*a[k] <= a[k-1] );  // A132011
}
// -------------------------

bool cond_diff_neq1(const ulong *a, ulong k)
// No distinct parts differ by 1:
// partitions:  A116931
// compositions: A238422
{
    if ( k==0 )  return true;
//    if ( ! cond_desc(a,k) )  return false;  // partition
    const ulong a0 = a[k],  a1 = a[k-1];
    const ulong d = ( a0 > a1 ? a0-a1 : a1-a0 );
    return ( d != 1 );  // no diff==1
//    return ( (d&1)!=0 );  // no even diff: part:A179080, comp:A062200
//    return ( (d&1)==0 );  // no odd diff: part:A096441, comp:A097896
}
// -------------------------


bool cond_wiggly1(const ulong *a, ulong k)
// A129852
{
    if ( k==0 )  return true;
    if ( k&1 )  return (a[k-1]<=a[k]);
    else        return (a[k-1]>=a[k]);
}
// -------------------------

bool cond_wiggly2(const ulong *a, ulong k)
// A129853
{
    if ( k==0 )  return true;
    if ( k&1 )  return (a[k-1]>=a[k]);
    else        return (a[k-1]<=a[k]);
}
// -------------------------


bool cond_change(const ulong *a, ulong k)
// Bounded change (cond_fall && cond_growth):  A224957
{
    if ( k==0 )  return true;
    if  ( a[k] > 2*a[k-1] )  return false;  // this only ==> A002843
    if  ( 2*a[k] < a[k-1] )  return false;  // this only ==> A002843
    return true;
}
// -------------------------

bool cond_mers_desc(const ulong *a, ulong k)
// s-partitions: partitions into Mersenne numbers: A000929
{
    ulong x = a[k];
    if ( !!(x & (x+1)) )  return false;
    if ( k==0 )  return true;
    return ( x<=a[k-1] );
}
// -------------------------


bool cond_mers(const ulong *a, ulong k)
// parts are Mersenne numbers: A104977 (absolute values)
{
    ulong x = a[k];
    return !(x & (x+1));
}
// -------------------------

bool cond_2pow(const ulong *a, ulong k)
// parts are powers of 2:  A023359
// As partitions: A018819, cf. A000123
{
    ulong x = a[k];
    return !(x & (x-1));
}
// -------------------------


bool cond_first_max(const ulong *a, ulong k)
{
    if ( k==0 )  return true;
//    return ( a[k] <= a[0] );  // first part max: A007059, A079500
    return ( a[k] < a[0] );  // first part strictly max: A007059
//    return  ( a[k] <=  a[0] + 1 );  // A048888
}
// -------------------------

bool cond_first_min(const ulong *a, ulong k)
{
    if ( k==0 )  return true;
    return ( a[k] >= a[0] );  // first part min: A171682
//    return ( a[k] > a[0] );  // first part strictly min: A079501
//    return  ( a[k] >=  a[0] - 1 );  // A224960
}
// -------------------------

bool cond_min(const ulong *a, ulong k)
{
    return  ( a[k] >= 2 );  // A000045 a(n)=a(n-1)+a(n-2)
//    return  ( a[k] >= 3 );  // A000930 a(n)=a(n-1)+a(n-3)
//    return  ( a[k] >= 4 );  // A003269 a(n)=a(n-1)+a(n-4)
}
// -------------------------

bool cond_no_3prog(const ulong *a, ulong k)
// No 3 consecutive parts in arithmetic progression:
// compositions: A238423
// partitions:   A238424
{
//    if ( k!=0 )  if ( a[k]>a[k-1] )  return false;  // partitions

    if ( k<=1 )  return true;
    ulong d1 = a[k] - a[k-1];
    ulong d2 = a[k-1] - a[k-2];
    return ( d1 != d2 );
}
// -------------------------

bool cond_2dist(const ulong *a, ulong k)
// part(k) != part(k-2):
// Partitions: A000726; compositions A224958.
{
//    if ( k!=0 )  if ( a[k]>a[k-1] )  return false;  // partitions: A000726
    if ( k<=1 )  return true;
    return ( a[k] != a[k-2] );
}
// -------------------------

bool cond_up_step(const ulong *a, ulong k)
// Limited up-steps
{
    if ( k==0 )  return true;
    if ( a[k] > a[k-1] )  return ( (a[k] - a[k-1]) <= 1 );  // A003116
//    if ( a[k] > a[k-1] )  return ( (a[k] - a[k-1]) <= 2 );  // A224959
    return true;
}
// -------------------------


bool cond_test(const ulong *a, ulong k)
{
    if ( k==0 )  return true;

    if ( 0!=(k&1) )  return ( a[k] <= a[k-1] ); // A028495
//    if ( 0!=(k&1) )  return ( a[k] < a[k-1] ); // A000045
//    if ( 0==(k&1) )  return ( a[k] <= a[k-1] ); // abs(A078038)
//    if ( 0==(k&1) )  return ( a[k] < a[k-1] ); // A000045

//    if ( 0!=(k&1) )  return ( a[k] >= a[k-1] ); // A028495
//    if ( 0!=(k&1) )  return ( a[k] > a[k-1] ); // A000045
//    if ( 0==(k&1) )  return ( a[k] >= a[k-1] ); // abs(A078038)
//    if ( 0==(k&1) )  return ( a[k] > a[k-1] ); // A000045

    return true;

//    if ( k==0 )  return ( a[k]==1 );  //A002083
//    ulong s =0;
//    for (ulong j=0; j<k; ++j)  s += a[j];
//    return ( a[k] <= s );

//    if ( k==0 )  return true;  // no two adjacent non-ones A005251
//    return ( (a[k]==1) || (a[k-1]==1) );

//    if ( k==0 )  return ( 0==(a[0]%2) );  // first part even/odd: A001045
//    if ( a[k] > a[k-1] )  return false;  // A027187 (even), cf. A027193 (odd)
//    return true;

//    return ( a[k]!=k );  // A000000
//    return ( a[k]!=k+1 );  // A000000

//    return  ( a[k] <= k + a[0] );  // A000000
//    return  ( a[k] <= 2*a[0] );  // A000000
//    return  ( a[k] <= a[0] + 1 );  // A048888
//    return  ( a[k] <= a[0] + 2 );  // A000000
//    return  ( a[k] <= (k+1)*a[0] );  // A000000

//    return  ( a[k-1] >= a[k] );  // partitions (desc)
//    return  ( 2*a[k] <= 3*a[k-1] );  // A000000
}
// -------------------------

//  echo $(for n in $(seq 1 20); do ./bin $n 99; done | grep ct= ) | sed 's/ ct=/, /g;'


int
main(int argc, char **argv)
{
    ulong n = 7;
    NXARG(n, "compositions of n (n>=1)");

    ulong c = 5;
    NXARG(c, "Condition function:"
          "\n      0 ==> all compositions (condition always true),"
          "\n      1 ==> adjacent digits distinct"
          "\n      2 ==> up-down"
          "\n      3 ==> consecutive parts"
          "\n      4 ==> odd parts"
          "\n      5 ==> growth condition: a[k] <= 2*a[k-1]"
          "\n      6 ==> fall condition: 2*a[k] <= a[k-1]"
          "\n      7 ==> parts are Mersenne numbers"
          "\n      8 ==> parts are Mersenne numbers, partitions"
          "\n      9 ==> parts are powers of 2"
//          "\n      rest ==> see source"
          );


    composition_nz_restrpref P(n, cond_true);

    switch ( c )
    {
    case 0: P.first( cond_true );  break;
    case 1: P.first( cond_dist );  break;
    case 2: P.first( cond_updown );  break;
    case 3: P.first( cond_consec );  break;
    case 4: P.first( cond_odd );  break;
    case 5: P.first( cond_growth );  break;
    case 6: P.first( cond_fall );  break;
    case 7: P.first( cond_mers );  break;
    case 8: P.first( cond_mers_desc );  break;
    case 9: P.first( cond_2pow );  break;


    case 20: P.first( cond_change );  break;
    case 22: P.first( cond_2dist );  break;

    case 33: P.first( cond_no_3prog );  break;

    case 40: P.first( cond_par_diff );  break;

    case 45: P.first( cond_first_max );  break;
    case 46: P.first( cond_first_min );  break;
    case 47: P.first( cond_min );  break;

    case 50: P.first( cond_asc );  break;
    case 51: P.first( cond_desc );  break;

    case 55: P.first( cond_up_step );  break;

    case 60: P.first( cond_smooth );  break;
    case 61: P.first( cond_smooth_part );  break;

    case 65: P.first( cond_1diff );  break;
    case 66: P.first( cond_diff_growth );  break;

    case 70: P.first( cond_superdiag );  break;
    case 71: P.first( cond_subdiag );  break;
    case 72: P.first( cond_superdiag_growth );  break;
    case 73: P.first( cond_subdiag_growth );  break;

    case 88: P.first( cond_false );  break;

    case 91: P.first( cond_wiggly1 );  break;
    case 92: P.first( cond_wiggly2 );  break;

    case 95: P.first( cond_diff_neq1 );  break;

    case 99: P.first( cond_test );  break;


    default:  cout << "Not a valid condition!" << endl;
        return 1;
    }

    ulong ct = 0;

#ifdef TIMING
    P.first( );
    while ( P.valid() )  { ++ct;  P.next(); }

#else  // TIMING

    ulong aa = 0;
    NXARG(aa, "If aa!=0, render as compositions (1) or fountains of coins (2)");

    while ( P.valid() )
    {
        ++ct;
#if 0
        cout << setfill('0');
        cout << "" << setw(2) << ct << "";  // format for OEIS examples
        cout << setfill(' ');
        cout << ":";
#else
        cout << setw(2) << ct << ":";
//        ulong m = P.num_parts();
//        cout << "  [" << setw(2) << m << "]";
#endif

        P.print("  ");

        cout << endl;

        if ( aa )  // ASCII art
        {
            if ( aa & 1 )  P.print_composition_aa();
            if ( aa & 2 )  P.print_fountain_aa();
            cout << endl;
            cout << endl;
        }

        jjassert( P.OK() );
        P.next();
    }

#endif  // TIMING

    cout << " ct=" << (n!=0 ? ct : 1) << endl;  // report ct=1 for n==0

    return 0;
}
// -------------------------

/*

q=33 # choose condition

condition q for OEIS sequence:
 echo $(for n in $(seq 1 30) ; do ./bin $n $q | grep ct=; done) | sed 's/ct=//g; s/ /, /g;'

OEIS example:
 ./bin 6 $q | sed 's/^ /0/;'

*/


/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 30 0
arg 1: 30 == n  [compositions of n (n>=1)]  default=9
[...]
 ct=536870912
./bin 30 0  6.92s user 0.00s system 99% cpu 6.927 total
 ==> 536870912/6.92 == 77,582,501 per second

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/composition-nz-restrpref-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/composition-nz-restrpref-demo.cc DEMOFLAGS=-DTIMING"
/// End:

