#include<iostream>
#include <cmath>
using std::cout;
using std::endl;

extern double *mat(int n, int m)
{
    double *p;
    
    if (n<=0||m<=0) return NULL;
    if (!(p=(double *)malloc(sizeof(double)*n*m))) {
        
    }
    return p;
}

int LD(int n, const double *Q, double *L, double *D)
{
    int i,j,k,info=0;
    double a,*A=mat(n,n);

    memcpy(A,Q,sizeof(double)*n*n);

    for (i=n-1;i>=0;i--) {
        if ((D[i]=A[i+i*n])<=0.0) {info=-1; break;}
        a=sqrt(D[i]);
        for (j=0;j<=i;j++) L[i+j*n]=A[i+j*n]/a;
        for (j=0;j<=i-1;j++) for (k=0;k<=j;k++) A[j+k*n]-=L[i+k*n]*L[i+j*n];
        for (j=0;j<=i;j++) L[i+j*n]/=L[i+i*n];
    }
    free(A);
    if (info) fprintf(stderr,"%s : LD factorization error\n",__FILE__);
    return info;
}

int main()
{   
    double temp[]={4,12,-16,12,37,-43,-16,-43,98};
    double *Q=mat(3,3);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            Q[i+j*3]=temp[j+i*3];
        }
    }
    cout<<"Q矩阵为： "<<endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<Q[i+j*3]<<" ";
        }
        cout<<"\n";
    }
    
    double *L=mat(3,3),*D=mat(3,1);
    int info=LD(3,Q,L,D);
    cout<<"L矩阵为： "<<endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<L[i+j*3]<<" ";
        }
        cout<<"\n";
    }
    cout<<"D矩阵为： "<<endl;
    for(int i=0;i<3;i++)
    {
        {
            cout<<D[i]<<" ";
        }
    }
    return 0;
}