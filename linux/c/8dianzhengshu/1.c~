#include<stdio.h>
void main() {
  float shurur[] = {0.3535,0.3535,0.6464,1.0607,0.3535,-1.0607,-1.3535,-0.3535};
  float sr, si,ac,bd,ad,bc;
  float b0r,b0i,b1r,b1i,b2r,b2i,b3r,b3i,b4r,b4i,b5r,b5i,b6r,b6i,b7r,b7i;
  float d0r,d1r,d2r,d3r,d4r,d5r,d6r,d7r;
  float d0i,d1i,d2i,d3i,d4i,d5i,d6i,d7i;
  float c0r,c1r,c2r,c3r,c4r,c5r,c6r,c7r,c0i,c1i,c2i,c3i,c4i,c5i,c6i,c7i;
      /*一*/
       b0r=shurur[0]+shurur[4];
       b4r=shurur[0]-shurur[4];
       b2r=shurur[2]+shurur[6];
       b6r=shurur[2]-shurur[6];
       b1r=shurur[1]+shurur[5];
       b5r=shurur[1]-shurur[5];
       b3r=shurur[3]+shurur[7];
       b7r=shurur[3]-shurur[7];

       /*二*/
       d0r=b0r+b2r;
       d0i=0;
       d2r=b0r-b2r;
       d2i=0;


       b4i=0;
       b6i=0;
       sr=0;
       si=-1;
       ac=b6r*sr;
       bd=b6i*si;
       ad=b6i*sr;
       bc=b6r*si;
       b6r=ac-bd;
       b6i=ad+bc;
       d4r=b4r+b6r;
       d4i=b4i+b6i;
       d6r=b4r-b6r;
       d6i=b4i-b6i;

       d1r=b1r+b3r;
       d1i=0;
       d3r=b1r-b3r;
       d3i=0;


       b6i=0;
       b7i=0;
       sr=0;
       si=-1;
       ac=b7r*sr;
       bd=b7i*si;
       ad=b7i*sr;
       bc=b7r*si;
       b7r=ac-bd;
       b7i=ad+bc;
       d5r=b5r+b7r;
       d5i=b5i+b7i;
       d7r=b5r-b7r;
       d7i=b5i-b7i;

       
       /*三*/
	 
	 
          c0r=d0r+d1r;
          c0i=d0i+d1i;
          c4r=d0r-d1r;
          c4i=d0i-d1i;

          
          sr=0.7071;
          si=-0.7071;
          ac=d5r*sr;
          bd=d5i*si;
          ad=d5i*sr;
          bc=d5r*si;
          d5r=ac-bd;
          d5i=ad+bc;
          c1r=d4r+d5r;
          c1i=d4i+d5i;
          c5r=d4r-d5r;
          c5i=d4i-d5i;

          sr=0;
          si=-1;
          ac=d3r*sr;
          bd=d3i*si;
          ad=d3i*sr;
          bc=d3r*si;
          d3r=ac-bd;
          d3i=ad+bc;
          c2r=d2r+d3r;
          c2i=d2i+d3i;
          c6r=d2r-d3r;
          c6i=d2i-d3i;

          sr=-0.7071;
          si=-0.7071;
          ac=d7r*sr;
          bd=d7i*si;
          ad=d7i*sr;
          bc=d7r*si;
          d7r=ac-bd;
          d7i=ad+bc;
          c3r=d6r+d7r;
          c3i=d6i+d7i;
          c7r=d6r-d7r;
          c7i=d6i-d7i;
              
       printf("%f         %f \n",c0r,c0i);
       printf("%f         %f \n",c1r,c1i);
       printf("%f         %f \n",c2r,c2i);
       printf("%f         %f \n",c3r,c3i);
       printf("%f         %f \n",c4r,c4i);
       printf("%f         %f \n",c5r,c5i);
       printf("%f         %f \n",c6r,c6i);
       printf("%f         %f \n",c7r,c7i);


}
