#define MUL 32768.000000
int cordic_ctab [] = {0x00168000,0x000D4853,0x000704A3,0x00039000,0x0001C9C5,0x0000E51B,0x00007295,0x0000394B,0x00001CA5,0x00000E52,0x00000729,0x00000394,0x000001CA,0x000000E5,0x00000072,0x00000039,0x0000001C,0x0000000E,0x00000007,0x00000003,0x00000001};
void cordic(int x, int y, int *jiaodu, int *s, int *c, int n)
{
  int k, d, xx,yy,dangqian_jiaodu;
  n=21;
dangqian_jiaodu=0;
 if(x <  0){
 dangqian_jiaodu = 180*32768;
x = -x;
y = -y;
}
else{
 if(y < 0)
	dangqian_jiaodu = 360 * 32768;
}
  for (k=0; k<n; ++k)
  {
	if(y < 0 ){
	xx = x-(y >> k);
	yy=y+(x>>k);
	dangqian_jiaodu=dangqian_jiaodu-cordic_ctab[k];
	}
	else{ 
	xx = x+(y >> k);
	yy=y-(x>>k);
	dangqian_jiaodu=dangqian_jiaodu+cordic_ctab[k]; 
	}
	x=xx;
	y=yy;
  }  

 *jiaodu = dangqian_jiaodu;
 *s=xx;
  *c=yy;
}
