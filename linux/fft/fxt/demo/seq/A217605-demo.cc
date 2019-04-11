
#include "comb/partition.h"

//#include "aux0/factorial.h"

#include "fxttypes.h"

#include "jjassert.h"
#include "nextarg.h"

#include "fxtio.h"

//% OEIS sequence A217605:
//% Number of partitions that are fixed points of a certain map.

// Cf. comb/partition-demo.cc

//#define TIMING  // uncomment to disable printing


int
main(int argc, char **argv)
{
    ulong n = 16;
    NXARG(n, "Partitions of n");
    bool sq = 0;
    NXARG(sq, "Whether to print in partitions in falling order");
    partition P(n);

    ulong *Z = new ulong[n+1];  // scratch space
    for (ulong j=0; j<=n; ++j)  Z[j] = 0;

    ulong ct = 0;

    do
    {
//        if ( P.num_of(1) == 0 )  { ct += 1; }  // A002865: no part == 1.
//        if ( P.num_of(2) == 0 )  { ct += 1; }  // A027336: no part == 2.

//        if ( P.num_of(1) == 0 )  { ct += P.num_of(3); }  // A182713
//        if ( P.num_of(1) == P.num_of(2) )  { ct += 1; }  // A174455: number of 1's and 2's are equal.
//        if ( P.num_of(1) != P.num_of(2) )  { continue; }  // A174455 (show partitions)

//        if ( P.num_of(1) != 0 )  continue;
//        { ulong m=2; while ( P.num_of(m) == 0 )  { ++m; };  ct += m; }

//        { ulong m=1; while ( P.num_of(m) == 0 )  { ++m; }; ct += (n-m*P.num_of(m)); }
//        { ulong m=; while ( P.num_of(m) == 0 )  { ++m; }; ct += (n-m*P.num_of(m)); }

//        { const ulong *d = P.data();
//            ulong k;
//            for (k=2; k<=n; ++k)
//                if ( d[k] > d[k-1]  )  break;   // A007294
//            ct += (k>n);
//        }

//        ct += (  P.num_parts() == P.num_sorts() );  // A000009: distinct parts
//        ct += (  P.num_parts() != P.num_sorts() );  // A047967: some part repeated

//        { long s = 0;  // number of even vs. number of odd terms
//            for (ulong k=1; k<=n; k+=2)  s += P.num_of(k);  // num odd
//            for (ulong k=2; k<=n; k+=2)  s -= P.num_of(k);  // num even
//
//            ct += (s==0);  // A045931: equal number of even and odd parts
//            ct += (s>=0);  // A130780: number of odd parts >= to number of even parts.
//            ct += (s<0);  // A108949: more even parts than odd parts.
//            ct += (s<=0);  // A171966: not more odd than even parts.
//            ct += (s>0);  // A108950: more odd parts than even parts.
//            ct += (s==1);  // A000000: one more odd part than even parts
//            ct += (s==-1);  // A000000 (as above, shifted right)
//        }

//        ct += ( (P.num_parts()&1)==1 );  // A027193
//        ct += ( (P.num_parts()&1)==0 );  // A027187

//        ct += ( (P.num_sorts()&1)==1 );  // A090794
//        ct += ( (P.num_sorts()&1)==0 );  // A092306

//        { long r = P.rank();
//            if ( r==P.num_parts() )  ct += 1; // A237753: 2*(greatest part) = (number of parts)
//            if ( r>=0 )  ct += 1; // A064174: nonnegative rank.
//            if ( r>0 )  ct += 1; // A064173: positive rank.
//            if ( r>0 )  ct += ( r%2UL==0 );  // A101708: positive even rank
//            if ( r>0 )  ct += ( r%2UL==1 );  // A101707: positive odd rank
//            if ( r>=0 )  ct += ( r%2UL==0 );  // A101709: nonnegative even rank
//            ct += ( r==0 );  // A047993: largest part equals the number of parts
//            ct += ( r==1 );  // A101198: rank == 1
//            ct += ( r==2 );  // A101199: rank == 2
//            ct += ( r==-2 );  // A101199 (by symmetry)
//            ct += ( r==3 );  // A101200: rank == 3
//            ct += ( r==4 );  // A000000: rank == 4
//            ct += ( r==5 );  // A000000: rank == 5
//            ct += ( r%2UL==0 ? +1 : -1 );  // A000025: 3rd order mock theta function f(q)
//        }



//        if ( P.num_parts() == 2*P.largest_part() )  { ct += 1; }  // A237753: 2*(greatest part) = (number of parts)
//        if ( P.num_parts() >= P.largest_part() )  { ct += 1; }  // A064174: nonnegative rank
//        if ( P.num_parts() < P.largest_part() )  { ct += 1; }  // A064173: positive rank

//        if ( P.is_dist_parts() )
//        {
//            ct += ( P.num_parts() < P.largest_part() );  // A000000: positive rank
//            ct += ( P.num_parts() <= P.largest_part() );  // A000009 (all dist.)
//            ct += ( 2 * P.num_parts() == P.largest_part() );  // A000000
//            ct += ( (P.num_parts()%2==0) && (P.largest_part()%2==0) );  // A000000
//            ct += ( P.num_parts()%2==0 );  // A067661: distinct parts, number of parts is an even
//            ct += ( P.num_parts()%2==1 );  // A067659: number of parts is odd
//            ct += ( P.num_parts()==P.rank() );  // A000000
//        }


// Abramowitz/Stegun order (conjugate partitions):
//        cout << P.largest_part() << ", ";  // A036043
//        cout << P.num_parts() << ", ";  // A049085
//        cout << -P.rank() << ", ";  // A105805
//        cout << P.num_sorts() << ", ";  // A103921 / reversed lines: A115623
// cf. A117194, A117195


//        if ( P.num_parts() == P.largest_part() )  { ct += 1; }  // A047993
//        if ( P.num_parts() != P.largest_part() )  continue;  // A047993
        // A047993: balanced partitions: first element = number of elements.
        // largest part is equal to number of parts.

//        if ( P.num_parts() == P.smallest_part() )  { ct += 1; }  // A006141: smallest part == number of parts


//        { // A098859: Wilf partitions: all multiplicities are distinct
//            for (ulong j=0; j<=n; ++j)  Z[j] = 0;
//            bool q = true;
//            for (ulong k = 1; k<=n; ++k)
//            {
//                ulong ck = P.num_of(k);
//                if ( ck && (Z[ck]!=0) )
//                { q = false;  break; }
//                Z[ck] = 1;
//            }
//            ct += q;
//            if ( !q )  continue;
//        }


//        {  // compositions into distinct parts:
//            if ( ! P.is_dist_parts() )  continue;
//
////            ct += factorial( P.num_parts() );  // A032020: compositions into distinct parts.
//
////            if ( ! P.is_into_odd_parts() )  continue;
////            ct += factorial( P.num_parts() );  // A032021: compositions into distinct odd parts.
//
//            bool q = true;
//            for (ulong k=1; k<=n; ++k)
//                if ( P.num_of(k) && ( (k%3)!=1 ) ) { q = false;  break; }
//            if ( q )  ct += factorial( P.num_parts() );  // A000000: compositions into distinct parts == 1 mod 3.
//
//            continue;
//        }

#if 1
        { // A217605: fixed points of a certain involution
            bool q = true;
            for (ulong k = 1; k<=n; ++k)
            {
                ulong ck = P.num_of(k);
                if ( ck && (P.num_of(ck) != k) )
                { q = false;  break; }
            }
            ct += q;
            if ( !q )  continue;
        }
#endif


#ifndef  TIMING
        cout << setw(4) << ct << ": ";

//        cout << " [" << P.num_parts() << "]  ";
//        cout << " [" << P.num_sorts() << "]  ";
//        cout << " [" << P.rank() << "]  ";
//        cout << " [" << P.num_of(1) << "]  ";

        cout << setw(4) << n;

        const bool szq = true;  // whether to skip zeros with long format
        cout << " == ";
        P.print_long(szq);

        if ( szq )  cout  << endl << "         ";
        cout << "  ==  ";
        if ( sq )  P.print_falling();
        else       P.print();

        cout << endl;

        jjassert( P.OK() );
#endif  // TIMING
    }
    while ( P.next() );


    cout << " ct=" << (long)ct << endl;

    delete [] Z;  // scratch space

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A217605-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A217605-demo.cc DEMOFLAGS=-DTIMING"
/// End:

