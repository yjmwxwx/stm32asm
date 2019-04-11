#if !defined HAVE_COMPOSITIONALT_H__
#define      HAVE_COMPOSITIONALT_H__


#include "fxttypes.h"
#include "bits/bitcombminchange.h"
#include "bits/bit2composition.h"


class composition_alt
{
public:
    ulong n_;  // number of elements to choose from
    ulong k_;  // number of elements of subsets
    ulong igc_bits_;
    ulong bits_;
    ulong igc_last_;
    ulong igc_first_;
    ulong *x_;

public:
    composition_alt(ulong k)
    {
        k_ = (k ? k : 1);  // not zero
        n_ = 2 * k_ - 1;  // not zero
        x_ = new ulong[k_];

        igc_last_ =  igc_last_comb(k_, n_);
        igc_first_ =  first_sequency(k_);

        first();
    }

    ~composition_alt() { delete [] x_; }

    const ulong * data()  const  { return x_; }


    ulong first()
    {
        igc_bits_ = igc_first_;
        bits_ = gray_code( igc_bits_ );
        sync_x();
        return  bits_;
    }

    ulong last()
    {
        igc_bits_ = igc_last_;
        bits_ = gray_code( igc_bits_ );
        sync_x();
        return  bits_;
    }

    ulong next()  // return zero if current comb is the last
    {
        if ( igc_bits_ == igc_last_ )  return 0;

        ulong gy, y, i = 2;
        do
        {
            y = igc_bits_ + i;
            gy = gray_code( y );
            i <<= 1;
        }
        while ( bit_count( gy ) != k_ );
        igc_bits_ = y;
        bits_ = gy;

        sync_x();
        return  bits_;
    }

    ulong prev()  // return zero if current comb is the first
    {
        if ( igc_bits_ == igc_first_ )  return 0;

        ulong gy, y, i = 2;
        do
        {
            y = igc_bits_ - i;
            gy = gray_code( y );
            i <<= 1;
        }
        while ( bit_count( gy ) != k_ );
        igc_bits_ = y;
        bits_ = gy;

        sync_x();
        return  bits_;
    }

    void sync_x()  // aux
    // Sync bits into array
    {
        bit2composition(bits_, x_, k_);
    }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITIONALT_H__
