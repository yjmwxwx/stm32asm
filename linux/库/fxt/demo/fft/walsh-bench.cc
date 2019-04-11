
#include "walsh-all.h"

#include "nextarg.h"
#include "fxttypes.h"

//% benchmark for Walsh transform routines.

inline void fill1(double *f, ulong n)
{
    for (ulong k=0;  k<n;  k+=4)
    {
        f[k+0] = 1.0;
        f[k+1] = 1.0;
        f[k+2] = 1.0;
        f[k+3] = 1.0;
    }
}
// -------------------------


#define SAYFUNC() \
    cout << "routine = " << fn << "()" << endl;

#define  STR(s)  #s
#define DO(func) \
    fn =  STR(func); \
    SAYFUNC(); \
    for (ulong j=0; j<rep; ++j)  { fill1(f, n); func(f, ldn); } \
    break;


//inline void compl_walsh_wak_dif(double *f, ulong ldn)
//{ walsh_wak_dif((Complex*)f, ldn-1); }
//
//inline void compl_walsh_wak_dit(double *f, ulong ldn)
//{ walsh_wak_dit((Complex*)f, ldn-1); }
//
//
//inline void compl_walsh_wak_loc_dif2(double *f, ulong ldn)
//{ walsh_wak_loc_dif2((Complex*)f, ldn-1); }
//
//inline void compl_walsh_wak_loc_dit2(double *f, ulong ldn)
//{ walsh_wak_loc_dit2((Complex*)f, ldn-1); }


int
main(int argc, char **argv)
{
    ulong ldn = 5;
    NXARG(ldn, "Using 2**ldn elements (n>1)");
    const ulong n = 1UL<<ldn;
    ulong rep = 1;
    NXARG(rep, "Number of times the transform is made");
    ulong tt = 0;
    NXARG(tt, "type of transform, see code");

    double *f = new double[n];
    const char *fn = 0;

    switch ( tt )
    {
    case 0: DO( walsh_wak_loc_dif2 );
    case 1: DO( walsh_wak_loc_dit2 );
    case 2: DO( walsh_wak_dif2 );
    case 3: DO( walsh_wak_dit2 );
    case 4: DO( walsh_wak_dif4 );
    case 5: DO( walsh_wak_dit4 );
    case 6: DO( walsh_wak_dif8 );
    case 7: DO( walsh_wak_dit8 );
    default: ;
    }

    cout << "size=" << n << endl;
    cout << "memsize="
         << (n*sizeof(double)/1024) << " kB"
         << " =" << (n*sizeof(double)/1024/1024) << " MB"
         << endl;
    const double mb = (double)(1024 * 1024);
    const double xf = (double)ldn * (double)n * sizeof(double) * (double)rep;
    cout << "xfer=" << (xf/mb) << " MB" << endl;

    SAYFUNC();

    delete [] f;
    return 0;
}
// -------------------------

