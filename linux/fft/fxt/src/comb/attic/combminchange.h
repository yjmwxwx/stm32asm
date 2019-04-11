#if !defined HAVE_COMBMINCHANGE_H__
#define      HAVE_COMBMINCHANGE_H__


#include "funcemu.h"
#include "bitcombination.h"  // first_comb()
#include "fxttypes.h"

#include "fxtio.h"


class comb_minchange
{
public:
    ulong n_;
    ulong k_;
    ulong bits_;
    ulong last_;
    ulong sw1_, sw2_;
    ulong *x_;
    funcemu<ulong> *fe_;

public:
    comb_minchange(ulong n, ulong k);
    ~comb_minchange();

    ulong first()
    {
        bits_ = first_comb(k_);
        sync_x();
        sw1_ = sw2_ = 0;
        return  bits_;
    }

    ulong next()  // return zero if previous comb was the last
    {
        if ( bits_ == last_ )  return 0;

        next_recursion();
        sync_x();
        return  bits_;
    }

    ulong next_recursion();  // aux

    const ulong * data()  const  { return x_; }

    friend ostream & operator << (ostream &os, const comb_minchange &x);

    void bit_swap_01(ulong n, ulong k)
    // Swap bits n-1 and k-1
    // Bits must have different values
    // (i.e. one is zero, the other one)
    // Index k-1==0 wraps around to n-2
    {
        if ( 1==k )  k = n;
        --k;
        sw1_ = n - 1;
        sw2_ = k - 1;
        bits_ ^= ( (1UL<<sw1_) | (1UL<<sw2_) );
    }

//private:
    void sync_x()
    {
        ulong tbits = bits_;
        ulong xi = 0, bi = 0;
        while ( bi < n_ )
        {
            if ( tbits & 1 )  x_[xi++] = bi;
            ++bi;
            tbits >>= 1;
        }
    }
};
// -------------------------



#endif  // !defined HAVE_COMBMINCHANGE_H__
