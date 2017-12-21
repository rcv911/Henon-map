#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

const int l=1000;
const int N=10033;
const int xmax=10;
const double eps=1e-5;

int Nper(double lambda, double be)
{
  double x[N];
  int h,Nl,p,f,num;

  x[0]=0.03;
  x[1]=0.01;

  Nl=10000;

  for(h=2;h<N;h++) {   //iterate 10033
    if(fabs(x[h-1])>xmax) {
      return 0;
    }
    else {
      x[h]=1-(lambda*pow(x[h-1],2))-(be*x[h-2]);
    }
  }


  for(f=1;f<33;f++) {
    if(fabs(x[f+10000]-x[10000])<eps) {
      return f;
    }
  }
  return 33;
}


int main()
{
  FILE *F;
  double lam[l],b[l],db,dlam;
  int i,k,j;
  char period[l][l];


  lam[0]=0;
  lam[l-1]=2.0;
  b[0]=-0.5;
  b[l-1]=0.5;
  dlam=fabs((lam[l-1]-lam[0])/l);
  db=fabs((b[l-1]-b[0])/l);

  #pragma omp parallel for private(i)
  for(i=0;i<l;i++) {
    lam[i]=lam[0]+i*dlam;
    b[i]=b[0]+i*db;
  }
  #pragma omp parallel for private(k,j)
  for(k=0;k<l;k++) {
    for(j=0;j<l;j++) {
      period[k][j]=Nper(lam[k],b[j]);
    }
  }

  F=fopen("henon_omp_c.txt","w+");
  if(F==NULL) {
    printf("\nError");
  }
  else {
    for(k=0;k<l;k++) {
      for(j=0;j<l;j++) {
        fprintf(F,"%2i ",period[k][j]);
      }
      fprintf(F,"\n");
    }
  }
  fclose(F);
}


