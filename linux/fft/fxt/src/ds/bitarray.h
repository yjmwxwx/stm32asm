#if !defined HAVE_BITARRAY_H__
#define      HAVE_BITARRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitcount.h"
#include "bits/bitasm.h"
#include "bits/bitsperlong.h"
#include "fxttypes.h"

// suppress assembler instructions, for timing or testing purposes:
//#undef  BITS_USE_ASM


#ifndef  BITS_USE_ASM

#define  DIVMOD(n, d, bm) \
ulong d = n / BITS_PER_LONG; \
ulong bm = 1UL << (n % BITS_PER_LONG);

#define  DIVMOD_TEST(n, d, bm) \
ulong d = n / BITS_PER_LONG; \
ulong bm = 1UL << (n % BITS_PER_LONG); \
ulong t = bm & f_[d];

#endif  // ifndef  BITS_USE_ASM


#define CHECK  0  // define to disable check of out of bounds access
//#define CHECK  1  // define to handle out of bounds access
//#define CHECK  2  // define to fail with out of bounds access

#if ( CHECK == 2 )
#warning 'activating assertions in bitarray'
#include "jjassert.h"
#endif

class bitarray
// Bit-array class mostly for use as memory saving array of Boolean values.
// Valid index is 0...nb_-1 (as usual in C arrays).
{
public:
    ulong *f_;   // bit bucket
    ulong n_;    // number of bits
    ulong nfw_;  // number of words where all bits are used, may be zero
    ulong mp_;   // mask for partially used word if there is one, else zero
    // (ones are at the positions of the bits used)
    bool myfq_;  // whether f[] was allocated by class

    static bool use_asm_q()
    {
#ifdef  BITS_USE_ASM
        return true;
#else
        return false;
#endif  // BITS_USE_ASM
    }

private:  // have pointer data
    bitarray(const bitarray&);  // forbidden
    bitarray & operator = (const bitarray&);  // forbidden

private:
    ulong ctor_core(ulong nbits)
    {
        n_ = nbits;

        // nw: number of words (incl. partially used), nw>=1
        ulong nw = n_ / BITS_PER_LONG;       // number of words

        // nbl: number of bits used in last (partially used) word, 0 if mw==mfw
        ulong nbl = n_ - nw*BITS_PER_LONG;  // number of bits used in last word
        nfw_ = nw;  // number of fully used words

        mp_ = 0UL;
        if ( 0!=nbl )  // there is a partially used word
        {
            ++nw;  // increase total number of words
            // mask for last (partially used) word:
            mp_ = ~0UL;
            mp_ >>= (BITS_PER_LONG-nbl);
        }

        return nw;
    }

public:
    explicit bitarray(ulong nbits, ulong *f=0)
    // nbits must be nonzero
    {
        ulong nw = ctor_core(nbits);
        if ( f!=0 )
        {
            f_ = f;
            myfq_ = false;
        }
        else
        {
            f_ = new ulong[nw];
            myfq_ = true;
        }
    }

    ~bitarray()
    {
        if ( myfq_ ) delete [] f_;
    }

    ulong size()  const  { return n_; }

    ulong test(ulong n)  const
    // Test whether n-th bit set.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return 0;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        return asm_bt(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        return  t;
#endif  // BITS_USE_ASM
    }


    void set(ulong n)
    // Set n-th bit.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        asm_b_s(f_, n);
#else
        DIVMOD(n, d, bm);
        f_[d] |= bm;
#endif  // BITS_USE_ASM
    }


    void clear(ulong n)
    // Clear n-th bit.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        asm_b_r(f_, n);
#else
        DIVMOD(n, d, bm);
        f_[d] &= ~bm;
#endif  // BITS_USE_ASM
    }

    void change(ulong n)
    // Toggle n-th bit.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        asm_b_c(f_, n);
#else
        DIVMOD(n, d, bm);
        f_[d] ^= bm;
#endif  // BITS_USE_ASM
    }


    ulong test_set(ulong n)
    // Test whether n-th bit is set and set it.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return 0;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        return asm_bts(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        f_[d] |= bm;
        return  t;
#endif  // BITS_USE_ASM
    }


    ulong test_clear(ulong n)
    // Test whether n-th bit is set and clear it.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return 0;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        return asm_btr(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        f_[d] &= ~bm;
        return  t;
#endif
    }


    ulong test_change(ulong n)
    // Test whether n-th bit is set and toggle it.
    {
#if ( CHECK == 1 )
        if ( n>=n_ )  return 0;
#endif
#if ( CHECK == 2 )
        jjassert( n<n_ );
#endif

#ifdef  BITS_USE_ASM
        return asm_btc(f_, n);
#else
        DIVMOD_TEST(n, d, bm);
        f_[d] ^= bm;
        return  t;
#endif  // BITS_USE_ASM
    }


    void clear_all()
    // Clear all bits.
    {
        for (ulong k=0; k<nfw_; ++k)  f_[k] = 0;
        if ( mp_ )  f_[nfw_] = 0;
    }

    void set_all()
    // Set all bits.
    {
        for (ulong k=0; k<nfw_; ++k)  f_[k] = ~0UL;
        if ( mp_ )  f_[nfw_] = mp_;
    }


    bool all_set_q()  const
    // Return whether all bits are set.
    {
        for (ulong k=0; k<nfw_; ++k)  if ( ~f_[k] )  return false;
        if ( mp_ )
        {
            ulong z = f_[nfw_] & mp_;
            if ( z!=mp_ )  return false;
        }
        return true;
    }

    ulong all_clear_q()  const
    // Return whether all bits are clear.
    {
        for (ulong k=0; k<nfw_; ++k)  if ( f_[k] )  return false;
        if ( mp_ )
        {
            ulong z = f_[nfw_] & mp_;
            if ( z!=0 )  return false;
        }
        return true;
    }

    ulong next_set(ulong n)  const
    // Return index of next set bit or value beyond end.
    // Note: the given index n is included in the search
    {
        while ( (n<n_) && (!test(n)) )  ++n;
        return  n;
    }

    ulong next_clear(ulong n)  const
    // Return index of next clear bit or value beyond end.
    // Note: the given index n is included in the search
    {
        while ( (n<n_) && (test(n)) )  ++n;
        return  n;
    }

    // todo: next_set_sparse() / next_clear_sparse()

    ulong first_set()
    // Return index of first set bit or value beyond end.
    {
        ulong k = 0;
        while ( k<nfw_ )
        {
            if ( f_[k] ) break;
            ++k;
        }
        return  next_set( k * BITS_PER_LONG );
    }

    ulong first_clear()
    // Return index of first clear bit or value beyond end.
    {
        ulong k = 0;
        while ( k<nfw_ )
        {
            if ( ~f_[k] ) break;
            ++k;
        }
        return  next_clear( k * BITS_PER_LONG );
    }

    // todo: prev_set() / prev_clear()
    // todo: last_set() / last_clear()

    ulong count_ones()  const
    // Return the number of set bits.
    {
        ulong ct = 0;
#if 0
        for (ulong j=0; j<n_; ++j)  ct += (0!=test(j));
#else
        for (ulong j=0; j<nfw_; ++j)  ct += bit_count(f_[j]);
        if ( mp_ )  ct += bit_count( mp_ & f_[nfw_] );
#endif
        return ct;
    }

    ulong count_zeros()  const
    // Return the number of clear bits.
    { return  n_ - count_ones(); }

    void dump()  const;
    void dump_bits(ulong prettyq=0)  const;
};
// -------------------------

#undef  CHECK
#undef  DIVMOD
#undef  DIVMOD_TEST


#endif  // !defined HAVE_BITARRAY_H__