/*
Timing:

++++++++++ small size transforms ++++++++++
arg 1: 12 == ldn  [Using 2**ldn elements (n>1)]  default=5
arg 2: 65536 == rep  [Number of times the transform is made]  default=1
arg 3: 0 == tt  [type of transform, see code]  default=0
size=4096
memsize=32 kB =0 MB
xfer=24576 MB

routine = walsh_wak_loc_dif2()
./bin 12 65536 0  2.90s user 0.00s system 99% cpu 2.909 total

routine = walsh_wak_loc_dit2()
./bin 12 65536 1  2.98s user 0.00s system 99% cpu 3.001 total

routine = walsh_wak_dif2()
./bin 12 65536 2  4.99s user 0.01s system 99% cpu 5.019 total

routine = walsh_wak_dit2()
./bin 12 65536 3  5.18s user 0.02s system 99% cpu 5.221 total

routine = walsh_wak_dif4()
./bin 12 65536 4  2.90s user 0.00s system 98% cpu 2.943 total

routine = walsh_wak_dit4()
./bin 12 65536 5  3.14s user 0.00s system 99% cpu 3.146 total

routine = walsh_wak_dif8()
./bin 12 65536 6  2.82s user 0.00s system 99% cpu 2.828 total

routine = walsh_wak_dit8()
./bin 12 65536 7  2.86s user 0.01s system 100% cpu 2.867 total


++++++++++ medium size transforms ++++++++++
arg 1: 16 == ldn  [Using 2**ldn elements (n>1)]  default=5
arg 2: 1024 == rep  [Number of times the transform is made]  default=1
arg 3: 0 == tt  [type of transform, see code]  default=0
size=65536
memsize=512 kB =0 MB
xfer=8192 MB

routine = walsh_wak_loc_dif2()
./bin 16 1024 0  1.62s user 0.00s system 99% cpu 1.624 total

routine = walsh_wak_loc_dit2()
./bin 16 1024 1  1.76s user 0.01s system 100% cpu 1.766 total

routine = walsh_wak_dif2()
./bin 16 1024 2  3.61s user 0.02s system 99% cpu 3.630 total

routine = walsh_wak_dit2()
./bin 16 1024 3  3.84s user 0.01s system 99% cpu 3.847 total

routine = walsh_wak_dif4()
./bin 16 1024 4  4.11s user 0.01s system 99% cpu 4.118 total

routine = walsh_wak_dit4()
./bin 16 1024 5  3.83s user 0.01s system 99% cpu 3.844 total

routine = walsh_wak_dif8()
./bin 16 1024 6  2.52s user 0.00s system 99% cpu 2.525 total

routine = walsh_wak_dit8()
./bin 16 1024 7  2.70s user 0.01s system 100% cpu 2.708 total


++++++++++ large size transforms ++++++++++
arg 1: 24 == ldn  [Using 2**ldn elements (n>1)]  default=5
arg 2: 1 == rep  [Number of times the transform is made]  default=1
arg 3: 0 == tt  [type of transform, see code]  default=0
size=16777216
memsize=131072 kB =128 MB
xfer=3072 MB

routine = walsh_wak_loc_dif2()
./bin 24 1 0  1.18s user 0.10s system 99% cpu 1.285 total

routine = walsh_wak_loc_dit2()
./bin 24 1 1  1.22s user 0.10s system 98% cpu 1.339 total

routine = walsh_wak_dif2()
./bin 24 1 2  2.12s user 0.10s system 99% cpu 2.225 total

routine = walsh_wak_dit2()
./bin 24 1 3  2.10s user 0.11s system 99% cpu 2.217 total

routine = walsh_wak_dif4()
./bin 24 1 4  2.59s user 0.10s system 100% cpu 2.696 total

routine = walsh_wak_dit4()
./bin 24 1 5  2.58s user 0.12s system 99% cpu 2.702 total

routine = walsh_wak_dif8()
./bin 24 1 6  2.13s user 0.10s system 99% cpu 2.243 total

routine = walsh_wak_dit8()
./bin 24 1 7  2.32s user 0.11s system 99% cpu 2.427 total


BENCHARGS=24 1 0
BENCHARGS=24 1 1
BENCHARGS=24 1 2
BENCHARGS=24 1 3
BENCHARGS=24 1 4
BENCHARGS=24 1 5
BENCHARGS=24 1 6
BENCHARGS=24 1 7

BENCHARGS=16 1024 0
BENCHARGS=16 1024 1
BENCHARGS=16 1024 2
BENCHARGS=16 1024 3
BENCHARGS=16 1024 4
BENCHARGS=16 1024 5
BENCHARGS=16 1024 6
BENCHARGS=16 1024 7

BENCHARGS=12 65536 0
BENCHARGS=12 65536 1
BENCHARGS=12 65536 2
BENCHARGS=12 65536 3
BENCHARGS=12 65536 4
BENCHARGS=12 65536 5
BENCHARGS=12 65536 6
BENCHARGS=12 65536 7

*/


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/fft"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/fft/walsh-bench.cc"
/// make-target2: "1demo DSRC=demo/fft/walsh-bench.cc DEMOFLAGS=-DTIMING"
/// End:
