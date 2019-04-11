
// demo-is-self-contained

//% Generate all Schroeder trees with m-leaf nodes, loopless algorithm.

// Code is taken from the paper
//  James F. Korsh, Paul S. Lafollette: "Loopless Generation of Schroeder Trees"
//  Department of Computer and Information Science, Temple University, 2003

#include "fxtio.h"
#include "nextarg.h"


const int MAX=20;
const int TMAX=10*MAX;
int m, k, n, p, top, last, r, numtrees, j, sum;
int Comp[MAX], S[MAX], c[TMAX], q[TMAX], M[TMAX], t[MAX];

//#define TIMING  // uncomment to disable printing


void print_degrees()
{
    for (int i=1; i<=k; i++)  cout << " " << Comp[i]+2;
}
// -------------------------

void print_tree()
{
    for (int i=1; i<=r; i++)  cout << " " << c[i];
}
// -------------------------


void next_comp()
{
    if ( p<k )  Comp[p+1] = 1;
    else
    {
        p = S[top];
        Comp[p+1] = Comp[k]+1;

        if ( Comp[p]==1 ) top--;
        if ( p<k-1 )
        {
            Comp[k] = 0;
            top++;
            S[top] = p+1;
        }
    }

    Comp[p] = Comp[p]-1;
    p++;
}
// -------------------------



void init()
{
    Comp[k-1] = 0;
    Comp[1] = m-k-1;
    S[1] = 1;
    top = p = 1;
    last = 0;
    r = m-1;
    M[k] = 0;
    q[r] = k;
    q[r-1] = k-1;
    M[k-1] = -1;
    sum = c[1] = 0;
    j = r-1;
    q[1] = t[1] = 1;
}
// -------------------------

inline void visit()
{
    numtrees++;

#ifndef TIMING
    cout << setw(4) << numtrees << ":   ";
    print_degrees();
    cout << "   ";
    print_tree();
    cout<<endl;
#endif  // TIMING
}
// -------------------------


void all_trees()
{
    visit();

    while ( j>0 )
    {
        sum = sum+1-c[j+1];
        c[j] = c[j]+1;
        if ( M[q[j]]==-1 )
        {
            M[q[j]] = k-q[j];
            if ( q[j]!=1 )
            {
                q[j+1-Comp[q[j]]-2] = q[j]-1;
                M[q[j+1-Comp[q[j]]-2]] = -1;
                t[q[j]] = j - Comp[q[j]];
            }
        }

        if ( M[q[j]] > M[q[j+1]] )  { M[q[j]] = M[q[j+1]]+1; }

        M[q[j+1]] = M[q[j]];
        c[j+1] = 0;

        if ( sum==M[q[j]] )
        {
            if (t[q[j]]<j)  { q[j-1] = q[j]; }
            j--;
        }
        else
        {
            M[k] = sum;
            j = r-1;
        }

        visit();
    }
}
// -------------------------

void reset()
{
    r = r+last-Comp[k];
    last = Comp[k];
    M[k] = 0;
    q[r] = k;
    q[r-1] = k-1;
    M[k-1] = -1;
    sum = c[1] = 0;
    j = r-1;
}
// -------------------------


int
main(int argc, char **argv)
{
    m = 5;
    NXARG(m, "Generate all m-leaf trees");

    for (int i=1; i<=m; i++)  { c[i]=0; Comp[i]=0; }

    numtrees = 0;

//    if ( m==1 )  cout<< "Only one tree with just the root" << endl;
//    else
    {
        Comp[1] = m-2;
        k = r = 1;
        cout << "k=" << k << ":" << endl;
        visit();
    }

    for (k=2; k<m; k++)
    {
        cout << "k=" << k << ":" << endl;
        init();
        all_trees();
        while ( Comp[k] < m-k-1 )
        {
            next_comp();
            reset();
            all_trees();
        }
    }

    cout << "ct=" << numtrees << endl;

    return 0;
}
// -------------------------


/*
Timing:
 time ./bin 15
# trees is 372693519
./bin 15  4.19s user 0.02s system 99% cpu 4.231 total
 ==> 372693519/4.19 == 88,948,333 per second

 time ./bin 16
# trees is 1968801519
./bin 16  22.12s user 0.11s system 99% cpu 22.251 total
 ==> 1968801519/22.12 == 89,005,493 per second
*/

/*
Timing: (AMD Phenom II X4 945 3000MHz)

 time ./bin 16
ct=1968801519
./bin 16  14.05s user 0.00s system 99% cpu 14.057 total
 ==> 1968801519/14.05 == 140,128,221 per second

*/

// Number of m-leaf trees (OEIS A001003) http://www.oeis.org/A001003
//  1,1,3,11,45,197,903,4279,20793,103049,518859,2646723,13648869,
//  71039373,372693519,1968801519,10463578353,55909013009,300159426963,...


/// Emacs:
/// Local Variables:
/// MyRelDir: "demo/comb"
/// makefile-dir: "../../"
/// make-target: "1demo DSRC=demo/comb/schroeder-tree-demo.cc"
/// make-target2: "1demo DSRC=demo/comb/schroeder-tree-demo.cc DEMOFLAGS=-DTIMING"
/// End:
