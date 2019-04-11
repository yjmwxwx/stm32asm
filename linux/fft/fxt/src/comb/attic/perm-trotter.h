#if !defined HAVE_PERM_TROTTER_H__
#define      HAVE_PERM_TROTTER_H__

#include "aux0/swap.h"
#include "comb/comb-print.h"
#include "fxttypes.h"

class perm_trotter
// Gray code for permutations
// Trotter/Johnson algorithm.
{
public:
    ulong n_;   // number of elements to permute
    ulong *x_;  // current permutation (of {0, 1, ..., n-1})
    ulong *d_;  // auxiliary: directions
    ulong *p_;  // auxiliary: mixed radix counting
    ulong sw1_, sw2_; // indices of elements swapped most recently

public:
    perm_trotter(ulong nn) // nn>=2
    {
        n_ = ( nn<2 ? 2 : nn );  // 1: trivial & segfault in next()
        p_ = new ulong[n_];
        d_ = new ulong[n_];
        x_ = new ulong[n_];
        first();
    }

    ~perm_trotter()
    {
        delete [] p_;
        delete [] d_;
        delete [] x_;
    }

    void first()
    {
        for (ulong i=0; i<n_; i++)  p_[i] = 0;
        for (ulong i=0; i<n_; i++)  d_[i] = 1;
        for (ulong i=0; i<n_; i++)  x_[i] = i;
        sw1_ = n_ - 1;
        sw2_ = n_ - 2;
    }

    bool next()
    // Trotter's algorithm.
    // Based on code by Helmut Herold.
    {
        ulong k = 0;
        ulong m = 0;
        ulong y = p_[m] + d_[m];
        p_[m] = y;

        while ( (y==n_-m) || (y==0) )
        {
            if ( y==0 )
            {
                d_[m] = 1;
                ++k;
            }
            else  d_[m] = -1UL;

            if ( m==n_-2 )
            {
                sw1_ = n_ - 1;
                sw2_ = sw1_ - 1;
                swap2(x_[sw1_], x_[sw2_]);

                // y = 1;
                return false;
            }
            else
            {
                ++m;
                y = p_[m] + d_[m];
                p_[m] = y;
            }
        }

        sw1_ = y + k;
        sw2_ = sw1_ - 1;  // note: adjacent positions
        swap2(x_[sw1_], x_[sw2_]);
        return true;
    }

    const ulong * data()  const  { return x_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_PERM_TROTTER_H__
