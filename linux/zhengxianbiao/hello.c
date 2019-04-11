#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc,char *argv[])
{
    int entries, entries_2PI, phase, amplitude, offset, data_per_line;
    int i, j;
    int max, min, max_digits;

    if (argc != 7) {
        fprintf(stderr,"Generate C source code for sine table\n");
        fprintf(stderr,"Usage:\n");
        fprintf(stderr,"sinus_gen entries entries_per_2PI phase amplitude offset data_per_line >outputfile\n\n");
        fprintf(stderr,"entries         : number of entries in sine table\n");
        fprintf(stderr,"entries_per_2PI : number of samples within full 360 degree\n");
        fprintf(stderr,"phase           : phase offset in samples\n");
        fprintf(stderr,"amplitude       : amplitude of sine wave, integer\n");
        fprintf(stderr,"offset          : offset of sine wave, integer\n");
        fprintf(stderr,"data_per_line   : number of samples per line in source file\n");
        fprintf(stderr,">outputfile     : redirect output form terminal to file\n");
        return 1;
    }

    entries = atoi(argv[1]);       //180
    entries_2PI = atoi(argv[2]);   //180
    phase = atoi(argv[3]);        // 0
    amplitude = atoi(argv[4]);     // 20
    offset = atoi(argv[5]);        // 20
    data_per_line = atoi(argv[6]); // 输出多少行

    min = abs(offset - amplitude);
    max = abs(offset + amplitude);

    max_digits=2;
    if (min > 99   || max > 99)   max_digits=3;
    if (min > 999  || max > 999)  max_digits=4;
    if (min > 9999 || max > 9999) max_digits=5;

    // header
    printf("const int sinus[%d] = {\n\t", entries);

    for (i=0, j=0; i<entries; i++) {
        switch(max_digits) {
            case 2: printf("%3d", (int)(offset + amplitude*sin((phase+i)*2*3.1415927/*3))); break;
            case 3: printf("%4d", (int)(offset + amplitude*sin((phase+i)*2*3.1415927/entries_2PI))); break;
            case 4: printf("%5d", (int)(offset + amplitude*sin((phase+i)*2*3.1415927/entries_2PI))); break;
            case 5: printf("%6d", (int)(offset + amplitude*sin((phase+i)*2*3.1415927/entries_2PI))); break;
        }
        if (i < (entries-1)) {
            printf(", ");
        }
        j++;
        if (j==data_per_line) {
            if (i < (entries-1)) {
                printf("\n\t");
            } else {
                printf("\n");
            }
            j=0;
        }
    }
    if (j !=0) printf("\n");

    // footer
    printf("};\n");

    return 0;
}
