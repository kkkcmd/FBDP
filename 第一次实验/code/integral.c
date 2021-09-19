#define N 10000
#define a 10
#define b 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc,char** argv)
{
    int myid,numprocs,C=0;
    int i,t,source;
    double sum = 0.0,dx=(double)(b-a)/N;
    double x,d;
    double startwtime=0.0,endwtime=0.0;
    MPI_Init(&argc,&argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    numprocs--;
    if(myid==0)
    {
        startwtime=MPI_Wtime();
        for(i = 0;i<N;i++)
            MPI_Send(&i,1,MPI_INT,i%numprocs+1,1,MPI_COMM_WORLD);
        for(source=1;source<=numprocs;source++)
        {
            MPI_Recv(&d,1,MPI_DOUBLE,source,99,MPI_COMM_WORLD,&status);
            sum += d;
        }

    }
    else
    {
        for(i=myid;i<=N;i=i+numprocs)
        {
            MPI_Recv(&t,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
            x=a+t*dx+dx/2;
            sum+=x*x*x*dx;
            C++;
        }
        MPI_Send(&sum,1,MPI_DOUBLE,0,99,MPI_COMM_WORLD);

    }
    printf("I am process %d.I recv total %d from process 0,and sum =%16.15f.\n",myid,C,sum);
    if(myid==0)
    {
        endwtime=MPI_Wtime();
        printf("wall clock time=%f.\n",endwtime-startwtime);
    }
    MPI_Finalize();
}
