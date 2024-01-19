#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILE_NAME 100
int main(int argc , char *argv[]){
    for(int i = 1; i < argc; i++){
        int lines = 1;
        FILE *fptr;
        fptr = fopen(argv[i],"r");
        if (fptr == NULL){
            printf("FILE NOT FOUND");
        }
        else{
            int x,min,max,sum;
            fscanf(fptr,"%d", &x);
            min = x;
            max = x;
            sum = x;
            while(fscanf(fptr,"%d", &x) != EOF){
                sum += x;
                lines += 1;
                if (x >= max){
                    max = x;
                }
                if(x<=min){
                    min = x;
                }
            }

            float avg = 0;
            avg = sum/(float)lines;

            char name[] = "";
            if(argc > 2) {sprintf(name,"output%d",i);}
            else{sprintf(name,"output");}
            FILE *f2;
            f2 = fopen(name, "w");
            fprintf(f2, "%d\n", lines);
            fprintf(f2, "%d\n", min);
            fprintf(f2, "%d\n", max);
            fprintf(f2, "%d\n", sum);
            fprintf(f2, "%.2f\n", avg);
    }
    }
    return 0;
}