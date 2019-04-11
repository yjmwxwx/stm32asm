#if !defined HAVE_COMBINATION_ALTMINCHANGE_H__
#define      HAVE_COMBINATION_ALTMINCHANGE_H__


#include "bits/bitcombminchange.h"
#include "fxttypes.h"
#include "fxtio.h"


class combination_altminchange
// Combinations n choose k in (alternative) minimal-change order
// Note: the performance is bad
{
public:
    ulong n_;  // number of elements to choose from
    ulong k_;  // number of elements of subsets
    ulong nk_;  // n_ - k_
    ulong igc_bits_;
    ulong bits_;
    ulong igc_last_;
    ulong igc_first_;
    ulong sw1_, sw2_;
    ulong *x_;

public:
    combination_altminchange(ulong n, ulong k)
    {
        n_ = (n ? n : 1);  // not zero
        k_ = (k ? (k>n_ ? n_ : k) : 1);  // 0<k<n
        x_ = new ulong[k_];

        nk_ = n_ - k;
//        last_ =  (first_comb(nk_) >> 1) | (1UL<<(n_-1));
        igc_last_ =  igc_last_comb(nk_, n_);
        igc_first_ =  first_sequency(nk_);

        first();
    }

    ~combination_altminchange()
    {
        delete [] x_;
    }

    const ulong * data()  const  { return x_; }


    ulong first()
    {
        igc_bits_ = igc_first_;
        bits_ = gray_code( igc_last_ );  // to get sw1_, sw2_ right
        sync_x();
        return  bits_;
    }

    ulong last()
    {
        igc_bits_ = igc_last_;
        bits_ = gray_code( igc_first_ );  // to get sw1_, sw2_ right
        sync_x();
        return  bits_;
    }

    ulong next()  // return zero if current combination is the last
    {
        if ( igc_bits_ == igc_last_ )  return 0;

        ulong gy, y, i = 2;
        do
        {
            y = igc_bits_ + i;
            gy = gray_code( y );
            i <<= 1;
        }
        while ( bit_count( gy ) != nk_ );
        igc_bits_ = y;

        sync_x();
        return  bits_;
    }

    ulong prev()  // return zero if current combination is the first
    {
        if ( igc_bits_ == igc_first_ )  return 0;

        ulong gy, y, i = 2;
        do
        {
            y = igc_bits_ - i;
            gy = gray_code( y );
            i <<= 1;
        }
        while ( bit_count( gy ) != nk_ );
        igc_bits_ = y;

        sync_x();
        return  bits_;
    }

    void sync_x()  // aux
    // Sync bits into array and
    // set sw1_ and sw2_
    // Similar a in combination_minchange::sync_x but
    //   bits_ is negated and reversed
    {
        ulong tbits = gray_code( igc_bits_ );
        ulong sw = bits_ ^ tbits;

        bits_ = tbits;

        ulong n1 = n_ - 1;
        ulong xi = 0, bi = n1;
        tbits = ~tbits;
        while ( bi < n_ )
        {
            if ( (tbits>>bi) & 1 )  x_[xi++] = n1 - bi;
            --bi;
        }

        sw1_ = 0;
        while ( 0==(sw&1) )  { sw >>= 1;  ++sw1_; }
        sw2_ = sw1_;
        do  { sw >>= 1;  ++sw2_; }  while ( 0==(sw&1) );

        sw1_ = n1 - sw1_;
        sw2_ = n1 - sw2_;
    }
};
// -------------------------



#endif  // !defined HAVE_COMBINATION_ALTMINCHANGE_H__
