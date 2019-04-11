#if !defined  HAVE_LYNDON_GRAY_H__
#define       HAVE_LYNDON_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014, 2016 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/bitarray.h"

#include "comb/num-necklaces.h"

#include "bits/bitcyclic-minmax.h"
#include "bits/bitcyclic-match.h"
#include "bits/bitcount.h"
#include "bits/graycode.h"
#include "bits/bitlex.h"
#include "bits/bitrotate.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"  // ulong
//#include "jjassert.h"


#define ALT_ALGORITM  // define to use half sized bitarray
// (faster for n>=29)

#ifdef ALT_ALGORITM
#define ALTALT  // define to use 1/4 sized bitarray
// (slight slowdown)
#endif


class lyndon_gray
// Gray code for n-bit Lyndon words (for prime n), else (n odd composite)
//   Gray code for necklaces (except all-ones and all-zeros word).
// Must have: n odd, n<BITS_PER_LONG
// Needs (2^n-2)/4 bits = (2^n-2)/32 bytes of memory.
{
public:
    ulong n_, n2_;  // n-bit Lyndon words, n2=2**n
    bitarray *pba_;  // tags for used words
    ulong uu_[BITS_PER_LONG];  // scratch space for sorting neighbors
    ulong p_;  // position
    int (*cmp)(const ulong &, const ulong &);
    ulong maxlyn_;  // maximal n-bit lyndon word
    ulong nlyn_;  // number of n-bit Lyndon words for prime n, else
    // number of necklaces - 2 (all necklaces except all-ones and all-zeros word)

    // The following are updated only if make_rot()
    // is called after each call of next():
    ulong pr_;  // position (rotated)
    ulong d_;   // bit-wise difference to last pr_ (a word with one bit)
    ulong r_;   // rotation (pr == bit_rotate_left(p, r))

private:  // have pointer data
    lyndon_gray(const lyndon_gray&);  // forbidden
    lyndon_gray & operator = (const lyndon_gray&);  // forbidden

public:
    explicit lyndon_gray(ulong n, ulong ncmp=0)
        : n_(n), n2_(1UL<<n)
    {
#ifdef ALT_ALGORITM
#ifdef ALTALT
        pba_ = new bitarray(n2_/4);
#else
        pba_ = new bitarray(n2_/2);
#endif  // ALTALT
#else
        pba_ = new bitarray(n2_);
#endif  // ALT_ALGORITM
        maxlyn_ = (n2_-1) >> 1;

//        nlyn_ = num_lyndon_tab[n];
        nlyn_ = num_necklaces_tab[n] - 2;

        init(ncmp);
    }

    ~lyndon_gray()
    {
        delete pba_;
    }

    void init(ulong ncmp=0)
    {
        pba_->clear_all();
#ifdef ALT_ALGORITM
        // full word treated separately in neighbors()
#else
        pba_->set(n2_-1);  // exclude full word (not a Lyndon word)
#endif
        pba_->set(0);  // exclude zero (not a Lyndon word)
        p_ = 1;
        pr_ = 0;  // initialize to get a meaningful delta for first word
        make_rot();
        switch ( ncmp )
        {
        case 0:  cmp = cmp_g03;  break;
        case 1:  cmp = cmp_g05;  break;
        case 2:  cmp = cmp_g21;  break;
        case 3:  cmp = cmp_g29;  break;
        case 4:  cmp = cmp_igc;  break;
        default:  cmp = cmp_test;  break;
        }
    }

    void mark(ulong ly)
    {
#ifdef ALT_ALGORITM
#ifdef ALTALT
        pba_->set(ly>>1);
#else
        pba_->set(ly);
#endif  // ALTALT
#else
        for (ulong k=0; k<n_; ++k)
        {
            pba_->set(ly);
            ly = bit_rotate_right(ly, 1, n_);
        }
#endif  // ALT_ALGORITM
    }

    inline ulong test(ulong v)
    {
#ifdef ALTALT
        v >>= 1;
#endif
        return ( pba_->test(v) );
    }

    ulong neighbors(ulong p)
    {
        ulong mct = 0;
        ulong b = 1UL<<(n_-1);
#ifdef ALT_ALGORITM
        // avoid testing all-ones word with reduced bitarray size:
        if ( p == maxlyn_ )  b >>= 1;
#endif  // ALT_ALGORITM
        for (  ; 0!=b;  b>>=1)  // for all neighbors
        {
            ulong vc = p ^ b;  // change one bit
#ifdef ALT_ALGORITM
            ulong vm = bit_cyclic_min(vc, n_);
            if ( test(vm) )  continue;
#else
            if ( test(vc) )  continue;
            ulong vm = bit_cyclic_min(vc, n_);
#endif  // ALT_ALGORITM
            uu_[mct++] = vm;
        }
        return mct;
    }

    // Various powers of the Gray code that lead to algorithms for 3<=n<=31:
#define X(n) x^=x>>n
    static inline ulong g03(ulong x) { X(1); X(2); return x; }
    static inline ulong g05(ulong x) { X(1); X(4); return x; }
    static inline ulong g21(ulong x) { X(1); X(4); X(16); return x; }
    static inline ulong g29(ulong x) { X(1); X(4); X(8); X(16); return x; }
#undef X

    // cmp_*() is used to determine which node to visit next
    static int cmp_g03(const ulong &a, const ulong &b)  // ncmp==0
    {  // fails for n = 37
        if ( a==b )  return 0;
#define CODE(x) g03(x)
        ulong ta = CODE(a), tb = CODE(b);
        return  ( ta < tb ? +1 : -1 );  // note the '<'
#undef CODE
    }

    static int cmp_g05(const ulong &a, const ulong &b)  // ncmp==1
    {  // all n OK
        if ( a==b )  return 0;
#define CODE(x) g05(x)
        ulong ta = CODE(a), tb = CODE(b);
        return  ( ta < tb ? +1 : -1 );  // note the '<'
#undef CODE
    }

    static int cmp_g21(const ulong &a, const ulong &b)  // ncmp==2
    {  // all n OK
        if ( a==b )  return 0;
#define CODE(x) g21(x)
        ulong ta = CODE(a), tb = CODE(b);
        return  ( ta < tb ? +1 : -1 );  // note the '<'
#undef CODE
    }

    static int cmp_g29(const ulong &a, const ulong &b)  // ncmp==3
    {  // fails for n = 21, 27, 33
        if ( a==b )  return 0;
#define CODE(x) g29(x)
        ulong ta = CODE(a), tb = CODE(b);
        return  ( ta < tb ? +1 : -1 );  // note the '<'
#undef CODE
    }

    static int cmp_igc(const ulong &a, const ulong &b)  // ncmp==4
    {  // fails for n = 21, 27, 29, 31
        if ( a==b )  return 0;
#define CODE(x) inverse_gray_code(x)
        ulong ta = CODE(a), tb = CODE(b);
        return  ( ta < tb ? +1 : -1 );  // note the '<'
#undef CODE
    }

    // For lyndon-gray-demo.cc:
    // for n in $(seq 3 2 27); do ./bin $n 0 5 | grep -F '#='; done
    // ./bin 21 0 5 27
    static int cmp_test(const ulong &a, const ulong &b)  // ncmp==5 (playground)
    {  //
        if ( a==b )  return 0;
#define CODE(x) lexrev2negidx(x)
//#define CODE(x) negidx2lexrev(x)
        ulong ta = CODE(a), tb = CODE(b);
        return  ( ta < tb ? +1 : -1 );  // note the '<'
#undef CODE
    }

    inline ulong choose_min(ulong u)
    // choose the minimum (wrt. cmp()) among neighbors found
    {
        ulong v = uu_[0];
        while ( u-- )  if ( cmp(uu_[u], v) < 0 )  v = uu_[u];
        return v;
    }

    ulong next()
    // Return next word in sequence, zero at end.
    {
        mark(p_);
        ulong u = neighbors(p_);
        if ( 0==u )  return 0;
        p_ = choose_min(u);
        return  p_;
    }

    ulong make_rot()
    // update r, pr, d
    {
        r_ = bit_cyclic_dist1_match(p_, pr_, n_);
//        jjassert( r_<=BITS_PER_LONG );
        ulong pr = bit_rotate_left(p_, r_, n_);
        d_ = pr ^ pr_;
        pr_ = pr;
        return   pr_;
    }

    bool is_cycle()  const
    {
        return ( 2==bit_count(p_));
    }
};
// -------------------------

#undef ALT_ALGORITM


#endif  // !defined HAVE_LYNDON_GRAY_H__
