#if !defined  HAVE_COMPOSITION_CHASE_H__
#define       HAVE_COMPOSITION_CHASE_H__


#include "comb/combination-chase.h"
#include "fxttypes.h"


class composition_chase
// k-compositions of n in a minimal-change order.
// Generated using near-perfect (N choose K) combinations
// where N=n+k-1 and K=n.
// Note: work per composition proportional to N ==> rather SLOW
{
public:
    combination_chase *cnp_;
    ulong *p_; // data: composition
    ulong n_, k_;  // k-composition of n
    ulong N_, K_;  // N=n+k-1 choose K=n

public:
    composition_chase(ulong n, ulong k)
    {
        n_ = n;  k_ = k;  // k-compositions of n
        N_ = n+k-1;  K_ = n;  // (N choose K) combinations
        cnp_ = new combination_chase(N_, K_);
        p_ = new ulong[k_];
        comb2comp();
    }

    ~composition_chase()
    {
        delete cnp_;
        delete [] p_;
    }

    bool next()
    {
        if ( false==cnp_->next() )  return false;
        comb2comp();
        return true;
    }

    void comb2comp()
    // convert delta set of combination to composition
    // NOTE: performance bottleneck
    {
        const ulong *x = cnp_->data();
        ulong w = 0;
        for (ulong j=0, z=0; j<N_; ++j)
        {
            if ( x[j] ) ++w;
            else { p_[z++] = w;  w=0; }
        }
        p_[k_-1] = w;
    }

    const ulong * data()  const  { return p_; }
    const ulong * combination_data()  const  { return cnp_->data(); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_CHASE_H__
