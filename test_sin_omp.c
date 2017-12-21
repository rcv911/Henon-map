#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main()
{
    float x[1000];
    int i,n,j;
    float t[1000];
    n=1000;
    FILE *pf,*tm;

    pf=fopen("sin.txt","w+");
    tm=fopen("time_sin.txt","w+");
    if (pf==NULL) {
        printf("\nError\n");
    }
    else{
        #pragma omp parallel for
            for(i=0;i<n;i++) {
                t[i]=i*0.01;
                x[i]=sin(2*M_PI*t[i]);
            }

        for(j=0;j<n;j++) {
            fprintf(tm,"%.3f\n",t[j]);
            fprintf(pf,"%f\n",x[j]);
        }
    }
    fclose(pf);
    fclose(tm);
    return 0;
}
