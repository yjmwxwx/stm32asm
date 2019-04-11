#if !defined  HAVE_TEST_H__
#define       HAVE_TEST_H__

#include "fxttypes.h"
#include "complextype.h"

// aux-test.cc:
double rms_diff(const double *f, const double *g, ulong n);
void print_twodim(const char *bla, const double *f, ulong r, ulong c, double eps=0.0);
void c_print(const char *what, const Complex *c, long n, double eps=0.0);
void ri_print(const char *bla, const double *fr, const double *fi, long n, double eps=0.0);
void approx_eq(const double *f, const double *g, ulong n,
               const char *bla, double eps=1e-12);
void approx_eq(const Complex *f, const Complex *g, ulong n,
               const char *bla, double eps=1e-12);
void approx_eq(const ulong *f, const ulong *g, ulong n, const char *bla);




#define  DO_CHECK() \
{ if ( rms_diff(fr, gr, 2*n) > 1e-10 ) \
 { cout << "  FAILED !"; \
   approx_eq(fr, gr, n,"\n1/2:\n",1e-10); \
   approx_eq(fi, gi, n,"\n2/2:\n",1e-10); \
 cout << " in LINE " << __LINE__ << endl; \
 cout << " n = " << n << endl; \
 exit(33); } \
 else  cout << "  OK." << endl; }

#define  DO_CHECK_IMAG() \
{ if ( rms_diff(fi, gi, n) > 1e-10 ) \
 { cout << "  FAILED !"; \
 approx_eq(fi, gi, n,"\nimag:\n",1e-10); \
 cout << " in LINE " << __LINE__ << endl; \
 cout << " n = " << n << endl; \
 exit(33); } \
 else  cout << "  OK." << endl; }

#define  DO_CHECK_REAL() \
{ if ( rms_diff(fr, gr, n) > 1e-10 ) \
 { cout << "  FAILED !"; \
 approx_eq(fr, gr, n,"\nreal:\n",1e-10); \
 cout << " in LINE " << __LINE__ << endl; \
 cout << " n = " << n << endl; \
 exit(33); } \
 else  cout << "  OK." << endl; }


#define  DO_CHECK_EXACT() \
{ ulong q=0; for (ulong k=0;k<n;++k) if(fr[k]!=gr[k]) { q=k+1;} \
 if ( q )  { cout << "  FAILED !"; \
 approx_eq(fr, gr, n,"\nexact:\n"); \
 cout << " in LINE " << __LINE__ << endl; \
 cout << " n = " << n << endl; \
 exit(33); } \
 else  cout << "  OK." << endl; }


#define  ECHO(x) \
{ acopy(ac, fc, n); \
 cout << ": " << #x << endl;  x; }

#define  CHECK(x) \
{ acopy(ac, gc, n); \
 cout << "== " << #x;  x; DO_CHECK(); }

#define  CHECK_IMAG(x) \
{ acopy(ac, gc, n); \
 cout << "== " << #x;  x; DO_CHECK_IMAG(); }

#define  CHECK_REAL(x) \
{ acopy(ac, gc, n); \
 cout << "== " << #x;  x; DO_CHECK_REAL(); }

#define  EQUIV(x) \
{ cout << "eq " << #x;  x; DO_CHECK(); }

#define  EQUIV_REAL(x) \
{ cout << "eq " << #x;  x; DO_CHECK_REAL(); }

#define  EQUIV_EXACT(x) \
{ cout << "eq " << #x;  x; DO_CHECK_EXACT(); }


#define SMALL_LDN  6  // slow_whatever() tested only for ldn<SMALL_LDN

//#undef copy // end (avoid unwanted std::copy)

#endif  // !defined HAVE_TEST_H__
