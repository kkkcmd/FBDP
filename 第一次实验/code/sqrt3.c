#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    
    
    int myid, P, numprocs, C = 0;
    double SqrtSum = 0.0;
    double result;
    double d;
    double startwtime = 0.0,endwtime=0.0;
    int i;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    int N;
    if(myid == 0)
    {
        printf("Enter a positive int:");
        scanf("%d",&N);
        startwtime = MPI_Wtime();
    }
    MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
    
    
    double *data=(double *)malloc(N*sizeof(double));
    for(i=0;i<N;i++)
        data[i]=i*(i+1);
    

    for(i = myid;i<N;i=i+numprocs)
    {
        SqrtSum+=sqrt(data[i]);
        C++;
    }

    MPI_Reduce(&SqrtSum,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    printf("I am process %d. I calculate total %d ,and SqrtSum=%f.\n", myid, C, SqrtSum);
    if(myid==0)
    {
        printf("I am process 0. final result is %f.\n",result);
        endwtime=MPI_Wtime();
        printf("wall clock time=%f.\n",endwtime-startwtime);
    }
    free(data);
    data=NULL;
    MPI_Finalize();
    return 0;
}

