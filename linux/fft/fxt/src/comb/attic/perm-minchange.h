#if !defined HAVE_PERM_MINCHANGE_H__
#define      HAVE_PERM_MINCHANGE_H__

#include "comb/comb-print.h"
#include "fxttypes.h"


class perm_minchange
// Permutations in (Johnson/Trotter) minimal-change order.
// Biggest element moves most often.
{
public:
    ulong *p_;  // p[n] contains a permutation of {0, 1, ..., n-1}
    ulong *ip_; // ip[n] contains the inverse permutation of p[]
    ulong *d_;  // aux
    ulong *ii_; // aux
    ulong n_;   // number of elements to permute
    ulong sw1_, sw2_; // indices of elements swapped most recently

public:
    perm_minchange(ulong nn)
    {
        n_ = ( nn<1 ? 1 : nn );
        p_  = new ulong[n_];
        ip_ = new ulong[n_];
        d_  = new ulong[n_];
        ii_ = new ulong[n_];
        first();
    }

    ~perm_minchange()
    {
        delete [] p_;
        delete [] ip_;
        delete [] d_;
        delete [] ii_;
    }

    void first()
    {
        for (ulong i=0; i<n_; i++)
        {
            p_[i] = ip_[i] = i;
            d_[i] = -1UL;
            ii_[i] = 0;
        }
        sw1_ = sw2_ = 0;
    }

    ulong next()  { return make_next(n_-1); }  // return 0 if on last permutation
    const ulong * data()  const  { return p_; }
    const ulong * invdata()  const  { return ip_; }
    void get_swap(ulong &s1, ulong &s2)  const  { s1=sw1_; s2=sw2_; }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, data(), n_, dfz); }

    void print_inv(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_perm(bla, invdata(), n_, dfz); }

private:
    ulong make_next(ulong m)
    {
        ulong i = ii_[m];
        ulong ret = 1;

        if ( i==m )
        {
            d_[m] = -d_[m];
            if ( 0!=m )  ret = make_next(m-1);
            else         ret = 0;
            i = -1UL;
        }

        if ( (long)i>=0 )
        {
            // this block based on code by
            // Frank Ruskey / Glenn Rhoads:
            ulong j = ip_[m];
            ulong k = j + d_[m];
            ulong z = p_[k];
            p_[j] = z;
            p_[k] = m;
            ip_[z] = j;
            ip_[m] = k;

            sw1_ = j;  // note that sw1_ == sw2_ +-1 (adjacent positions)
            sw2_ = k;
        }

        ii_[m] = i + 1;

        return  ret;
    }
};
// -------------------------


#endif  // !defined HAVE_PERM_MINCHANGE_H__
