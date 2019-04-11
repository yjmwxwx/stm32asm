
#include "ds/heap.h"
#include "ds/priorityqueue.h"

#include "sort/sort.h"

#include "aux0/randf.h"  // rnd01()

#include "jjassert.h"

#include "fxtio.h"

#include "nextarg.h"  // NXARG()
#include "fxttypes.h"


//% Priority queue.


void
print(char ev, double tev, ulong k)
{
    cout << setw(2) << k << ": ";
    cout << setw(6) << ev;
    cout.flags(ios::left);
    cout << "  @      " << setw(12) << tev << endl;
    cout.flags(ios::right);
}
// -------------------------


// define to get different random numbers with each run:
//#define RSEED

int
main(int argc, char **argv)
{
#ifdef  RSEED
    cout << " rseed=" << rseed() << endl;
#endif

    ulong n = 10;
    NXARG(n, "Number of elements (0<n<=26)");

//    priority_queue<double, double> Q(n);
    priority_queue<double, char> Q(3, 2);  // check grow

    double *T = new double[n];
    char *E = new char[n];
    rnd01(T, n);
//    print("random values:", T, n);
    for (ulong k=0; k<n; ++k)  E[k] = (char)('A' + k);  // events names are A, B, C, ...

    cout << endl;
    cout << "Inserting into piority_queue:" << endl;
    cout << setw(2) << "# " << ": ";
    cout << " event" << "  @  " << setw(8) << "time" << endl;
    for (ulong k=0; k<n; ++k)
    {
        char ev = E[k];
        double tev = T[k];
        print(ev, tev, k);
        jjassert( Q.insert(T[k], E[k]) );
    }

    cout << endl;
    cout << "Extracting from piority_queue:" << endl;
    cout << setw(2) << "# " << ": ";
    cout << setw(6) << " event";
    cout << "  @  " << setw(8) << "time" << endl;
    ulong k = n;
    while ( k )
    {
        --k;

        char ev=' ';  double tev = 0;  // avoid warning 'may be used uninitialized'
        jjassert( Q.extract_next(tev, ev) );
        print(ev, tev, k);
        T[k] = tev;
        E[k] = ev;
    }
    jjassert( 0==Q.num() );

//    jjassert( is_sorted(T, n) );
    jjassert( is_sorted_desc(T, n) );

    delete [] T;
    delete [] E;

    return 0;
}
// -------------------------


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/ds"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/ds/priorityqueue-demo.cc"
/// make-target2: "1demo DSRC=demo/ds/priorityqueue-demo.cc DEMOFLAGS=-DTIMING"
/// End:

