
#include "comb/allsetpartitions.h"

//#include "jjassert.h"
#include "fxtio.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"


ulong all_set_partitions::bell_table[] = { // Bell numbers
 1UL, // 0
 1UL, // 1
 2UL, // 2
 5UL, // 3
 15UL, // 4
 52UL, // 5
 203UL, // 6
 877UL, // 7
 4140UL, // 8
 21147UL, // 9
 115975UL, // 10
 678570UL, // 11
 4213597UL, // 12
 27644437UL, // 13
 190899322UL, // 14
 1382958545UL, // 15
#if  ( BITS_PER_LONG>32 )
 10480142147UL, // 16
 82864869804UL, // 17
 682076806159UL, // 18
 5832742205057UL, // 19
 51724158235372UL, // 20
 474869816156751UL, // 21
 4506715738447323UL, // 22
 44152005855084346UL, // 23
 445958869294805289UL, // 24
 4638590332229999353UL, // 25
#endif  //  ( BITS_PER_LONG>32 )
// 49631246523618756274UL, // 26
// 545717047936059989389UL, // 27
// 6160539404599934652455UL, // 28
// 71339801938860275191172UL, // 29
// 846749014511809332450147UL, // 30
// 10293358946226376485095653UL, // 31
// 128064670049908713818925644UL, // 32
};
// -------------------------


//#define SHOW_RECURSION  // whether to show how the "build process"

void
all_set_partitions::init(bool xdr, int dr0)
{
    p_[0] = -1;  // == { {1} }
    ulong b = 1;  // == bell_table[1]
    for (ulong k=2; k<=n_; ++k)
    {
        bool dr = (dr0 > 0 ? true : false );
        ulong b1 = b;
        b = bell_table[k];
        ulong nb1 = b1 * (k-1);
        signed char *p1 = p_ + np_ - nb1;
#ifdef SHOW_RECURSION
        cout << " ------------------ " << endl;
//        cout << " nb1=" <<  nb1 << endl;
#endif
        for (ulong j=0; j<nb1; ++j)  p1[j] = p_[j];

        signed char *p = p_;
        for (ulong j=0; j<b1; ++j)  // for all all_set_partitions(k-1)
        {
            ulong nc = 0;  // number of sets in partititon
            for (ulong i=0; i<k-1; ++i)  if ( p1[i]<0 )  ++nc;
#ifdef SHOW_RECURSION
            cout << "p1=";  print_p(p1, k-1); cout << endl;
#endif
            if ( dr )
            {
                for (ulong a=0; a<nc+1; ++a)
                {
                    cp_append(p1, p, k, a);
#ifdef SHOW_RECURSION
                    cout << "      -->  p=";  print_p(p, k); cout << endl;
#endif
                    p += k;
                }
            }
            else
            {
                for (long a=nc; a>=0; --a)
                {
                    cp_append(p1, p, k, a);
#ifdef SHOW_RECURSION
                    cout << "      -->  p=";  print_p(p, k); cout << endl;
#endif
                    p += k;
                }
            }

            p1 += (k-1);
            if ( xdr )  dr = !dr;
        }
    }
}
// -------------------------


void // static
all_set_partitions::cp_append(const signed char *src, signed char *dst, ulong k, ulong a)
// Used by init:
// copy partition in src[0,...,k-2] to dst[0,...,k-1]
// append element k at subset a (a>=0)
{
    //        cout << " %% ";  print_p(src, k-1);
    ulong ct = 0;
    signed char en = -(signed char)k;
    for (ulong j=0; j<k-1; ++j)
    {
        int e = src[j];
        //            cout << "  e=" << (int)e;
        //            jjassert( 0!=e );
        if ( e > 0 )  dst[j] = e;
        else
        {
            if ( a==ct )  { dst[j]=-e; ++dst; dst[j]=en; }
            else  dst[j] = e;
            ++ct;
        }
    }
    if ( a>=ct )  dst[k-1] = en;
}
// -------------------------


ulong // static
all_set_partitions::print_p(const signed char *x, ulong n)
{
//    cout << "[";
//    for (ulong j=0; j<n; ++j)  cout << (int)x[j] << ", ";
//    cout << "]  ";

    ulong nch = 1;  // number of chars printed
    cout << "{";
    for (ulong j=0; j<n; ++j)
    {
        int e = x[j];
        if ( e>0 ) { cout << e << ", ";  nch += 3; }
        else
        {
            e = -e;
            cout << e << "}";  nch += 2;
            if ( j+1<n )  { cout << ", {";  nch +=3; }
        }
    }
    if ( n>9 )  nch += (n-9);
    return nch;
}
// -------------------------
