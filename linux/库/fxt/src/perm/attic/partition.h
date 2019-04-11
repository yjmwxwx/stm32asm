#if !defined HAVE_PARTITION_H__
#define      HAVE_PARTITION_H__


class partition
{
public:
    partition(int nn);
    ~partition();
    void init();

    int next()
    {
        if ( i<0 )  return 0; // already at last
        make_next();
        return k+1;;
    }

    int index()  const  { return idx; }
    int length()  const  { return k+1; }
    const int *data()  const  { return x;}

private:
    void make_next();
    int n;
//    int n1;
    int k;
    int i;
    int idx;
    int *x;
};
//---------------------


#endif  // !defined HAVE_PARTITION_H__
