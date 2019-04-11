#if !defined HAVE_COMBINATION_MINCHANGE_H__
#define      HAVE_COMBINATION_MINCHANGE_H__


#include "bits/bitcombminchange.h"
#include "fxttypes.h"


class combination_minchange
// Minimum-change combinations
// based on the mechanism from bitcombminchange.h
// Note: the performance is bad,
//   prefer class combination_revdoor (it is much faster).
{
public:
    ulong n_;  // number of elements to choose from
    ulong k_;  // number of elements of subsets
    ulong igc_bits_;
    ulong bits_;
    ulong igc_last_;
    ulong igc_first_;
    ulong sw1_, sw2_;
    ulong *x_;

public:
    combination_minchange(ulong n, ulong k)
    {
        n_ = (n ? n : 1);  // not zero
        k_ = (k ? k : 1);  // not zero
        x_ = new ulong[k_];

        igc_last_ =  igc_last_comb(k_, n_);
        igc_first_ =  first_sequency(k_);

        first();
    }

    ~combination_minchange()  { delete [] x_; }

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
        while ( bit_count( gy ) != k_ );
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
        while ( bit_count( gy ) != k_ );
        igc_bits_ = y;

        sync_x();
        return  bits_;
    }

    void sync_x()  // aux
    // Sync bits into array and
    // set sw1_ and sw2_
    // Note: performance bottleneck
    {
        ulong tbits = gray_code( igc_bits_ );
        ulong sw = bits_ ^ tbits;

        bits_ = tbits;

        ulong xi = 0, bi = 0;
        while ( bi < n_ )
        {
            if ( tbits & 1 )  x_[xi++] = bi;
            ++bi;
            tbits >>= 1;
        }

        sw1_ = 0;
        while ( 0==(sw&1) )  { sw >>= 1;  ++sw1_; }
        sw2_ = sw1_;
        do  { sw >>= 1;  ++sw2_; }  while ( 0==(sw&1) );
    }
};
// -------------------------



#endif  // !defined HAVE_COMBINATION_MINCHANGE_H__
