#if !defined  HAVE_ALL_COMPOSITIONS_MINCHANGE_H__
#define       HAVE_ALL_COMPOSITIONS_MINCHANGE_H__

#include "comb/composition-colex.h"
#include "aux0/binomial.h"
#include "fxttypes.h"


class all_compositions_minchange
// All k-compositions of n in minimal-change order
// Note that a table of size (k * binomial(n+k-1, n)) is allocated
//   upon creation of an instance.
{
public:
    composition_colex cl_;
    ulong &n_, &k_;
    uchar *xx_;   //
    ulong b_;   //
    mutable uchar *x_;   //

public:
    all_compositions_minchange(ulong n, ulong k)
        : cl_(n,k), n_(cl_.n_), k_(cl_.k_)
    {
        b_ = binomial(n_ + k_ - 1,  n_);
        xx_ = new uchar[k_ * b_];
        init();
    }

    ~all_compositions_minchange()  { delete [] xx_; }


    uchar *get(ulong z)  const
    {
        if ( z>=b_ )  return 0;
        x_ = xx_ + z * k_;
        return  x_;
    }

    void print(ulong z)  const
    {
        if ( get(z) )  print();
    }


protected:
    void swap(ulong i1, ulong i2, ulong k);
    void gray(ulong k);
//    void gray_rev(ulong k);
//    void rev(ulong i1, ulong i2, ulong k);
    void init();
    void print()  const;
};
// -------------------------


#endif  // !defined HAVE_ALL_COMPOSITIONS_MINCHANGE_H__
