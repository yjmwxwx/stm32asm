
#include "fht/fhtloc2.h"
#include "fht/fht.h"

#include "nextarg.h"
#include "fxttypes.h"

//% benchmark for FHT routines.

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


inline void compl_fht_dif_core(double *f, ulong ldn)
{ fht_dif_core((Complex*)f, ldn-1); }

inline void compl_fht_dit_core(double *f, ulong ldn)
{ fht_dit_core((Complex*)f, ldn-1); }


inline void compl_fht_loc_dif2_core(double *f, ulong ldn)
{ fht_loc_dif2_core((Complex*)f, ldn-1); }

inline void compl_fht_loc_dit2_core(double *f, ulong ldn)
{ fht_loc_dit2_core((Complex*)f, ldn-1); }


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
    case 0: DO( fht_loc_dif2_core );
    case 1: DO( fht_loc_dit2_core );
    case 2: DO( fht_dif_core );
    case 3: DO( fht_dit_core );
    case 4: DO( compl_fht_loc_dif2_core );
    case 5: DO( compl_fht_loc_dit2_core );
    case 6: DO( compl_fht_dif_core );
    case 7: DO( compl_fht_dit_core );
    default: ;
    }

    cout << "size=" << n << endl;
    cout << "memsize="
         << (n*sizeof(double)/1024) << " kB"
         << " =" << (n*sizeof(double)/1024/1024) << " MB"
         << endl;
    const double mb = (double)(1024 * 1024);
    const double xf = (double)ldn * (double)n * (double)sizeof(double) * (double)rep;
    cout << "xfer=" << (xf/mb) << " MB" << endl;

//    SAYFUNC();

    delete [] f;
    return 0;
}
// -------------------------

/*
Timing:

++++++++++ large size transforms ++++++++++
arg 1: 24 == ldn  [Using 2**ldn elements (n>1)]  default=5
arg 2: 1 == rep  [Number of times the transform is made]  default=1
arg 3: 0 == tt  [type of transform, see code]  default=0
size=16777216
memsize=131072 kB =128 MB
xfer=3072 MB
routine = fht_loc_dif2_core()
./bin 24 1 0  2.13s user 0.12s system 99% cpu 2.278 total

routine = fht_loc_dit2_core()
./bin 24 1 1  2.15s user 0.09s system 99% cpu 2.259 total

routine = fht_dif_core()
./bin 24 1 2  8.27s user 0.12s system 100% cpu 8.393 total

routine = fht_dit_core()
./bin 24 1 3  8.56s user 0.11s system 99% cpu 8.684 total

routine = compl_fht_loc_dif2_core()
./bin 24 1 4  1.90s user 0.12s system 99% cpu 2.025 total

routine = compl_fht_loc_dit2_core()
./bin 24 1 5  1.94s user 0.10s system 99% cpu 2.048 total

routine = compl_fht_dif_core()
./bin 24 1 6  4.55s user 0.10s system 100% cpu 4.648 total

routine = compl_fht_dit_core()
./bin 24 1 7  4.49s user 0.13s system 99% cpu 4.644 total


++++++++++ medium size transforms ++++++++++
arg 1: 16 == ldn  [Using 2**ldn elements (n>1)]  default=5
arg 2: 1024 == rep  [Number of times the transform is made]  default=1
arg 3: 0 == tt  [type of transform, see code]  default=0
size=65536
memsize=512 kB =0 MB
xfer=8192 MB

routine = fht_loc_dif2_core()
./bin 16 1024 0  3.66s user 0.01s system 99% cpu 3.687 total

routine = fht_loc_dit2_core()
./bin 16 1024 1  3.57s user 0.01s system 99% cpu 3.592 total

routine = fht_dif_core()
./bin 16 1024 2  6.68s user 0.02s system 99% cpu 6.751 total

routine = fht_dit_core()
./bin 16 1024 3  7.16s user 0.02s system 100% cpu 7.179 total

routine = compl_fht_loc_dif2_core()
./bin 16 1024 4  3.04s user 0.01s system 99% cpu 3.055 total

routine = compl_fht_loc_dit2_core()
./bin 16 1024 5  3.13s user 0.01s system 99% cpu 3.142 total

routine = compl_fht_dif_core()
./bin 16 1024 6  4.08s user 0.01s system 99% cpu 4.098 total

routine = compl_fht_dit_core()
./bin 16 1024 7  4.49s user 0.01s system 99% cpu 4.503 total


++++++++++ small size transforms ++++++++++
arg 1: 12 == ldn  [Using 2**ldn elements (n>1)]  default=5
arg 2: 65536 == rep  [Number of times the transform is made]  default=1
arg 3: 0 == tt  [type of transform, see code]  default=0
size=4096
memsize=32 kB =0 MB
xfer=24576 MB

routine = fht_loc_dif2_core()
./bin 12 65536 0  7.87s user 0.01s system 100% cpu 7.879 total

routine = fht_loc_dit2_core()
./bin 12 65536 1  8.04s user 0.02s system 99% cpu 8.053 total

routine = fht_dif_core()
./bin 12 65536 2  7.90s user 0.01s system 99% cpu 7.907 total

routine = fht_dit_core()
./bin 12 65536 3  8.04s user 0.02s system 100% cpu 8.055 total

routine = compl_fht_loc_dif2_core()
./bin 12 65536 4  5.29s user 0.01s system 99% cpu 5.297 total

routine = compl_fht_loc_dit2_core()
./bin 12 65536 5  5.39s user 0.00s system 99% cpu 5.400 total

routine = compl_fht_dif_core()
./bin 12 65536 6  5.29s user 0.01s system 100% cpu 5.299 total

routine = compl_fht_dit_core()
./bin 12 65536 7  5.40s user 0.01s system 99% cpu 5.434 total

*/

/*
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
/// make-target: "1demo DSRC=demo/fft/fht-bench.cc"
/// make-target2: "1demo DSRC=demo/fft/fht-bench.cc DEMOFLAGS=-DTIMING"
/// End:
