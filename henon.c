#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

const int l=100;
const int N=10033;
const int xmax=10;
const double eps=1e-5;

int Nper(double lambda, double be)
{
  double x[N],newx[33];
  int h,Nl,p,f,num;

  x[0]=0.02;
  x[1]=0.04;

  Nl=10000;

  for(h=2;h<N;h++) {   //iterate 10033
    if(x[h]>xmax) {
      return 0;
    }
    else {
      x[h]=1-(lambda*pow(x[h-1],2))-(be*x[h-2]);
    }
  }

  for(p=Nl;p<=N;p++) {
    num=0;
    newx[num]=x[p];
    num++;
  }

  for(f=1;f<33;f++) {
    if(abs(newx[f]-newx[0])<eps) {
      return f;
    }
    else {
      return 33;
    }
  }

}


int main()
{
  FILE *F;
  double lam[l],b[l],db,dlam;
  int i,k,j,period[l][l];


  lam[0]=0;
  lam[l-1]=2.0;
  b[0]=-0.5;
  b[l-1]=0.5;
  dlam=fabs((lam[l-1]-lam[0])/l);
  db=fabs((b[l-1]-b[0])/l);

  for(i=0;i<l;i++) {
    lam[i]=lam[0]+i*dlam;
    b[i]=b[0]+i*db;
  }

  F=fopen("henon_c.txt","w+");
  if(F==NULL) {
    printf("\nError");
  }
  else {
    for(k=0;k<l;k++) {
      for(j=0;j<l;j++) {
        period[k][j]=Nper(lam[k],b[j]);
        printf(F,"%2i ",period[k][j]);
      }
      printf("\n");
    }
  }
  fclose(F);
}


