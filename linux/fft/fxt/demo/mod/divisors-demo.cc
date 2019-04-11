
#include "mod/divisors.h"

#include "fxttypes.h"
#include "nextarg.h"
#include "fxtio.h"

//% List all divisors of an integer



int
main(int argc, char **argv)
{
    umod_t n =  2*3*3*5*7;
//    umod_t n = 614889782588491410ULL;  // == 2*3*5*7*11*...*43*47
    NXARG(n, "Number whose divisors shall be listed");

    divisors D(n);

    cout << " primes    = [";
    for (ulong j=0; j<D.n_; ++j)  cout << setw(3) << D.p_[j] << " ";
    cout << " ]";
    cout << endl;
    cout << " exponents = [";
    for (ulong j=0; j<D.n_; ++j)  cout << setw(3) << D.mr_->m1_[j] << " ";
    cout << " ]";
    cout << endl;
    cout << endl;


    ulong d = D.first();
    ulong ct = 0;
    do
    {
        ++ct;

        cout << setw(3) << ct << ":  ";
        cout << setw(6) << d;

        cout << "   t=[";
        for (ulong j=0; j<=D.n_; ++j)  cout << setw(4) << D.t_[j];
        cout << " ]";

        cout << "   mr=[";
        for (ulong j=0; j<D.n_; ++j)  cout << setw(2) << D.mr_->a_[j];
        cout << " ]";

        cout << "   j = " << D.mr_->j_;

        cout << endl;
    }
    while ( ( d=D.next() ) );

    cout << " #= " << ct << endl;

    return 0;
}
// -------------------------



/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/mod"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/mod/divisors-demo.cc"
/// make-target2: "1demo DSRC=demo/mod/divisors-demo.cc DEMOFLAGS=-DTIMING"
/// End:
