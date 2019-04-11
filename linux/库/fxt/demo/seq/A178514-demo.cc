
#include "perm/perm-genus.h"  // perm_genus()
#include "comb/perm-restrpref.h"  // class perm_restrpref

#include "perm/perminvert.h"  // make_inverse()
#include "ds/bitarray.h"


#include "perm/printcycles.h"
#include "comb/comb-print.h"
#include "perm/permq.h"

#include "comb/fact2perm.h"

#include "fxtio.h"
#include "aux0/swap.h"
#include "fxttypes.h"

//#include "jjassert.h"

#include "nextarg.h"  // NXARG()

//% OEIS sequence A178514:
//% genus of derangements.
//% Also A178515: genus of involutions.
//% Also A178516: genus of up-down permutations.
//% Also A177267: genus of all permutations.
//% Also A178517: genus of non-derangement permutations.

// A178518: permutations of [n] having genus 0 and p(1)=k.

//% Cf. comb/perm-genus-demo.cc

//#define TIMING  // uncomment to disable printing

ulong z[32];
ulong czi[32];
ulong stats[32];
bitarray B(64);
// used here:
#ifdef TIMING
void visit(const ulong *a, ulong n, ulong)
{
    for (ulong i=0; i<n; ++i)  z[i] = a[i+1] - 1;
    ulong g = perm_genus(z, n, czi, &B);
    stats[g] += 1;
}
// -------------------------
#else // TIMING
void visit(const ulong *a, ulong n, ulong ct)
{
    for (ulong i=0; i<n; ++i)  z[i] = a[i+1] - 1;
    ulong g = perm_genus(z, n, czi, &B);
    stats[g] += 1;

    cout << setw(4) << ct << ":";
    print_perm("  ", z, n);
    cout << "  " << g;
//    print_cycles( "    ", z, n);
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

bool cond_inv(const ulong *a, ulong k)
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

ulong N;  // set to n in main()
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

static bool cnd[32];
bool cond_non_derange(const ulong *a, ulong k)
// non-derangement condition: f[k]==k for at least one k
{
    cnd[k] = cnd[k-1] | (a[k]==k);
    if ( k<N )
        return true;
    else
        return  cnd[k];
}
// -------------------------


int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Permutations of {1, 2, ..., n}");
    N = n;

    for (ulong j=0; j<n; ++j)  stats[j] = 0;

    ulong c = 4;
    NXARG(c, "Condition function:"
          "\n      (0: empty), (1: involutions),"
          "\n      (2: up-down), (3: indecomposable),"
          "\n      (4: derangement), (5: no [x,x+1])"
          "\n      (6: non-derangement)"
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
        perm = new perm_restrpref(n, cond_inv, visit);  break;
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
        cnd[0] = 0;
        cout << "Non-derangements (at least one fixed point):" << endl;
        perm = new perm_restrpref(n, cond_non_derange, visit);  break;

//    case 7:
//        cout << "Playground:" << endl;
//        perm = new perm_restrpref(n, cond_dist_set, visit);  break;

    default:
        cout << "Error!" << endl;
        return 1;
    }

    ulong ct = perm->all();


    for (ulong j=0; j<n; ++j)  cout << stats[j] << ", ";
    cout << endl;
    cout << " ct=" << ct << endl;

    delete perm;

    return 0;
}
// -------------------------

