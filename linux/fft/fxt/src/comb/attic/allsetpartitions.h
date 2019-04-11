#if !defined  HAVE_ALLSETPARTITIONS_H__
#define       HAVE_ALLSETPARTITIONS_H__

#include "fxttypes.h"


class all_set_partitions
// Set partitions of the set {1,2,3,...,n}
// A table of _all_ partitions is created upon creation of an instance.
// By default in minimal change order
// Restriction on n (table has to fit in memory):
//   32 bit machines:  n<=15
//   64 bit machines:  n<=25
{
public:
    signed char *p_;  // Table of all set partitions
    // (each partition is a unterminated string of n signed chars)
    ulong n_;  // Number of elements in set; set = {1,2,3,...,n}
    ulong b_;  // Bell number B(n)
    ulong np_; // Number of chars in array p points to
    static ulong bell_table[]; // Bell numbers B(n)

public:
    all_set_partitions(ulong n, bool xdr=true, int dr0=+1)
    // n:  Create set partitions of {1,2,3,...,n}
    // xdr: change direction in recursion ==> minimal change order
    // dr0: starting direction in each recursive step:
    //   dr0=+1  ==> start with partition  {{1,2,3,...,n}}
    //   dr0=-1  ==> start with partition  {{1},{2},{3},...,{n}}}
    {
        n_ = n;
        b_ = bell_table[n_];
        np_ = n_ * b_;
        p_ = new signed char[np_];
        init(xdr, dr0);
    }

    ~all_set_partitions()  { delete [] p_; }

    void init(bool xdr, int dr0);  // build up the table

    ulong print(ulong k)  const
    // Print k-th set partition (0<=k<B(n)).
    // Return number of chars printed
    {
        if ( k >= b_ )  return 0;
        const signed char *x = p_ + k * n_;
        return print_p(x, n_);
    }

    bool get(ulong k, signed char *dst)  const
    // Copy set partition k to dst[0,...,n-1] (0<=k<B(n))
    {
        if ( k >= b_ )  return false;
        const signed char *x = p_ + k * n_;
        for (ulong j=0; j<n_; ++j)  dst[j] = x[j];
        return  true;
    }

public:
    static ulong print_p(const signed char *x, ulong n);


protected:
    static void cp_append(const signed char *src, signed char *dst, ulong k, ulong a);
};
// -------------------------


#endif  // !defined HAVE_ALLSETPARTITIONS_H__
