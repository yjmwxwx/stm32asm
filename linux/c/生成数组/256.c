//位反转
#include <stdio.h>
void main() {
	int aa,a2,a3,a4,a5,bb,cc,dd;


	bb=256;				//长度
	dd=bb;
	for(aa=0;aa<bb;aa++){
		cc=1;
		a3=0;
		a4=a3;
		while(cc<dd){
		a2=aa & cc;
		a5=bb>>1;
		if(a2!=0){
		a5=a5>>a4;
		a3=a3 | a5;
}
		cc=cc<<1;
		a4=a4+1;

	
}
	printf("0x%04X,",a3*4);		
}	
	printf("\n");
}

	
