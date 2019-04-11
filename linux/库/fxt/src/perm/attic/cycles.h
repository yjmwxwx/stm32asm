#if !defined HAVE_CYCLES_H__
#define      HAVE_CYCLES_H__


#include "ds/bitarray.h"
#include "fxttypes.h"


class cycles
// compute and analyze cycles of a permutation
{
public:
    ulong n_;   // # of allocated elements
    ulong *f_;  // [nontrivial cycles] nce_ [fixed points] nn_ [unused] n_
    ulong nn_;  // # of elements actually used == nce_ + nf_
    ulong nc_;  // # of cycles
    ulong nce_; // # of elements in nontrivial cycles
    ulong nf_;  // # of fixed points (fixed points recorded at the end of f_[])
    ulong ma_, mi_; // max/min length of cycles
    bitarray *ta_;  // tag array to mark cycle ends
    bitarray *tt_;  // aux: tag array for creating cycles

public:
    cycles(ulong n);
    cycles(const cycles &c);
    ~cycles();
    int make_cycles(const ulong *f, ulong n);

    int make_permutation(ulong *f, ulong n)  const;  // 'inverse' of make_cycles()

    void invert();

    ulong get(ulong k)  const { return  f_[k]; }  // no range check
    ulong get_cycle_minima(ulong *m)  const;
    ulong get_cycle_maxima(ulong *m)  const;


    ulong next_cycle(ulong &k)  const;
    ulong cycle_length(ulong k)  const // length of cycle starting at index k
    { return  ta_->next_set(k) - k + 1; }

    int test_equivalent(const ulong *f, ulong n)  const;
    bool is_equivalent(const ulong *f, ulong n)  const
    { return  ( 0==test_equivalent(f, n) ); }

    void print(int info_only=0)  const;
    void print_cycles(int info_only=0)  const;
    void print_cycles_short()  const;
    void print_fixed_points(int info_only=0)  const;
    void print_leaders()  const;

    void print_code(const char *funcname, ulong n,
                    int use_swap=0, int use_stderr=0)  const;
};
// -------------------------


#endif  // !defined HAVE_CYCLES_H__