/*

Derangements (A178514):

 1:  0,
 2:  1, 0,
 3:  1, 1, 0,
 4:  3, 6, 0, 0,
 5:  6, 30, 8, 0, 0,
 6:  15, 130, 120, 0, 0, 0,
 7:  36, 525, 1113, 180, 0, 0, 0,
 8:  91, 2016, 8078, 4648, 0, 0, 0, 0,
 9:  232, 7476, 50316, 67408, 8064, 0, 0, 0, 0,
10:  603, 27000, 281862, 719640, 305856, 0, 0, 0, 0, 0,
11:  1585, 95535, 1459920, 6298930, 6223800, 604800, 0, 0, 0, 0, 0,
12:  4213, 332530, 7117902, 47851540, 90052336, 30856320, 0, 0, 0, 0, 0, 0,
13:  11298, 1141998, 33070752, 326618292, 1038687936, 822833856, 68428800, 0, 0, 0, 0, 0, 0,

Non-derangements (A178517):

 1:  1,
 2:  1, 0,
 3:  4, 0, 0,
 4:  11, 4, 0, 0,
 5:  36, 40, 0, 0, 0,
 6:  117, 290, 48, 0, 0, 0,
 7:  393, 1785, 1008, 0, 0, 0, 0,
 8:  1339, 9996, 12712, 1440, 0, 0, 0, 0,
 9:  4630, 52584, 123858, 48312, 0, 0, 0, 0, 0,
10:  16193, 264720, 1027446, 904840, 80640, 0, 0, 0, 0, 0,
11:  57201, 1290135, 7627158, 12449800, 3807936, 0, 0, 0, 0, 0, 0,
12:  203799, 6133930, 52188774, 140356480, 96646176, 7257600, 0, 0, 0, 0, 0, 0,
13:  731602, 28603718, 335517468, 1373691176, 1749377344, 448306560, 0, 0, 0, 0, 0, 0, 0,


Involutions (A178515):

 1:  1,
 2:  2, 0,
 3:  4, 0, 0,
 4:  9, 1, 0, 0,
 5:  21, 5, 0, 0, 0,
 6:  51, 25, 0, 0, 0, 0,
 7:  127, 105, 0, 0, 0, 0, 0,
 8:  323, 420, 21, 0, 0, 0, 0, 0,
 9:  835, 1596, 189, 0, 0, 0, 0, 0, 0,
10:  2188, 5880, 1428, 0, 0, 0, 0, 0, 0, 0,
11:  5798, 21120, 8778, 0, 0, 0, 0, 0, 0, 0, 0,
12:  15511, 74415, 48741, 1485, 0, 0, 0, 0, 0, 0, 0, 0,
13:  41835, 258115, 249249, 19305, 0, 0, 0, 0, 0, 0, 0, 0, 0,
14:  113634, 883883, 1201200, 191763, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
15:  310572, 2994355, 5519514, 1525095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
16:  853467, 10051860, 24408384, 10667800, 225225, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
17:  2356779, 33479460, 104552448, 67581800, 3828825, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,


Up-down permutations (A178516):

 1:  1,
 2:  1, 0,
 3:  2, 0, 0,
 4:  2, 3, 0, 0,
 5:  6, 10, 0, 0, 0,
 6:  6, 38, 17, 0, 0, 0,
 7:  22, 142, 104, 4, 0, 0, 0,
 8:  22, 351, 778, 234, 0, 0, 0, 0,
 9:  90, 1419, 4086, 2235, 106, 0, 0, 0, 0,
10:  90, 2856, 17402, 24357, 5816, 0, 0, 0, 0, 0,
11:  394, 12208, 87434, 171305, 78705, 3746, 0, 0, 0, 0, 0,
12:  394, 21676, 278062, 1053425, 1120648, 228560, 0, 0, 0, 0, 0, 0,
13:  1806, 96538, 1379035, 6532097, 10093748, 4078822, 186210, 0, 0, 0, 0, 0, 0,
14:  1806, 157416, 3643357, 29003045, 81711164, 71861423, 12982770, 0, 0, 0, 0, 0, 0, 0,
15:  8558, 723350, 18041640, 168584082, 612602752, 799624512, 291523362, 12649056, 0, 0, 0, 0, 0, 0, 0,


Indecomposable permutations (A185209):

 1:  1,
 2:  1, 0,
 3:  2, 1, 0,
 4:  5, 8, 0, 0,
 5:  14, 49, 8, 0, 0,
 6:  42, 268, 151, 0, 0, 0,
 7:  132, 1375, 1760, 180, 0, 0, 0,
 8:  429, 6768, 16184, 5712, 0, 0, 0, 0,
 9:  1430, 32354, 128578, 102917, 8064, 0, 0, 0, 0,
10:  4862, 151336, 923799, 1379384, 369944, 0, 0, 0, 0, 0,
11:  16796, 696027, 6164460, 15283308, 9233512, 604800, 0, 0, 0, 0, 0,
12:  58786, 3158280, 38863188, 147930256, 165848135, 36885312, 0, 0, 0, 0, 0, 0,
13:  208012, 14173566, 234193764, 1293232525, 2397551416, 1193273372, 68428800, 0, 0, 0, 0, 0, 0,


All permutations (A177267):

 1:  1,
 2:  2, 0,
 3:  5, 1, 0,
 4:  14, 10, 0, 0,
 5:  42, 70, 8, 0, 0,
 6:  132, 420, 168, 0, 0, 0,
 7:  429, 2310, 2121, 180, 0, 0, 0,
 8:  1430, 12012, 20790, 6088, 0, 0, 0, 0,
 9:  4862, 60060, 174174, 115720, 8064, 0, 0, 0, 0,
10:  16796, 291720, 1309308, 1624480, 386496, 0, 0, 0, 0, 0,
11:  58786, 1385670, 9087078, 18748730, 10031736, 604800, 0, 0, 0, 0, 0,
12:  208012, 6466460, 59306676, 188208020, 186698512, 38113920, 0, 0, 0, 0, 0, 0,
13:  742900, 29745716, 368588220, 1700309468, 2788065280, 1271140416, 68428800, 0, 0, 0, 0, 0, 0,


*/



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A178514-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A178514-demo.cc DEMOFLAGS=-DTIMING"
/// End:

