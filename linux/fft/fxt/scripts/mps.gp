
f(x)=
{
    x = floor(x);  x = Str(x);  x = Vec(x);
    for (j=1, #x,  print1(x[j]); if((#x-j)%3==0,print1(",")) );
}
