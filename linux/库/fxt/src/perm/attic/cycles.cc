
#include "perm/cycles.h"
#include "ds/bitarray.h"
#include "aux1/shift.h"
#include "sort/minmax.h"
#include "perm/reverse.h"
#include "fxttypes.h"


//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#warning  'PARANOIA tests enabled in cycles.cc'
#include "jjassert.h"
#endif // PARANOIA


#include "fxtio.h"


cycles::cycles(ulong n)
    : n_(n), f_(0),
      nn_(n),
      nc_(0), nce_(),
      nf_(0),
      ma_(0), mi_(0)
{
    f_ = new ulong[n_];
    ta_ = new bitarray(n);
    tt_ = new bitarray(n);
}
// -------------------------


cycles::~cycles()
{
    delete tt_;
    delete ta_;
    delete [] f_;
}
// -------------------------


int
cycles::make_cycles(const ulong *f, ulong n)
{
#ifdef PARANOIA
    jjassert( n<=n_ );
#endif // PARANOIA

    tt_->clear_all();

    ta_->clear_all();

    nc_ = 0;  // # of cycles
    nce_ = 0; // # of elements in nontrivial cycles
    nf_ = 0;  // # of fixed points
    ma_ = 1;  // max length of cycles
    mi_ = n;  // min length of cycles
    ulong k;  // index in f[]
    ulong j = 0;  // index in f_[]
    for (k=0; k<n; ++k)
    {
        if ( tt_->test_set(k) )  continue; // already processed

        ulong i = f[k];  // next in cycle

        if ( i==k )  // skip fixed points
        {
            ++nf_;
            f_[n_-nf_] = k;  // record fixed point backwards from end
            continue;
        }

        ulong cl = 0; // length of current cycle
        ++nc_;
        f_[j++] = k;
        ++nce_;
        ++cl;
        tt_->set(i); // cannot be already set, because minlen==2
        do
        {
            f_[j++] = i;
            ++nce_;
            ++cl;
            i = f[i];
        }
        while ( !tt_->test_set(i) ); // until we meet cycle leader again

        ta_->set(j-1); // tagged as last

        if ( ma_<cl )  ma_ = cl;
        if ( mi_>cl )  mi_ = cl;

#ifdef PARANOIA
        jjassert( i==k ); // fail if not a valid permutation
#endif // PARANOIA
    }

    nn_ =  nce_ + nf_;
#ifdef PARANOIA
    jjassert( nn_ <= n_ );
#endif // PARANOIA

    // want fixed points in order of appearence:
    if ( nf_ > 1 )  reverse(f_+n_-nf_, nf_);

    // want fixed points after cycles:
    if ( nf_ > 0 )
    {
        shift_left(f_+nce_, n_-nce_, n_-nce_-nf_);
    }

#ifdef PARANOIA
    jjassert( n==nn_ );
#endif // PARANOIA
    return  nn_;
}
// -------------------------

void
cycles::invert()
{
    // we could just reverse() the cycles part:
    // reverse(f_, nce_);
    // but then the tags must be moved as well,
    // so we invert the cycles one by one.

    ulong k=0, len=0;
    while ( (len=next_cycle(k)) )
    {
        if ( len>2 )  reverse(f_+k, len);
        k += len-1;
    }
}
// -------------------------

ulong
cycles::next_cycle(ulong &k)  const
// Set k to the index of the leader of the next cycle.
// Return the length of the cycle.
// Zero is returned if there is no more cycle.
//
// Assumes that input index k points to the last (i.e. tagged)
// element of a cycle or one higher (i.e. leader of next cycle).
//
// Usage:  (cf. print_leaders())
//   ulong k=0, len=0;
//   while ( (len=cc.next_cycle(k)) )
//   {
//       ulong v = cc.get(k);
//       // k==index  v=value
//       k += len-1;
//       ++ct;
//   }
//
{
    if ( k>=nce_ )  return 0;

    if ( ta_->test(k) )  ++k;  // advance if at cycle end
//    else  k = ta_->next_set(k) + 1;

    if ( k>=nce_ )  return 0;

    ulong len = ta_->next_set(k) - k + 1;

#ifdef PARANOIA
    jjassert( k+len <= nce_ );
#endif // PARANOIA

    return  len;
}
// -------------------------


int
cycles::make_permutation(ulong *f, ulong n)  const
// 'inverse' of make_cycles().
{
#ifdef PARANOIA
    jjassert( n>=n_ );
#endif // PARANOIA
    n = n_; // avoid "unused" warning

    // ---- fixed points:
    for (ulong k = nce_; k<nn_; ++k)
    {
        ulong x = f_[k];
        f[x] = x;
    }

    // ---- cycles:
    if ( 0==nc_ )  return 1;  // nothing to do

    ulong i = 0;
    ulong clen = cycle_length(0);
    do
    {
        ulong si = f_[i];  // cycle leader
        ulong di = f_[i+clen-1];  // last elem
        f[di] = si;

        for (ulong k=0; k<clen-1; ++k)
        {
            di = f_[i+k];
            si = f_[i+k+1];
            f[di] = si;
        }

        i += clen;
        clen = next_cycle(i);
    }
    while ( 0!=clen );

    return 1;
}
// -------------------------


int
cycles::test_equivalent(const ulong *f, ulong n)  const
// Test whether *this describes the permutation in f[].
// Return zero if it does.
{
    if ( n!=n_ )  return 1;

    // ---- check fixed points:
    for (ulong k = nce_; k<nn_; ++k)
    {
        ulong x = f_[k];
        if ( f[x]!=x )  return 1;
    }


    // ---- check cycles:
    if ( 0==nc_ )  return 0;  // nothing to do

    ulong i = 0;
    ulong clen = cycle_length(0);
    do
    {
        ulong si = f_[i];  // cycle leader
        ulong di = f_[i+clen-1];  // last elem
        if ( f[di] != si )  return 2;

        for (ulong k=0; k<clen-1; ++k)
        {
            di = f_[i+k];
            si = f_[i+k+1];
            if ( f[di] != si )  return 3;
        }

        i += clen;
        clen = next_cycle(i);
    }
    while ( 0!=clen );

    return 0;
}
// -------------------------


ulong
cycles::get_cycle_minima(ulong *m) const
{
    ulong k=0, len=0, ct = 0;
    while ( (len=next_cycle(k)) )
    {
        ulong t = min(f_+k, len);
        m[ct] = t;
        ++ct;
        k += len-1;
    }
    return  ct;
}
// -------------------------

ulong
cycles::get_cycle_maxima(ulong *m) const
{
    ulong k=0, len=0, ct = 0;
    while ( (len=next_cycle(k)) )
    {
        ulong t = max(f_+k, len);
        m[ct] = t;
        ++ct;
        k += len-1;
    }
    return  ct;
}
// -------------------------


static void
scream(const char *what)
{
    cout << "+++++++++++++++++  "
         << "--- " << what << "  ---"
         << endl;
}
// -------------------------

void
cycles::print(int info_only/*=0*/)  const
{
    if ( 0==nce_ )
    {
        scream("IDENTITY (only fixed points).");
        return;
    }
    else  print_cycles(info_only);

    if ( 0==nf_ )
    {
        cout << "No fixed points." << endl;
    }
    else  print_fixed_points(info_only);
}
// -------------------------


void
cycles::print_fixed_points(int info_only/*=0*/)  const
{
    cout << "number of fixed points = " << nf_ << endl;

    if ( info_only )  return;

    cout << "[";
    for (ulong k=0;  k<nf_-1; ++k)
    {
        cout << f_[nce_+k] << ". ";
    }
    cout << f_[nce_+nf_-1] << "]" << endl;
}
// -------------------------

void
cycles::print_cycles(int info_only/*=0*/)  const
{

    if ( !info_only )
    {
        ulong ct = 0;
        ulong k=0, len=0;
        while ( (len=next_cycle(k)) )
        {
            ulong x = get(k);
            cout << setw(3) << ct << ":";

            cout << "  (";
            cout << setw(3) << x << ",";
            ulong i;
            for (i=1; i<len-1; ++i)
            {
                cout << setw(3) << get(k+i) << ",";
                if ( 15==(i%16) )  cout << "\n  " << "     ";
            }
            cout << setw(3) << get(k+i) << ")";
            cout << " #=" << len;
            cout << endl;

            ++ct;
            k += len-1;
        }
    }

    cout << setw(4) << nce_ << " elements";
    cout << " in " << setw(3) << nc_ << " nontrivial cycles." << endl;

    if ( mi_==ma_ )
    {
        scream("ONE CYCLE LENGTH.");
        cout << "   which is == " << ma_ << endl;
        if ( 2==ma_ )  scream("INVOLUTION (self inverse).");
    }
    else
    {
        cout << " cycle lengths: "
             << setw(3) << mi_ << " ... " << setw(3) << ma_
             << endl;
    }
}
// -------------------------

void
cycles::print_cycles_short()  const
{
    ulong ct = 0;
    ulong k=0, len=0;
    while ( (len=next_cycle(k)) )
    {
        ulong x = get(k);
        cout << " (" << x << ", ";
        ulong i;
        for (i=1; i<len-1; ++i)
        {
            cout << get(k+i) << ", ";
//            if ( 15==(i%16) )  cout << "\n  " << "     ";
        }
        cout << get(k+i) << ")";
//        cout << " #=" << len;
//        cout << endl;

        ++ct;
        k += len-1;
    }
}
// -------------------------


void
cycles::print_leaders()  const
{
    ulong k=0, len=0, ct = 0;
    while ( (len=next_cycle(k)) )
    {
        cout << "#" << setw(3) << ct << ":  ";
        ulong mi, ma;
        mi = ma = get(k+len-1);
        cout << "  len = " << setw(3) << len;
        update_min_max(f_+k, len-1, &mi, &ma);
        cout << "   [" << setw(3) << mi << " .. "
             << setw(3) << ma << "]";
        cout << endl;

        k += len-1;
        ++ct;
    }

#ifdef PARANOIA
    jjassert( ct == nc_ );
#endif // PARANOIA
}
// -------------------------


static void
print_cycle_code(const ulong *f, ulong len, std::ostream &out)
{
    ulong ct = 0;
    ulong z = f[0];
    out << "  { Type t=f[" << z << "]; ";
    out << "f[" << z << "]";

    for (ulong k=1; k<len; ++k)
    {
        z = f[k];
        out  << "=f[" << z << "];";
        ++ct;
        if ( !(ct&3) )  out << endl;
        out << " f[" << z << "]";
    }

    out << "=t; }" << endl;
}
// -------------------------


void
cycles::print_code(const char *funcname, ulong n,
                   int use_swap/*=0*/, int use_stderr/*=0*/)  const
{
    std::ostream &out = (use_stderr ? cerr : cout);

    cout << " ===== start printing CODE "
         << (use_stderr?"(to stderr)":"")
         << " ====="<< endl;
    out << "template <typename Type>" << endl;
    out << "inline void" << endl;
    out << funcname << "_" << n << "(Type *f)" << endl;
    out << "// unrolled version for length " << n << endl;
    out << "{" << endl;

    ulong k=0, len=0, ct = 0;
    while ( (len=next_cycle(k)) )
    {
        if ( (len==2) && use_swap )
        {
            out << "  swap2(f[" << f_[k] << "], f[" << f_[k+1] << "]);" << endl;
        }
        else  print_cycle_code(f_+k, len, out);

        k += len-1;
        ++ct;
    }

    out << "}" << endl;
    cout << " ===== end (printing CODE) "
         << (use_stderr?"to stderr":"")
         << " ====="<< endl;

#ifdef PARANOIA
    jjassert( ct == nc_ );
#endif // PARANOIA
}
// -------------------------



