
#include "comb/ruler-func.h"

//#include "comb/comb-print.h"

#include "fxtio.h"

#include "jjassert.h"

#include "fxttypes.h"
#include "nextarg.h"

//% A276691:  Sum of maximum subrange sum over all length-n arrays of {+1, -1}.

// Cf. comb/ruler-func-demo.cc

//#define TIMING  // uncomment to disable printing

template <typename Type>
inline Type max_subrange_val(Type * const x, ulong n)
// From: Jon Bentley, Programming pearls, Addison-Wesley, 1984, p. 74
{
    Type msf = 0;  // MaxSoFar
    Type meh = 0;  // MaxEndingHere
    for (ulong j=0; j<n; ++j)
    {
        Type t = meh + x[j];
        meh = ( t > 0 ? t : 0 );
        msf = ( msf > meh ? msf : meh );
    }
    return msf;
}
// -------------------------

inline void print_sgn_vec(const char *bla, const long *x, ulong n)
// Print x[0,..,n-1] as vector, n is the number of elements in the set.
{
    if ( bla )  cout << bla;

    cout << "[ ";
    for (ulong k=0; k<n; ++k)
    {
        long t = x[k];
        cout << ( t > 0 ? '+' : '-' );
        if ( k<n-1 )  cout << " ";
    }
    cout << " ]";
}
// -------------------------

int
main(int argc, char **argv)
{
    ulong n = 5;
    NXARG(n, "Words of n letters");

    ruler_func R(n);

    ulong ct = 0;

    long * const x = new long[n];
    for (ulong j=0; j<n; ++j)  x[j] = +1;
    x[0] = -1L;

    ulong j = 0;
    do
    {
        x[j] = -x[j];
        ulong s = max_subrange_val(x, n);
        ct += s;

#ifndef TIMING
        print_sgn_vec("", x, n);
//        cout << "  j = " << j;
        cout << "  s = " << s;
        cout << endl;
#endif  // TIMING

        j = R.next();
    }
    while ( j != n );

    cout << " ct=" << ct << endl;  // A276691

    delete [] x;

    return 0;
}
// -------------------------

/*
A272604:
echo  $(./bin 8 | sort | cut -d= -f2 | tac)
*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/seq"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/seq/A276691-demo.cc"
/// make-target2: "1demo DSRC=demo/seq/A276691-demo.cc DEMOFLAGS=-DTIMING"
/// End:
